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
        self.functions = {"host" : self.test_host}#, "port" : self.run_cmd, "send" : self.run_cmd, "recv" : self.run_cmd,
                        #"check" : self.run_cmd, "parse" : self.run_cmd, "connect" : self.run_cmd}
        
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
        