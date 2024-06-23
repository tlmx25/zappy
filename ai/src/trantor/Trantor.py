##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ATrantor.py
##

from ai.src.trantor.ITrantor import ITrantor
from ai.src.Server import Server
from ai.src.FlagParser import FlagParser
import sys

class Trantor(ITrantor):
    """
    The Trantor class implements the ITrantor interface, defining all general-purpose functions.
    """
    
    def __init__(self, server : Server):
        """
        Set values at class init.
        @param server: server class use to communicate
        @type server: Server
        @return: None
        """
        self.server = server
        self.team = ""
        self.id = ""
        self.free_slots_team = 0
        self.world_dimension = []
        self.messages = []
        self.incantation = False
        self.alive = True
        self.incatator = False
        self.level = 1
        self.trantor_inventory = { 'food' : 0,
                        'linemate' : 0,
                        'deraumere' : 0,
                        'sibur' : 0,
                        'mendiane' : 0,
                        'phiras' : 0,
                        'thystame' : 0}
        self.requirement = {1 : {'linemate' : 1, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0},
                            2 : {'linemate' : 1, 'deraumere' : 1, 'sibur' : 1, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0},
                            3 : {'linemate' : 2, 'deraumere' : 0, 'sibur' : 1, 'mendiane' : 0, 'phiras' : 2, 'thystame' : 0},
                            4 : {'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'mendiane' : 0, 'phiras' : 1, 'thystame' : 0},
                            5 : {'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3, 'phiras' : 0, 'thystame' : 0},
                            6 : {'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'mendiane' : 0, 'phiras' : 1, 'thystame' : 0},
                            7 : {'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1}}

    # Gestion de messages

    def receive(self) -> str:
        cmd_response = None
        serv_response = self.server.recv()
        while serv_response[-1] != "\n":
            serv_response += self.server.recv()
        #print(self.id + " received : " + serv_response)
        serv_response = list(filter(None, serv_response.split("\n")))
        for response in serv_response:
            if not response or "eject" in response:
                continue
            if response == "dead":
                self.alive = False
                return "dead"
            elif "message" in response:
                response = response[7:].replace(" ", "").split(",")
                self.messages.append((int(response[0]), response[1]))
                #print(self.id + ": Added message to messages.")
            elif "Elevation" in response:
                self.incantation = True
            elif "Current level" in response:
                self.incantation = False
                self.level = int(response[15:])
                if self.incantator:
                    cmd_response = response
                    self.incatator = False
            else:
                cmd_response = response
        return cmd_response
    
    def send(self, command : str) -> str:
        if not self.alive:
            return None
        self.server.send(command)
        response = self.receive()
        while response is None or self.incantation:
            response = self.receive()
        return response
    
    # Commandes

    def move_forward(self) -> str:
        return self.send("Forward\n")
    
    def move_left(self) -> str:
        response = self.send("Left\n")
        response = self.move_forward()
        return response
    
    def turn_left(self) -> str:
        return self.send("Left\n")
    
    def move_right(self) -> str:
        response = self.send("Right\n")
        response = self.move_forward()
        return response
        
    def turn_right(self) -> str:
        return self.send("Right\n")
        
    def move_behind(self) -> str:
        response = self.turn_right()
        response = self.turn_right()
        return self.move_forward()
    
    def take_object(self, object: str) -> str:
        #print("Take : " + object)
        return self.send("Take " + object + "\n")
        
    def look(self) -> dict:
        interpreted_look = {}
        response = self.send("Look\n")
        response = response.replace("[", "").replace("]", "").split(',')
        for i in range(0, len(response)):
            interpreted_look[i] = {"player" : 0, "food" : 0, "linemate" : 0, "deraumere" : 0, "sibur" : 0, "mendiane" : 0, "phiras" : 0, "thystame" : 0}
        for i in range(0, len(response)):
            splited_tile = response[i].split(' ')
            for object in splited_tile:
                match object:
                    case "player":
                        interpreted_look[i]["player"] += 1
                    case "food":
                        interpreted_look[i]["food"] += 1
                    case "linemate":
                        interpreted_look[i]["linemate"] += 1
                    case "deraumere":
                        interpreted_look[i]["deraumere"] += 1
                    case "sibur":
                        interpreted_look[i]["sibur"] += 1
                    case "mendiane":
                        interpreted_look[i]["mendiane"] += 1
                    case "phiras":
                        interpreted_look[i]["phiras"] += 1
                    case "thystame":
                        interpreted_look[i]["thystame"] += 1
                    case _:
                        pass
        #print("Look : " + str(interpreted_look), file=sys.stderr)
        return interpreted_look
    
    def inventory(self) -> str:
        response = self.send("Inventory\n")
        if response is None:
            return response
        response = response.strip('[]').split(",")
        for object in response:
            object = object.strip().split()
            self.trantor_inventory[object[0]] = int(object[1])
        #print("Inventory : " + str(self.trantor_inventory), file=sys.stderr)
        return "ok"

    def broadcast(self, message : str) -> str:
        return self.send("Broadcast " + message + "\n")
    
    def set_object(self, object: str) -> str:
        return self.send("Set " + object + "\n")
    
    def incantation(self) -> str:
        self.incatator = True
        return self.send("Incantation\n")
    
    def fork(self) -> str:
        return self.send("Fork\n")
    
    def eject(self) -> str:
        return self.send("Eject\n")
    
    def connect_nbr(self):
        response = self.send("Connect_nbr\n")
        return None
        
    def run(self):
        food_fail = 0
        self.inventory()
        while self.alive:
            while self.take_object("food") != "ko" and self.alive:
                food_fail = 0
                self.take_object("food")
            food_fail += 1
            if food_fail > 3:
                self.move_left()
                self.turn_right()
            else:
                self.move_forward()
    
    def set_starting_data(self, parser: FlagParser):
        server_res = self.server.recv()
        if server_res == "WELCOME\n":
            response = self.server.send(parser.get_team() + "\n")
            self.team = parser.get_team()
            response = self.server.recv()
            if response == "ko\n":
                raise Exception("ATrantor : Error in team name.")
            splited_r = response.replace('\n', ' ').split(" ")
            self.free_slots_team = int(splited_r[0])
            for i in range (1, 2):
                self.world_dimension.append(splited_r[i])

    def dropResource(self, inventory):
        print("dropResource\n")
        items = inventory[1:-1].split(", ")
        print("items: " + str(items) + "\n")
        for item in items:
            object_name, quantity = item.split()
            quantity = int(quantity)
            for _ in range(quantity):
                print(f"Set {object_name}\n")
                self.send(f"Set {object_name}\n")