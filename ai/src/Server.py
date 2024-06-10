##
## EPITECH PROJECT, 2023
## zappy [WSL: Ubuntu-22.04]
## File description:
## Server.py
##

import socket
import select

class Server:
    def __init__(self, _host = "", _port = 0):
        self.host = _host
        self.port = _port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.s.setblocking(False)
            if (self.host != "" and self.port != 0):
                self.conenct_server()
        except:
            raise Exception("Server : Error in init probably during connection.")
    
    def set_host(self, _host):
        self.host = _host
    
    def set_port(self, _port):
        self.port = _port
    
    def connect_server(self):
        try:
            print("Host : " + self.host + " Port : " + str(self.port))
            self.s.connect((self.host, self.port))
            print("Client connected succesfully.")
        except:
            raise Exception("Server : Error while connecting try changing port / host.")
        
    def send(self, command):
        try:
            str_length = len(command)
            for i in range(0, str_length, 1024):
                mess_part = command[i:i + 1024]
                self.s.send(mess_part.encode())
        except Exception:
            raise Exception("Server : Error while sending message.")
        
    def recv(self) -> str:
        response = b""
        try:
            while self.check_read():
                response_part = self.s.recv(1024)
                if (response_part):
                    response += response_part
            return str(response.decode())
        except Exception:
            raise Exception("Server : Error during recieve. Probably dev error.")
        
    def check_read(self) -> bool:
        ready_to_read, _, _ = select.select([self.s], [], [], 1)
        if self.s in ready_to_read:
            return True
        else:
            return False

    def close_socket(self):
        try:
            self.s.close()
        except:
            raise Exception("Server : Error while closing.")