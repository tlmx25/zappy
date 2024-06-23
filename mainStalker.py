#!/usr/bin/env python3
import sys
from ai.src.stalker import Stalker
from ai.src import Server

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: ./Stalker.py team_name ip port")
        sys.exit(84)
    try:
        print("Stalker started with ip: " + sys.argv[2] + " and port: " + sys.argv[3])
        server = Server.Server(sys.argv[2], int(sys.argv[3]))
        print("Stalker started with ip: " + sys.argv[2] + " and port: " + sys.argv[3])
        Stalker = Stalker.Stalker(sys.argv[1], server)
        Stalker.run()
    except Exception as e:
        print(e, file=sys.stderr)
        sys.exit(84)
