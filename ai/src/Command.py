from Server import Server

class Command:

    def __init__(self, server: Server):
        self.commandSend = []
        self.server = server


    def mooveForward(self):
        self.server.send("Forward\n")
        while not self.server.check_read():
            pass

    def mooveRight(self):
        self.server.send("Right")
        while not self.server.check_read():
            pass

    def mooveLeft(self):
        self.server.send("Left")
        while not self.server.check_read():
            pass

    def look(self):
        self.server.send("Look")
        while not self.server.check_read():
            pass

    def inventory(self):
        self.server.send("Inventory")
        while not self.server.check_read():
            pass
        return self.server.recv()

    def broadcast(self, message):
        self.server.send("Broadcast " + message)
        while not self.server.check_read():
            pass

    def connectNumber(self, number):
        self.server.send("Connect_nbr " + number)
        while not self.server.check_read():
            pass

    def fork(self):
        self.server.send("Fork")
        while not self.server.check_read():
            pass

    def eject(self):
        self.server.send("Eject")
        while not self.server.check_read():
            pass

    def takeObject(self, object):
        self.server.send("Take " + object)
        while not self.server.check_read():
            pass

    def setObject(self, object):
        self.server.send("Set " + object)
        while not self.server.check_read():
            pass

    def incantation(self):
        self.server.send("Incantation")
        while not self.server.check_read():
            pass
