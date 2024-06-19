import sys
from ai.src.stalker.Stalker import Stalker
from ai.src.Server import Server

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Usage: ./stalker.py ip port name")
        sys.exit(84)
    try:
        server = Server(sys.argv[1], int(sys.argv[2]))
        stalker = Stalker(sys.argv[3])
        stalker.set_welcome_data()
        stalker.run()
