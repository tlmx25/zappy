##
## EPITECH PROJECT, 2023
## zappy [WSL: Ubuntu-22.04]
## File description:
## Server.py
##

import socket
import select

class Server:
    def __init__(self, _host="", _port=0):
        self.host = _host
        self.port = _port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            if (self.host != "" and self.port != 0):
                self.connect_server()
        except:
            raise Exception("Server : Error in init probably during connection.")

    def set_host(self, _host):
        self.host = _host

    def set_port(self, _port):
        self.port = _port

    def connect_server(self):
        try:
            self.s.connect((self.host, self.port))
            print("Client connected succesfully.")
        except:
            raise Exception("Server : Error while connecting try changing port / host.")
        
    def send(self, command):
        try:
            self.s.sendall(command.encode("ascii"))
        except Exception:
            raise Exception("Server : Error while sending message.")
        
    def recv(self) -> str:
        try:
            response = self.s.recv(8192).decode()
            return response
        except Exception:
            raise Exception("Server : Error during recieve.")

    def close_socket(self):
        try:
            self.s.close()
        except:
            raise Exception("Server : Error while closing.")