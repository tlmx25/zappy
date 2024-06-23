##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Queen.py
##

from ai.src.trantor.Trantor import Trantor
from ai.src.Server import Server
import subprocess
import random


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
                             4 : self.level_up,
                             5 : self.define_cycle_reset,
                             6 : self.temp
                             }
        self.connected_worker = 0
        self.assembled_worker = 0
        self.ressource_dropped = 0
        self.id_message = []
        self.id_farm = {}
        self.in_farming = False
        self.enough_ressources = False
        self.elevated = False
        self.common_inventory = { 'food' : 0,
                        'linemate' : 0,
                        'deraumere' : 0,
                        'sibur' : 0,
                        'mendiane' : 0,
                        'phiras' : 0,
                        'thystame' : 0}

    def run(self):
        while self.alive:
            if self.trantor_inventory["food"] < 3:
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
        elif self.ko_food != 0:
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
        elif not self.elevated:
            self.cycle = 4
        else:
            self.cycle = 5
    
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
        self.broadcast("Queen+Assemble+" + str(random.randint(0,1000000)))
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
        if self.common_inventory["food"] < 40:
            self.enough_ressources = False
            return
        self.inventory()
        if self.trantor_inventory["food"] < 6:
            self.enough_ressources = False
            return
        requirement = self.requirement[self.level]
        for mineral in requirement:
            if requirement[mineral] > self.common_inventory[mineral]:
                self.enough_ressources = False
                return
        self.enough_ressources = True
    
    def check_elevate(self):
        if self.enough_ressources:
            self.assemble_workers()
            if self.assembled_worker == 5:
                self.assembled_workers = 0
                self.id_message.clear()
                self.cycle = 4
                #print("\033[33mQueen send startdrop\033[0m")
                while self.trantor_inventory["food"] > 7:
                    self.set_object("food")
                    self.inventory()
                self.broadcast("Queen+STARTDROP+" + str(random.randint(0,1000000)))
        else:
            self.look_for_food()
            if len(self.messages) == 0:
                self.check_ressources()
                return
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
                print("\033[33mQueen : Common ressources : " + str(self.common_inventory) + "\033[0m")
            self.check_ressources()
            self.messages.clear()
            
    def start_incantation(self):
        response = self.incantation()
        if response == "ko":
            print("\033[31mQueen : Incantation failed!\033[0m")
        else:
            print("\033[32mQueen : Incant succeed -> level = " + str(self.level) + "\033[0m")
        self.ressource_dropped = 0
        self.cycle = 5
        self.elevated = True
            
    def level_up(self):
        if self.ressource_dropped == 5:
            self.id_message.clear()
            self.ressource_dropped = 0
            self.broadcast("Queen+INCANT+" + str(random.randint(0,1000000)))
            self.start_incantation()
            return
        self.inventory()
        for message in self.messages:
            if message[0] != 0:
                continue
            message = message[1].split("+")
            if len(message) != 2 or message[1] != "DROP" or "Worker" not in message[0]:
                continue
            try:
                only_id = message[0][6:]
                id = int(only_id)
                if not id in self.id_message:
                    self.id_message.append(id)
                    self.ressource_dropped += 1
            except Exception as e:
                print("WORKER FAILED : " + str(e))
        self.messages.clear()
        #print("\033[33mQueen : Actual dropped ressources : " + str(self.ressource_dropped) + "\033[0m")
        
    def set_ressources(self, values : list):
        try:
            print("\033[33mQueen : range 1 inv " + str(values) + "\033[0m")
            self.common_inventory["food"] += int(values[0])
            self.common_inventory["linemate"] += int(values[1])
            self.common_inventory["deraumere"] += int(values[2])
            self.common_inventory["sibur"] += int(values[3])
            self.common_inventory["mendiane"] += int(values[4])
            self.common_inventory["phiras"] += int(values[5])
            self.common_inventory["thystame"] += int(values[6])
        except:
            raise Exception("Set value fail")
        
    def define_cycle_reset(self):
        inv_worker = 0
        self.broadcast("Queen+TAKERES+" + str(random.randint(0,1000000)))
        for ressource in self.common_inventory:
            self.common_inventory[ressource] = 0
        print("\033[33mQueen : Common ressources at the begining : " + str(self.common_inventory) + "\033[0m")
        while inv_worker != 5:
            self.inventory()
            for message in self.messages:
                if message[0] != 0:
                    continue
                message = message[1].split("+")
                if len(message) != 9 or not "Worker" in message[0] or "INV" != message[1]:
                    continue
                only_id = message[0][6:]
                try:
                    id = int(only_id)
                    if not id in self.id_message:
                        print("\033[33mQueen : Try 1 inv : " + str(inv_worker) + " " + str(id) + "\033[0m")
                        self.id_message.append(id)
                        inv_worker += 1
                        self.set_ressources(message[2:])
                except Exception as e:
                    print("WORKER FAILED : " + str(e))
            self.messages.clear()
        self.id_message.clear()
        self.messages.clear()
        self.assembled_worker = 0
        self.enough_ressources = False
        self.elevated = False
        self.cycle = 3
        self.broadcast("Queen+FARM+" + str(random.randint(0, 1000000)))

    def temp(self):
        pass
