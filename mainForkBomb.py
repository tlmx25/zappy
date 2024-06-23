#!/usr/bin/env python3
import sys
from ai.src.bomb import ForkBomb
from ai.src import Server

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: ./ForkBomb.py team_name ip port")
        sys.exit(84)
    try:
        print("ForkBomb started with ip: " + sys.argv[2] + " and port: " + sys.argv[3])
        server = Server.Server(sys.argv[2], int(sys.argv[3]))
        print("ForkBomb started with ip: " + sys.argv[2] + " and port: " + sys.argv[3])
        ForkBomb = ForkBomb.Stalker(sys.argv[1], server)
        ForkBomb.run()
    except Exception as e:
        print(e, file=sys.stderr)
        sys.exit(84)
