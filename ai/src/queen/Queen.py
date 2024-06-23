##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Queen.py
##

from ai.src.trantor.Trantor import Trantor
from ai.src.Server import Server
import subprocess


class Queen(Trantor):
    def __init__(self, server: Server):
        super().__init__(server)
        self.id = "Queen"
        self.cycle = 0
        self.ko_food = 0
        self.cycle_action = {0 : self.get_vital_ressources,
                             1 : self.init_worker,
                             2 : self.start_farming,
                             3 : self.check_elevate,
                             4 : self.temp
                             }
        self.connected_worker = 0
        self.assembled_worker = 0
        self.id_message = []
        self.id_farm = {}
        self.in_farming = False
        self.enough_ressources = False
        self.common_inventory = { 'food' : 0,
                        'linemate' : 0,
                        'deraumere' : 0,
                        'sibur' : 0,
                        'mendiane' : 0,
                        'phiras' : 0,
                        'thystame' : 0}

    def run(self):
        while self.alive:
            if self.trantor_inventory["food"] < 5:
                self.cycle = 0
            self.cycle_action[self.cycle]()
            self.inventory()
    
    def look_for_food(self):
        response = self.take_object("food")
        if response == "ko":
            self.ko_food += 1
        else:
            self.ko_food = 0
        if self.ko_food >= 3:
            self.move_right()
            self.turn_left()
            self.ko_food = 0
        else:
            self.move_forward()
    
    def get_vital_ressources(self):
        ko_food = 0
        while self.trantor_inventory["food"] < 15:
            self.look_for_food()
            self.inventory()
        if self.connected_worker < 5:
            self.cycle = 1
        elif not self.in_farming:
            self.cycle = 2
        elif not self.enough_ressources:
            self.cycle = 3
        else:
            self.cycle = 4
    
    def init_worker(self):
        worker_id = str(self.connected_worker + 1)
        if self.free_slots_team < 1:
            response = self.fork()
            self.free_slots_team += 1
        subprocess.Popen(["./mainWorker.py", worker_id, self.team,
                          self.server.host, str(self.server.port)])
        self.connected_worker += 1
        self.free_slots_team -= 1
        if self.connected_worker == 5:
            self.cycle = 2

    def assemble_workers(self):
        self.broadcast("Assemble")
        if len(self.messages) > 0:
            for message in self.messages:
                if message[0] != 0:
                    continue
                content = message[1].split("+")
                if len(content) != 2 or not "Worker" in content[0] or "Assembled" != content[1]:
                    continue
                try:
                    only_id = content[0][6:]
                    id = int(only_id)
                    if not id in self.id_message:
                        self.id_message.append(id)
                        self.assembled_worker += 1
                except Exception as e:
                    print("WORKER FAILED : " + str(e))
            self.messages.clear()

    def start_farming(self):
        self.assemble_workers()
        if self.assembled_worker == 5:
            self.broadcast("FARM")
            self.cycle = 3
            self.assembled_worker = 0
            self.id_message.clear()
            
    def check_ressources(self):
        if self.common_inventory["food"] < 20:
            return
        requirement = self.requirement[self.level]
        for mineral in requirement:
            if requirement[mineral] > self.common_inventory[mineral]:
                return
        self.enough_ressources = True
    
    def check_elevate(self):
        if self.enough_ressources:
            self.assemble_workers()
            if self.assembled_worker == 5:
                self.cycle = 4
        else:
            self.look_for_food()
            for message in self.messages:
                message = message[1].replace("[", "").replace("]", "").split("+")
                if not "Worker" in message[0] or message[1] != "FOUND" or message[2] == '':
                    continue
                try:
                    found_id = int(message[-1])
                except Exception:
                    continue
                if message[0] in self.id_farm and self.id_farm[message[0]] == found_id:
                    continue
                self.id_farm[message[0]] = found_id
                for i in range(2, len(message) - 1):
                    self.common_inventory[message[i]] += 1
                print("Queen updated common inventory : " + str(self.common_inventory))
            self.check_ressources()
            self.messages.clear()

    def temp(self):
        print("QUEEN NEED START ELEVATION")
        pass
