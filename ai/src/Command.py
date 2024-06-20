from src.Server import Server

class Command:
    def __init__(self, server: Server):
        self.commandSend = []
        self.server = server

    def parse_response(self, response):
        if 'broadcast' in response:
            return 42
        if 'ko' in response:
            return -1
        return response

    def move_forward(self):
        self.server.send("Forward\n")
        ##while not self.server.check_read():
        ##    pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def turn_right(self):
        self.server.send("Right\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def turn_left(self):
        self.server.send("Left\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def look(self):
        self.server.send("Look\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def inventory(self):
        self.server.send("Inventory\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def broadcast(self, message):
        self.server.send("Broadcast " + message + "\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def connect_nbr(self):
        self.server.send("Connect_nbr\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def fork(self):
        self.server.send("Fork\n")
        print("J'ai send fork")
        while not self.server.check_read():
            pass
        print("Je reçois une réponse")
        response = self.server.recv()
        print("LA RESPONSE : " + response)
        if self.parse_response(response) == 42:
            return 42
        return response

    def eject(self):
        self.server.send("Eject\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response

    def take_object(self, object):
        self.server.send("Take " + object + "\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            print("no ressource")
            return -1
        return response

    def set_object(self, object):
        self.server.send("Set " + object + "\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response

    def incantation(self):
        self.server.send("Incantation\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response
