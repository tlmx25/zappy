##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Queen.py
##

from src.trantor.Trantor import Trantor
from src.Server import Server
import subprocess


class Queen(Trantor):
    def __init__(self, server: Server):
        super().__init__(server)
        self.cycle = 0
        self.cycle_action = {0 : self.get_food,
                             1 : self.init_worker,
                             2 : self.temp}
        self.connected_worker = 0

    def run(self):
        while self.alive:
            if self.trantor_inventory["food"] < 25:
                self.cycle = 0
            self.cycle_action[self.cycle]()
            self.inventory()
    
    def get_food(self):
        while self.trantor_inventory["food"] < 40:
            response = self.take_object("food")
            if response == "ko":
                self.move_forward()
            self.inventory()
        if self.connected_worker < 5:
            self.cycle = 1
        else:
            self.cycle = 2
    
    def init_worker(self):
        subprocess.run("./src/worker/Worker.py")
        self.connected_worker += 1
        if self.connected_worker == 5:
            self.cycle = 2

    def temp(self):
        resopnse = self.fork()
        if resopnse == "ok":
            print("fork success")
        pass