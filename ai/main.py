#!/usr/bin/env python3

from src.Server import Server
from src.FlagParser import FlagParser
from src.queen.Queen import Queen

import sys

if __name__ == '__main__':
    parser = FlagParser.FlagParser(len(sys.argv), sys.argv)
    if not parser.parse_flag():
        exit(84)
    server = Server.Server(parser.get_host(), parser.get_port())
    try:
        server = Server(parser.get_host(), parser.get_port())
        queen = Queen(server)
        queen.set_starting_data(parser)
        queen.run()
    except Exception as e:
        print(e, file=sys.stderr)
