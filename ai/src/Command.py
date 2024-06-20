from Server import Server

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

    def mooveForward(self):
        self.server.send("Forward\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def mooveRight(self):
        self.server.send("Right")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def mooveLeft(self):
        self.server.send("Left")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def look(self):
        self.server.send("Look")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def inventory(self):
        self.server.send("Inventory")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def broadcast(self, message):
        self.server.send("Broadcast " + message)
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def connectNumber(self, number):
        self.server.send("Connect_nbr " + number)
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def fork(self):
        self.server.send("Fork")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return 42
        return response

    def eject(self):
        self.server.send("Eject")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response

    def takeObject(self, object):
        self.server.send("Take " + object)
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response

    def setObject(self, object):
        self.server.send("Set " + object)
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response

    def incantation(self):
        self.server.send("Incantation")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.parse_response(response) == 42:
            return -1
        if self.parse_response(response) == -1:
            return -1
        return response
