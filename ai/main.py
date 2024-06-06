#!/usr/bin/env python3

from src import Server as Server
from src import FlagParser as FlagParser
import sys

if __name__ == '__main__':
    parser = FlagParser.FlagParser(len(sys.argv), sys.argv)
    if not parser.parse_flag():
        exit(84)
    server = Server.Server(parser.get_host(), parser.get_port())
    try:
        print("Welcome : " + server.recv(), end="")
        server.send(parser.get_team() + "\n")
        print("team : " + server.recv())
        server.send("Broadcast Hello\n")
        print("Broadcast : " + server.recv())
    except Exception:
        raise Exception("Error during sending")