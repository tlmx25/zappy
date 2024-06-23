import sys

from ai.src.Server import Server
from ai.src.trantor.Trantor import Trantor
from ai.src.FlagParser import FlagParser
import random

class Worker(Trantor):
    def __init__(self, argv, server: Server):
        self._worker = None
        self.id = argv[1]
        self.object_taken = []
        self.team_name = argv[2]
        super().__init__(server)
        self.id = argv[1]
        self.direction = None
        self.orientation = 1
        self.state = 1
        self.last_id_queen = -1
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
        while True:
            self.take_object("food")
            for message in self.messages:
                direction = message[0]
                message = message[1].split("+")
                if len(message) == 3 and message[0] == "Queen" and message[1] == "Assemble":
                    try:
                        id_message = int(message[2])
                        if self.last_id_queen == id_message:
                            continue
                        self.direction = direction
                        return
                    except:
                        continue
            self.messages.clear()

    def starting_mode(self):
        self.goToQueen()
        self.broadcast("Worker" + self.id + "+Assembled\n")
        print("WAITING FARM SIGNAL !\n")
        while True:
            self.take_object("food")
            for mes in self.messages:
                if "FARM" in mes[1]:
                    self.emptyMessage()
                    self.setFarmingPosition(int(self.id))
                    return

    def setModeFarming(self):
        self.setFarmingPosition(self.orientation)

    def set_welcome_data(self, parser: FlagParser = None):
        response = self.server.recv()
        if response == "WELCOME\n":
            print(self.team_name + "\n")
            self.server.send(self.team_name + "\n")
            response = self.server.recv()
            if response == "ko\n":
                raise Exception("Worker : Error in team name.")
            splited_r = response.replace('\n', ' ').split(" ")
            self.free_slots_team = int(splited_r[0])
            for i in range (1, 2):
                self.world_dimension.append(splited_r[i])

    def set_starting_data(self, parser: FlagParser):
        self.set_welcome_data()
        self.waiting_to_start()
        self.starting_mode()
        
    def check_queen_order(self, order: str):
        self.receive()
        if not self.alive:
            print("\033[31mWorker" + self.id + " died.\033[0m")
            exit(0)
        for message in self.messages:
            if message[0] != 0:
                continue
            message = message[1].split("+")
            if len(message) != 3 or message[0] != "Queen" or message[1] != order:
                continue
            try:
                id_message = int(message[2])
                if id_message == self.last_id_queen:
                    continue
                self.last_id_queen = id_message
                self.messages.clear()
                return True
            except Exception:
                print("Worker : Incant not from my queen")
        self.messages.clear()
        return False

    def run(self):
        self.set_starting_data(None)
        print("STARTING MODE FINISHED")
        count = 0
        self.emptyMessage()
        while True:
            if self.state == 0:
                print("IN ASSEMBLE MODE")
                self.goToQueen()
                self.broadcast("Worker" + self.id + "+Assembled\n")
                while not self.check_queen_order("STARTDROP"):
                    continue
                    #print("\033[34m Worker" + self.id + " : waiting for drop\033[0m")
                self.dropResource(self.getInventory())
                self.broadcast("Worker" + self.id + "+DROP\n")
                while not self.check_queen_order("INCANT"):
                    continue
                self.inventory()
                print("\033[33mWorker current level : " + str(self.level) + "\033[0m")
                while not self.check_queen_order("TAKERES"):
                    continue
                self.take_ressources()
                self.setModeFarming()
                self.state = 1
            lookRespond = self.lookAt()
            print(lookRespond)
            self.takeObjectPlayerTile(lookRespond)
            count += 1
            if count == 3:
                self.sendInventoryToQueen()
                count = 0
            self.move_forward()
            for mes in self.messages:
                if "Assemble" in mes[1]:
                    self.state = 0
                    self.emptyMessage()
                    print("Orientation = " + str(mes[0]))
                    self.orientation = int(mes[0])

    def take_ressources(self):
        res = self.look()
        if not res is None:
            res = res[0]["food"]
        print("\033[34m Worker" + self.id + " : take ressources\033[0m")
        ressources = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
        inventory_val = ""
        for ressource in ressources:
            if ressource == "food" and res is not None:
                for i in range(0, int(res / 5)):
                    self.take_object("food")
                continue
            while self.take_object(ressource) == "ok":
                continue
        self.inventory()
        for ressource in self.trantor_inventory:
            print("\033[34m Worker" + self.id + " : ajoute " + ressource + "\033[0m")
            inventory_val += str(self.trantor_inventory[ressource]) + "+"
        self.broadcast("Worker" + self.id + "+INV+" + inventory_val[:-1])
        while not self.check_queen_order("FARM"):
            continue
        
    def takeObjectPlayerTile(self, lookResponse):
        if lookResponse is None:
            response = self.take_object("food")
            if response == "ok":
                self.object_taken.append(object_type)
            return
        for object_type, quantity in lookResponse[0].items():
            if quantity > 0:
                if "player" in object_type:
                    print("player detected\n")
                else:
                    print("take: " + object_type + "\n")
                    self.object_taken.append(object_type)
                    self.take_object(object_type)

    def getInventory(self):
        print("getInventory\n")
        response = self.send("Inventory\n")
        print("Worker Inventory: " + response)
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
        self.messages.clear()
        while True:
            self.take_object("food")
            for message in self.messages:
                direction = message[0]
                message = message[1].split("+")
                if len(message) != 3 or message[0] != "Queen" and message[1] != "Assemble":
                    continue
                try:
                    id_message = int(message[2])
                    if self.last_id_queen == id_message:
                        continue
                    self.orientation = direction
                    self.last_id_queen = id_message
                    return "Assemble"
                except:
                    continue
            self.messages.clear()

    def sendInventoryToQueen(self):
        print("sendInventoryToQueen\n")
        response = " ".join(self.object_taken)
        response = response.replace(" ", "+")
        response = "[" + response + "]+" + str(random.randint(0, 1000000))
        print("SendInventoryResponse: " + response)
        self.send("Broadcast Worker" + self.id + "+FOUND+" + response +"\n")
        self.object_taken.clear()
        return

    def lookAt(self):
        response = self.look()
        #print("Send Look !")
        return response

    def setFarmingPosition(self, dist: int):
        for i in range(dist):
            self.move_forward()
        self.move_left()

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
