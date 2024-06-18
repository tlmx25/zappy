#!/usr/bin/env python3
import sys
from ai.src.worker.Worker import Worker
from ai.src.Server import Server

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: ./worker.py id team_name ip port")
        sys.exit(84)
    try:
        server = Server(sys.argv[3], int(sys.argv[4]))
        Worker = Worker(sys.argv, server)
        Worker.set_welcome_data()
        Worker.waiting_to_start()
        Worker.run()
    except Exception as e:
        print(e, file=sys.stderr)
        sys.exit(84)