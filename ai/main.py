#!/usr/bin/env python3

from ai.src.Server import Server
from ai.src.FlagParser import FlagParser
from ai.src.queen.Queen import Queen
import sys
import traceback

if __name__ == '__main__':
    parser = FlagParser(len(sys.argv), sys.argv)
    if not parser.parse_flag():
        exit(84)
    try:
        server = Server(parser.get_host(), parser.get_port())
        queen = Queen(server)
        queen.set_starting_data(parser)
        queen.run()
    except Exception as e:
        print(e, file=sys.stderr)
        traceback.print_exc()