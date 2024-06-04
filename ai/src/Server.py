##
## EPITECH PROJECT, 2023
## zappy [WSL: Ubuntu-22.04]
## File description:
## Server.py
##

import socket

class Server:
    def __init__(self, _host, _port):
        host = _host
        port = _port
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.connect()
        except:
            raise Exception("Error while connecting at init try connect method.")
    
    def setHost(self, _host):
        self.host = _host
    
    def setPort(self, _port):
        self.port = _port;
    
    def connect(self):
        try:
            self.s.connect((self.host, self.port))
            print("Client connected succesfully.")
        except:
            raise Exception("Error while connecting try changing port / host.")
        
    def send(self, command):
        pass
    
    