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
        self.cycle_action = {0 : self.get_food,
                             1 : self.init_worker,
                             2 : self.assemble_workers,
                             3 : self.temp}
        self.connected_worker = 0
        self.assembled_worker = 0
        self.id_message = []

    def run(self):
        while self.alive:
            if self.trantor_inventory["food"] < 5:
                self.cycle = 0
            self.cycle_action[self.cycle]()
            self.inventory()
    
    def get_food(self):
        ko_food = 0
        while self.trantor_inventory["food"] < 15:
            response = self.take_object("food")
            if response == "ko" and ko_food < 2:
                response = self.move_forward()
                ko_food += 1
            elif ko_food >= 2:
                self.move_right()
                self.turn_left()
                ko_food = 0
            self.inventory()
        if self.connected_worker < 5:
            self.cycle = 1
        else:
            self.cycle = 2
    
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
        print("LA LEN DE MESSAGES " + str(len(self.messages)))
        if len(self.messages) > 0:
            print("J'AI DES MESSAGES A READ !")
            for message in self.messages:
                #print("JE TRAITE CE MESSAGE : " + str(message[0]) + " " + message[1])
                if message[0] != 0:
                    pass
                content = message[1].split(",")
                if len(content) != 2 or not "Worker" in content[0] or "READY" != content[1]:
                    pass
                try:
                    id = int(content[0][:6])
                    if not id in self.id_message:
                        self.id_message.append(id)
                        self.assembled_worker += 1
                except Exception:
                    pass
            self.messages.clear()
        if self.assembled_worker == 5:
            self.broadcast("FARM")
            self.cycle = 3
            self.assembled_worker = 0
        pass

    def temp(self):
        print("Je suis passé au cycle 3")
        pass