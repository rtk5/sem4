import socket
import threading
import ssl
import sqlite3
import time
import os
from chatroom import ChatRoom

ADMIN_USERS = ["admin"]  # Example: hardcoded admin username
EMOJIS = {":smile:": "😊", ":sad:": "😞", ":laugh:": "😂", ":heart:": "❤️", ":thumbsup:": "👍"}

class ChatServer:
    def __init__(self, host='10.1.5.6', port=5555):
        self.host = host
        self.port = port
        self.server_socket = None
        self.running = False
        
        # Create SSL context
        self.context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
        self.context.load_cert_chain(certfile="ssl_cert/server.crt", keyfile="ssl_cert/server.key")
        
        self.chatrooms = {}
        self.client_usernames = {}  # socket -> username
        self.client_chatroom = {}   # socket -> chatroom
        self.muted_users = set()    # usernames
        self.banned_users = set()   # usernames
        self.typing_users = set()   # currently typing users
        self.clients = []          # all connected clients
        
        # Make sure database directory exists
        os.makedirs("database", exist_ok=True)

        self.conn = sqlite3.connect("database/chat_logs.db", check_same_thread=False)
        self.cursor = self.conn.cursor()
        self.cursor.execute("""
            CREATE TABLE IF NOT EXISTS logs (
                username TEXT, room TEXT, message TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )
        """)
        self.conn.commit()

    def initialize_socket(self):
        # Create a new socket
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # Wrap with SSL
        self.server_socket = self.context.wrap_socket(self.server_socket, server_side=True)

    def start_server(self):
        # Initialize default rooms
        for name in ["general", "tech", "fun"]:
            self.chatrooms[name] = ChatRoom(name)
        
        max_retries = 5
        retry_count = 0
        retry_delay = 2  # seconds
        
        while retry_count < max_retries:
            try:
                self.initialize_socket()
                self.server_socket.bind((self.host, self.port))
                self.server_socket.listen(5)
                print(f"Server started on {self.host}:{self.port}")
                self.running = True
                break
            except socket.error as e:
                if e.errno == 98:  # Address already in use
                    print(f"Port {self.port} is already in use. Retrying in {retry_delay} seconds...")
                    retry_count += 1
                    time.sleep(retry_delay)
                    
                    # Try with a different port if needed
                    if retry_count >= 3:
                        self.port += 1
                        print(f"Trying with port {self.port}")
                else:
                    print(f"Error binding socket: {e}")
                    break
        
        if not self.running:
            print("Failed to start server after multiple attempts")
            return
        
        self.accept_connections()

    def accept_connections(self):
        """Handle incoming connections in a loop"""
        while self.running:
            try:
                client_socket, addr = self.server_socket.accept()
                print(f"[LOG] Connection from {addr}")
                self.clients.append(client_socket)
                client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
                client_thread.daemon = True
                client_thread.start()
            except Exception as e:
                if self.running:  # Only show error if we're supposed to be running
                    print(f"Error accepting connection: {e}")
            
    def handle_client(self, client_socket):
        """Handle a single client connection"""
        username = None
        try:
            client_socket.send(b"Enter your username: ")
            username = client_socket.recv(1024).decode().strip()
            
            if not username:
                client_socket.send(b"Invalid username. Disconnecting.\n")
                return
                
            if username in self.banned_users:
                client_socket.send(b"You are banned from this server.\n")
                return

            self.client_usernames[client_socket] = username

            welcome = f"\n[Welcome {username}]\nYou have joined the chatroom!\nType /help for commands.\n"
            client_socket.send(welcome.encode())
            self.join_chatroom("general", client_socket)
            
            # Notify everyone that a new user has joined
            self.chatrooms["general"].broadcast(f"[System] {username} has joined the server!", sender_socket=client_socket)

            while True:
                try:
                    msg = client_socket.recv(1024).decode().strip()
                    if not msg:
                        break
                        
                    if msg.startswith("/"):
                        if msg.lower() == "/quit":
                            client_socket.send(b"Goodbye!\n")
                            break
                        self.handle_command(msg, client_socket)
                    else:
                        username = self.client_usernames[client_socket]
                        if username in self.muted_users:
                            client_socket.send(b"You are muted and cannot send messages.\n")
                            continue
                            
                        room = self.client_chatroom[client_socket].name
                        message = self.parse_emoji(f"[User: {username}] {msg}")
                        self.client_chatroom[client_socket].broadcast(message, sender_socket=client_socket)
                        
                        # Log the message to database
                        self.cursor.execute("INSERT INTO logs (username, room, message) VALUES (?, ?, ?)", 
                                           (username, room, msg))  # Store original message, not the emoji-parsed one
                        self.conn.commit()
                except ConnectionResetError:
                    print(f"[LOG] Connection reset by {username}")
                    break
                except Exception as e:
                    print(f"Error receiving message from {username}: {e}")
                    break
        except Exception as e:
            print(f"Error handling client: {e}")
        finally:
            self.disconnect_client(client_socket)

    def handle_command(self, msg, client_socket):
        cmd = msg.split(" ")
        username = self.client_usernames[client_socket]
        current_room = self.client_chatroom.get(client_socket)

        if cmd[0] == "/help":
            help_msg = """
Available commands:
/help                 Show this message
/quit                 Exit chat
/join <room>          Join existing room
/create <room>        Create and join a new room
/list                 List users in your room
/rooms                List all available rooms
/kick <username>      (Admin) Kick a user
/ban <username>       (Admin) Ban a user
/mute <username>      (Admin) Mute a user
/unmute <username>    (Admin) Unmute a user
            """
            client_socket.send(help_msg.encode())

        elif cmd[0] == "/quit":
            # This will be handled in the main loop
            pass

        elif cmd[0] == "/create" and len(cmd) == 2:
            roomname = cmd[1]
            if roomname not in self.chatrooms:
                self.chatrooms[roomname] = ChatRoom(roomname)
                client_socket.send(f"Room '{roomname}' created.\n".encode())
            self.join_chatroom(roomname, client_socket)

        elif cmd[0] == "/join" and len(cmd) == 2:
            roomname = cmd[1]
            if roomname in self.chatrooms:
                self.join_chatroom(roomname, client_socket)
            else:
                client_socket.send(f"Room '{roomname}' does not exist. Use /create {roomname} to create it.\n".encode())

        elif cmd[0] == "/list":
            if current_room:
                users = current_room.list_users()
                client_socket.send(f"Users in {current_room.name}: {', '.join(users)}\n".encode())
            else:
                client_socket.send(b"You are not in any room.\n")
                
        elif cmd[0] == "/rooms":
            rooms = ", ".join(self.chatrooms.keys())
            client_socket.send(f"Available rooms: {rooms}\n".encode())

        elif cmd[0] == "/kick" and len(cmd) == 2:
            if username in ADMIN_USERS:
                target = cmd[1]
                self.kick_user(target, reason="Kicked by admin")
                client_socket.send(f"User {target} kicked.\n".encode())
            else:
                client_socket.send(b"Permission denied. Admin privileges required.\n")

        elif cmd[0] == "/ban" and len(cmd) == 2:
            if username in ADMIN_USERS:
                target = cmd[1]
                self.ban_user(target)
                client_socket.send(f"User {target} banned.\n".encode())
            else:
                client_socket.send(b"Permission denied. Admin privileges required.\n")

        elif cmd[0] == "/mute" and len(cmd) == 2:
            if username in ADMIN_USERS:
                self.muted_users.add(cmd[1])
                client_socket.send(f"User {cmd[1]} muted.\n".encode())
            else:
                client_socket.send(b"Permission denied. Admin privileges required.\n")

        elif cmd[0] == "/unmute" and len(cmd) == 2:
            if username in ADMIN_USERS:
                if cmd[1] in self.muted_users:
                    self.muted_users.discard(cmd[1])
                    client_socket.send(f"User {cmd[1]} unmuted.\n".encode())
                else:
                    client_socket.send(f"User {cmd[1]} is not muted.\n".encode())
            else:
                client_socket.send(b"Permission denied. Admin privileges required.\n")

        else:
            client_socket.send(b"Invalid command. Type /help for available commands.\n")

    def kick_user(self, target_username, reason="You have been kicked from the server."):
        """Kick a user from the server"""
        for sock, name in list(self.client_usernames.items()):
            if name == target_username:
                sock.send(f"{reason}\n".encode())
                self.disconnect_client(sock)
                return True
        return False

    def ban_user(self, target_username):
        """Ban a user from the server"""
        self.banned_users.add(target_username)
        return self.kick_user(target_username, reason="You have been banned from the server.")

    def join_chatroom(self, roomname, client_socket):
        """Join a user to a chatroom"""
        current = self.client_chatroom.get(client_socket)
        username = self.client_usernames.get(client_socket, "Unknown")
        
        if current:
            current.broadcast(f"[System] {username} left room '{current.name}'.", sender_socket=None)
            current.remove_client(client_socket)
            
        self.chatrooms[roomname].add_client(client_socket)
        self.client_chatroom[client_socket] = self.chatrooms[roomname]
        client_socket.send(f"You joined room '{roomname}'.\n".encode())

    def disconnect_client(self, client_socket):
        """Handle client disconnection"""
        try:
            username = self.client_usernames.get(client_socket, "Unknown")
            print(f"[LOG] {username} disconnected")
            
            # Remove from chatroom
            room = self.client_chatroom.get(client_socket)
            if room:
                room.remove_client(client_socket)
                room.broadcast(f"[System] {username} left the chat.")
                
            # Clean up dictionaries
            self.client_usernames.pop(client_socket, None)
            self.client_chatroom.pop(client_socket, None)
            
            if client_socket in self.clients:
                self.clients.remove(client_socket)
                
            # Close socket
            client_socket.close()
        except Exception as e:
            print(f"Error during client disconnect: {e}")

    def parse_emoji(self, message):
        """Replace emoji codes with actual emojis"""
        for emoji_code, emoji in EMOJIS.items():
            message = message.replace(emoji_code, emoji)
        return message
        
    def shutdown(self):
        """Shut down the server properly"""
        self.running = False
        
        # Notify and disconnect all clients
        for client in list(self.clients):
            try:
                client.send(b"Server is shutting down. Goodbye!\n")
                client.close()
            except:
                pass
                
        # Close server socket
        if self.server_socket:
            self.server_socket.close()
            
        # Close database connection
        self.conn.close()
        print("Server shut down.")

if __name__ == "__main__":
    try:
        server = ChatServer()
        server.start_server()
    except KeyboardInterrupt:
        print("\nShutting down server...")
        server.shutdown()
    except Exception as e:
        print(f"Fatal error: {e}")