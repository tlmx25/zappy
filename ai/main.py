#!/usr/bin/env python3

from src import Server as Server

if __name__ == '__main__':
    server = Server.Server("127.0.0.1", 8581)
    print('Hello, AI!')