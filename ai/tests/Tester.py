##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Tester.py
##

import os
import sys

current_dir = os.path.dirname(os.path.abspath(__file__))
ai_parent_dir = os.path.join(current_dir, '..')
sys.path.append(ai_parent_dir)

from src import Server as Server
from src import FlagParser as FlagParser

class AiTester :
    def __init__(self):
        self.server = Server.Server()
        self.flag_parser = FlagParser.FlagParser(len(sys.argv), sys.argv)
        self.functions = {"host" : self.test_host, "port" : self.test_port, "connect" : self.test_connect, "send" : self.test_send}#, "recv" : self.run_cmd,
                        #"check" : self.run_cmd, "parse" : self.run_cmd, "connect" : self.run_cmd}
                        
    def connect(self, host, port):
        try:
            self.server.set_host(host)
            self.server.set_port(port)
            self.server.connect_server()
        except Exception:
            raise Exception("Error while connecting.")
    
    def concat_message(self, message):
        try:
            if not message:
                return ""
            return " ".join(message)
        except:
            print("Concat failed.", file=sys.stderr)
        
    def test_run(self):
        entry = input("Command > ")
        while (entry.lower() != "stop"):
            self.run_cmd(entry)
            entry = input("Command > ")
    
    def run_cmd(self, cmd):
        splited_cmd = cmd.split()
        if splited_cmd[0] in self.functions:
            self.functions[splited_cmd[0]](splited_cmd)
        else:
            print("Not aviable command.", file=sys.stderr)
            
    def test_host(self, cmd):
        try:
            self.server.set_host(cmd[1])
            if (self.server.host == cmd[1]):
                print("Host successfully set.", file=sys.stderr)
            else:
                print("Error while setting host.", file=sys.stderr)
        except Exception:
            print("Error while setting host.", file=sys.stderr)
        
    def test_port(self, cmd):
        try:
            self.server.set_port(int(cmd[1]))
            if (self.server.port == int(cmd[1])):
                print("Port successfully set.", file=sys.stderr)
            else:
                print("Error while setting port.", file=sys.stderr)
        except Exception:
            print("Error while setting port.", file=sys.stderr)
            
    def test_connect(self, cmd):
        try:
            self.connect(cmd[1], int(cmd[2]))
            print("Connected to server.", file=sys.stderr)
        except Exception:
            print("Connection failed.", file=sys.stderr)
            
    def test_send(self, cmd):
        try:
            self.connect(cmd[1], int(cmd[2]))
            self.server.send(self.concat_message(cmd[3:]))
            print("Message sended to server.", file=sys.stderr)
        except Exception:
            print("Send failed.", file=sys.stderr)
