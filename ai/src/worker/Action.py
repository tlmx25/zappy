from .. import Server
from src.trantor.Trantor import Trantor

class Action():
    def __init__(self, server: Server, orientation: int):
        self.server = server
        self.orientation = orientation
        self.lookResult = ""
        self.state = 1
        self.stateEnum = {
            0: "ELEVATION",
            1: "LOOKING_FOR_RESOURCE"
        }

    def wait_respond(self, nbr):
        print("wait respond:\n")
        for i in range(nbr - 1):
            while not self.server.check_read():
                print("waiting\n")
                pass
            response = self.server.recv()
            print(response + "\n")

    def takeObject(self, objects):
        self.server.send("Take " + objects + "\n")
        self.waitTillGoodResp()

    def look(self):
        response = self.server.send("Look\n")
        print("Send Look !")
        response = self.waitTillGoodResp()
        return response

    def getInventory(self):
        print("getInventory\n")
        self.server.send("Inventory\n")
        response = self.waitTillGoodResp()
        print("Inventory: " + response)
        return response

    def waitTillGoodResp(self):
        while True:
            while not self.server.check_read():
                pass
            response = self.server.recv()
            if "message" in response:
                self.analyseResponse(response)
                pass
            else:
                return response
