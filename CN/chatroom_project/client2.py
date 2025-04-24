import socket
import ssl
import threading
import time
import sys

def receive_messages(client_socket):
    """Continuously receive and display messages from the server"""
    try:
        buffer = ""
        while True:
            try:
                data = client_socket.recv(1024).decode('utf-8')
                if not data:
                    print("Server closed the connection.")
                    break
                    
                buffer += data
                
                # Process complete messages (in case we get multiple at once)
                lines = buffer.split('\n')
                # Keep the last line if it's incomplete
                buffer = lines.pop() if lines and not data.endswith('\n') else ""
                
                # Print each complete line
                for line in lines:
                    if line.strip():  # Only print non-empty lines
                        print(line)
                        
            except ssl.SSLError as e:
                if e.errno == ssl.SSL_ERROR_WANT_READ:
                    # Non-blocking SSL socket needs more data, just continue
                    continue
                else:
                    print(f"SSL Error: {e}")
                    break
            except Exception as e:
                print(f"Error in receive: {e}")
                break
    except Exception as e:
        print(f"Receive thread error: {e}")
    finally:
        print("Disconnected from server")

def start_client():
    """Connect to the server and handle user input"""
    client_socket = None
    try:
        # Create socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Connect first, then wrap with SSL
        print("Connecting to server...")
        client_socket.connect(('10.1.5.6', 5555))
        
        # Set up SSL context
        context = ssl.create_default_context()
        context.check_hostname = False
        context.verify_mode = ssl.CERT_NONE  # For development only, not secure for production
        
        # Wrap the socket with SSL
        client_socket = context.wrap_socket(client_socket, server_hostname="10.1.5.6")
        print("Connected to server.")
        
        # Handle initial username prompt
        username_prompt = client_socket.recv(1024).decode('utf-8')
        username = input(username_prompt)
        client_socket.send(username.encode('utf-8'))
        
        # Start the receive thread
        receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
        receive_thread.daemon = True
        receive_thread.start()
        
        print("\nStart typing messages (type /quit to exit):")
        while True:
            try:
                message = input()
                if message.lower() == "/quit":
                    client_socket.send(message.encode('utf-8'))
                    print("Goodbye!")
                    time.sleep(1)  # Give time for server to process quit command
                    break
                else:
                    client_socket.send(message.encode('utf-8'))
            except BrokenPipeError:
                print("Connection to server lost.")
                break
            except ConnectionResetError:
                print("Connection reset by server.")
                break
            except Exception as e:
                print(f"Error sending message: {e}")
                break
                
    except ConnectionRefusedError:
        print("Connection refused. Is the server running?")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        if client_socket:
            try:
                client_socket.shutdown(socket.SHUT_RDWR)
                client_socket.close()
            except:
                pass
        print("Client terminated.")

if __name__ == "__main__":
    start_client()