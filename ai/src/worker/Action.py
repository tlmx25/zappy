from .. import Server


class Action:
    def __init__(self, server: Server, orientation: int):
        self.server = server
        self.orientation = orientation
        self.lookResult = ""
        self.state = 0
        self.stateEnum = {
            0: "ELEVATION",
            1: "LOOKING_FOR_RESOURCE"
        }
        self.directionMethod = {
            1: self.goNorth,
            8: self.goNorthEast,
            7: self.goEast,
            6: self.goSouthEast,
            5: self.goSouth,
            4: self.goSouthWest,
            3: self.goWest,
            2: self.goNorthWest
        }

    def getOrientation(self):
        print("getOrientation\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if "message" in response:
            self.orientation = int(response.split(" ")[1].replace(',', ''))
        return

    def setOrientation(self, orientation: int):
        self.orientation = orientation

    def goToQueen(self):
        while self.orientation != 0:
            self.directionMethod[self.orientation]()
            self.getOrientation()

    def dropResource(self, inventory):
        items = inventory[1:-1].split(", ")
        for item in items:
            object_name, quantity = item.split()
            quantity = int(quantity)
            for _ in range(quantity):
                self.server.send(f"Set {object_name}\n")
                while not self.server.check_read():
                    pass
                response = self.server.recv()

    def waitDuringElevation(self):
        while True:
            while not self.server.check_read():
                pass
            response = self.server.recv()
            if "Finished" in response:
                return True

    def analyseResponse(self, response):
        if "Assemble" in response:
            self.state = 0
            self.orientation = int(response.split(" ")[1].replace(',', ''))
            return True
        return False

    def wait_respond(self, nbr):
        print("wait respond:\n")
        for i in range(nbr - 1):
            while not self.server.check_read():
                print("waiting\n")
                pass
            response = self.server.recv()
            print(response + "\n")
            self.analyseResponse(response)
            if "message" in response:
                self.orientation = int(response.split(" ")[1].replace(',', ''))

    def goNorth(self):
        print("goNorth\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(2)

    def goSouth(self):
        print("goSouth\n")
        self.server.send("Left\n")
        self.server.send("Left\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(4)

    def goEast(self):
        print("goEast\n")
        self.server.send("Right\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(3)

    def goWest(self):
        print("goWest\n")
        self.server.send("Left\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(3)

    def goNorthEast(self):
        print("goNorthEast\n")
        self.server.send("Forward\n")
        self.server.send("Right\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(4)

    def goNorthWest(self):
        print("goNorthWest\n")
        self.server.send("Forward\n")
        self.server.send("Left\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(4)

    def goSouthEast(self):
        print("goSouthEast\n")
        self.server.send("Right\n")
        self.server.send("Forward\n")
        self.server.send("Right\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(5)

    def goSouthWest(self):
        print("goSouthWest\n")
        self.server.send("Left\n")
        self.server.send("Forward\n")
        self.server.send("Left\n")
        self.server.send("Forward\n")
        self.takeObject("food")
        self.wait_respond(5)

    def takeObject(self, objects):
        self.server.send("Take " + objects + "\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        self.analyseResponse(response)
        if "ok" in response:
            return True
        return False

    def setWhereToGo(self):
        while not self.server.check_read():
            pass
        response = self.server.recv()
        self.analyseResponse(response)
        if "Look" in response:
            self.lookResult = response
        else:
            self.setWhereToGo()

    def setGoodPosition(self):
        for i in range(4):
            self.server.send("Look\n")
            while not self.server.check_read():
                pass
            response = self.server.recv()
            self.analyseResponse(response)
            if response == self.lookResult:
                return
            self.server.send("Right\n")
            while not self.server.check_read():
                pass
            response = self.server.recv()
            self.analyseResponse(response)

    def setFarmingPosition(self, dist: int):
        self.server.send("Left\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        self.analyseResponse(response)
        for i in range(dist):
            self.server.send("Forward\n")
            while not self.server.check_read():
                pass
            response = self.server.recv()
            self.analyseResponse(response)

    def look(self):
        self.server.send("Look\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        if self.analyseResponse(response):
            return None
        return response

    def getInventory(self):
        self.server.send("Inventory\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        self.analyseResponse(response)
        return response

    def doINeedFood(self, inventory):
        food_amount = int(inventory.split(",")[0].split()[1])
        if food_amount < 3:
            return True
        return False

    def takeObjectPlayerTile(self, lookResponse):
        objects = lookResponse.split(",")[0].split(" ")
        for obj in objects:
            if "player" not in obj:
                self.takeObject(obj)
        return
