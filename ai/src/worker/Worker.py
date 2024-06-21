import sys

from ai.src.Server import Server
from ai.src.trantor.Trantor import Trantor
from ai.src.FlagParser import FlagParser

class Worker(Trantor):
    def __init__(self, argv, server: Server):
        self._worker = None
        self.team_name = argv[2]
        super().__init__(server)
        self.id = argv[1]
        self.direction = None
        self.orientation = 1
        self.state = 1
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

    def waiting_to_start(self):
        response = self.broadcast("Worker" + self.id + ",READY\n")
        print("first response " + response + "\n")
        while True:
            self.take_object("food")
            #print("WAITING Assemble SIGNAL\n")
            for mes in self.messages:
                print("message: " + mes[1] + "\n")
                if "message" and "Assemble" in mes[1]:
                    print("second response " + mes[1] + "\n")
                    self.direction = mes[0]
                    # self.emptyMessage()
                    return
                #else:
                #    self.messages.pop(mes)

    def starting_mode(self):
        self.goToQueen()
        self.setFarmingPosition(int(self.id))

    def setModeFarming(self):
        self.setFarmingPosition(self.orientation)

    def set_welcome_data(self):
        response = ""
        try:
            print(self.team_name + "\n")
            response = self.send(self.team_name + "\n")
            if response == "ko\n":
                return
        except Exception as e:
            print(e, file=sys.stderr)
            raise Exception("Core: Error while sending welcome data.")

    def set_starting_data(self, parser: FlagParser):
        self.set_welcome_data()
        self.waiting_to_start()
        self.starting_mode()

    def run(self):
        self.set_starting_data(None)
        print("STARTING MODE FINISHED")
        count = 0
        self.emptyMessage()
        while True:
            if self.state == 0:
                print("IN ASSEMBLE MODE")
                self.goToQueen()
                self.dropResource(self.getInventory())
                self.waitDuringElevation()
                self.setModeFarming()
                self.state = 1
            lookRespond = self.look()
            if lookRespond is None:
                continue
            self.takeObjectPlayerTile(lookRespond)
            count += 1
            if count == 3:
                self.sendInventoryToQueen()
                count = 0
            self.move_forward()
            for mes in self.messages:
                if "Assemble" in mes:
                    self.state = 0
                    self.emptyMessage()
                    print("Orientation = " + str(mes[0]))
                    self.orientation = int(mes[0])

    def takeObjectPlayerTile(self, lookResponse):
        print("lookResponse: " + lookResponse)
        lookResponse = lookResponse.replace("[ ", "")
        lookResponse = lookResponse.replace(" ]", "")
        print("lookResponse: " + lookResponse)
        objects = lookResponse.split(",")[0].split(" ")
        print("objects: " + str(objects))
        for obj in objects:
            if "player" not in obj:
                print("take: " + obj)
                self.take_object(obj)

    def getInventory(self):
        print("getInventory\n")
        response = self.send("Inventory\n")
        print("Inventory: " + response)
        return response

    def goToQueen(self):
        while self.orientation != 0:
            self.getOrientation()
            if self.orientation == 0:
                break
            self.directionMethod[self.orientation]()

    def emptyMessage(self) -> None:
        self.messages = []

    def getOrientation(self):
        print("getOrientation\n")
        self.emptyMessage()
        while True:
            #print("WAITING ASSEMBLE SIGNAL\n")
            self.take_object("food")
            for mes in self.messages:
                if "Assemble" in mes[1]:
                    self.orientation = mes[0]
                    return "Assemble"

    def sendInventoryToQueen(self):
        print("sendInventoryToQueen\n")
        self.send("Inventory\n")
        response = self.waitTillGoodResp()
        response = response.replace("[ ", "[")
        response = response.replace(" ]", "]")
        response = response.replace(", ", ",")
        response = response.replace(" ", "+")
        print("SendInventoryResponse: " + response)
        self.send("Broadcast Worker,FOUND" + response + "\n")
        return

    def look(self):
        response = self.send("Look\n")
        print("Send Look !")
        return response

    def setFarmingPosition(self, dist: int):
        for i in range(dist):
            self.move_forward()
        self.move_left()
        print("WAITING FARM SIGNAL !\n")
        while True:
            for mes in self.messages:
                if "FARM" in mes[1]:
                    self.emptyMessage()
                    return

    def waitDuringElevation(self):
        while True:
            for mes in self.messages:
                if "Finished" in mes[1]:
                    self.emptyMessage()
                    return True

    def goNorth(self):
        print("goNorth\n")
        self.send("Forward\n")
        self.take_object("food")

    def goSouth(self):
        print("goSouth\n")
        self.send("Left\n")
        self.send("Left\n")
        self.send("Forward\n")
        self.take_object("food")

    def goEast(self):
        print("goEast\n")
        self.send("Right\n")
        self.send("Forward\n")
        self.take_object("food")

    def goWest(self):
        print("goWest\n")
        self.send("Left\n")
        self.send("Forward\n")
        self.take_object("food")
    def goNorthEast(self):
        print("goNorthEast\n")
        self.send("Forward\n")
        self.send("Right\n")
        self.send("Forward\n")
        self.take_object("food")
    def goNorthWest(self):
        print("goNorthWest\n")
        self.send("Forward\n")
        self.send("Left\n")
        self.send("Forward\n")
        self.take_object("food")

    def goSouthEast(self):
        print("goSouthEast\n")
        self.send("Right\n")
        self.send("Forward\n")
        self.send("Right\n")
        self.send("Forward\n")
        self.take_object("food")

    def goSouthWest(self):
        print("goSouthWest\n")
        self.send("Left\n")
        self.send("Forward\n")
        self.send("Left\n")
        self.send("Forward\n")
        self.take_object("food")
