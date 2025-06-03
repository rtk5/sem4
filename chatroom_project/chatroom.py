class ChatRoom:
    def __init__(self, name):
        self.name = name
        self.clients = []
        
    def add_client(self, client_socket):
        """Add a client to the chatroom"""
        if client_socket not in self.clients:
            self.clients.append(client_socket)
    
    def remove_client(self, client_socket):
        """Remove a client from the chatroom"""
        if client_socket in self.clients:
            self.clients.remove(client_socket)
    
    def broadcast(self, message, sender_socket=None):
        """Send a message to all clients in the room except the sender"""
        # Ensure the message ends with a newline for proper display
        if not message.endswith('\n'):
            message += '\n'
            
        message_bytes = message.encode('utf-8')
        
        # Make a copy of the clients list to avoid modification during iteration
        clients_copy = self.clients.copy()
        
        for client in clients_copy:
            # Don't send back to the sender
            if client != sender_socket:
                try:
                    client.send(message_bytes)
                except Exception as e:
                    print(f"Error broadcasting to client: {e}")
                    # Don't remove here, let the server handle disconnects
    
    def list_users(self):
        """Return a list of usernames in the room"""
        # This needs to be implemented by the server since it has the username mapping
        # We'll return client socket identifiers here, and the server will translate
        return [str(client.getpeername()) for client in self.clients]