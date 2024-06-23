#!/usr/bin/env python3
import sys
import os
import traceback

# current_dir = os.path.dirname(os.path.abspath(__file__))
# src_dir = os.path.abspath(os.path.join(current_dir, os.pardir, os.pardir, os.pardir))
# sys.path.append(src_dir)

from ai.src.worker import Worker
from ai.src import Server

if __name__ == '__main__':
    if len(sys.argv) != 5:
        print("Usage: ./worker.py id team_name ip port")
        sys.exit(84)
    try:
        print("Worker started with ip: " + sys.argv[3] + " and port: " + sys.argv[4])
        server = Server.Server(sys.argv[3], int(sys.argv[4]))
        print("Worker started with ip: " + sys.argv[3] + " and port: " + sys.argv[4])
        Worker = Worker.Worker(sys.argv, server)
        Worker.run()
    except Exception as e:
        print(e, file=sys.stderr)
        traceback.print_exc()
        sys.exit(84)
