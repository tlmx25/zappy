#!/usr/bin/env python3

from src import Server as Server
from src import FlagParser as FlagParser
from src import Core as Core
import sys

if __name__ == '__main__':
    parser = FlagParser.FlagParser(len(sys.argv), sys.argv)
    if not parser.parse_flag():
        exit(84)
    try:
        server = Server.Server(parser.get_host(), parser.get_port())
        bot = Core.Core(server)
        bot.set_welcome_data(server, parser)
    except Exception as e:
        print(e, file=sys.stderr)