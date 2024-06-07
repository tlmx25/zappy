from Server import Server

class Command:

    def __init__(self, server: Server):
        self.commandSend = []
        self.server = server


    def mooveForward(self):
        self.commandSend.append("Forward")

    def mooveRight(self):
        self.commandSend.append("Right")

    def mooveLeft(self):
        self.commandSend.append("Left")

    def look(self):
        self.commandSend.append("Look")

    def inventory(self):
        self.commandSend.append("Inventory")

    def broadcast(self, message):
        self.commandSend.append("Broadcast " + message)

    def connectNumber(self, number):
        self.commandSend.append("Connect_nbr " + number)

    def fork(self):
        self.commandSend.append("Fork")

    def eject(self):
        self.commandSend.append("Eject")

    def takeObject(self, object):
        self.commandSend.append("Take " + object)

    def setObject(self, object):
        self.commandSend.append("Set " + object)

    def incantation(self):
        self.commandSend.append("Incantation")
