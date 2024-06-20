##
## EPITECH PROJECT, 2023
## zappy [WSL: Ubuntu-22.04]
## File description:
## Server.py
##

import socket

class Server:
    """
    Server class that implements methods to handle tcp datatransfer beetween AI and server
    """

    def __init__(self, _host = "", _port = 0):
        self.host = _host
        self.port = _port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            if (self.host != "" and self.port != 0):
                self.connect_server()
        except:
            raise Exception("Server : Error in init probably during connection.")
    
    def set_host(self, _host):
        """
        Define host used for tcp connection.

        @param _host: host to set
        @type _host: str
        """
        self.host = _host
    
    def set_port(self, _port):
        """
        Define port used for tcp connection.

        @param _port: port to set
        @type _port: int
        """
        self.port = _port
    
    def connect_server(self):
        """
        Connect to a server using tcp socket, defined host and port.
        @return : None or raise Exception in case of fail.
        @rtype: None
        """
        try:
            self.s.connect((self.host, self.port))
            print("Client connected succesfully.")
        except:
            raise Exception("Server : Error while connecting try changing port / host.")
        
    def send(self, command):
        """
        Send data encoded in ascii to a server using socket.
        @param command: command to send.
        @type command: str
        @return: None or raise Exception in case of fail.
        @rtype: None
        """
        try:
            self.s.sendall(command.encode("ascii"))
        except Exception:
            raise Exception("Server : Error while sending message.")

    def recv(self) -> str:
        """
        Receive in a blocking way and decode data from a server using socket
        @return : Data send by the server.
        @rtype: str
        """
        try:
            response = self.s.recv(8192).decode()
            return response
        except Exception:
            raise Exception("Server : Error during recieve.")

    def close_socket(self):
        """
        Close opened tcp socket.
        @return : None or raise Exception in case of fail.
        @rtype: None
        """
        try:
            self.s.close()
        except:
            raise Exception("Server : Error while closing.")