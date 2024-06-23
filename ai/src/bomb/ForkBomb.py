from ai.src.Server import Server
from ai.src.FlagParser import FlagParser
from ai.src.trantor.Trantor import Trantor
import subprocess
import random


class Stalker(Trantor):
    def __init__(self, team_name: str, server: Server):
        self.team_name = team_name
        self.server = server
        super().__init__(server)
        self.team_name = team_name

    def set_welcome_data(self, parser: FlagParser = None):
        response = self.server.recv()
        if response == "WELCOME\n":
            print(self.team_name + "\n")
            self.server.send(self.team_name + "\n")
            response = self.server.recv()
            if response == "ko\n":
                raise Exception("Worker : Error in team name.")

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

    def emptyMessage(self) -> None:
        self.messages = []

    def forkBomb(self):
        for i in range(0, 4):
            print("Forking egg")
            self.fork()
        for i in range(0, 4):
            print("Forking")
            subprocess.Popen(["./mainForkBomb.py", self.team_name, self.server.host, str(self.server.port)])

    def randomDeplacement(self):
        randint = random.randint(0, 3)
        if randint == 0:
            self.move_forward()
        elif randint == 1:
            self.move_right()
            self.move_forward()
        elif randint == 2:
            self.move_left()
            self.move_forward()
        else:
            self.move_right()
            self.move_right()
            self.move_forward()

    def run(self):
        print("STARTING MODE")
        self.set_welcome_data()
        print("STARTING MODE FINISHED")
        while True:
            i = 0
            if i == 0:
                self.forkBomb()
                i = i + 1
            self.get_food()
            self.randomDeplacement()
