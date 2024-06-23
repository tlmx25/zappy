from ai.src.Server import Server
from ai.src.FlagParser import FlagParser
from ai.src.trantor.Trantor import Trantor


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

    def did_i_rcv_broadcast(self):
        for mes in self.messages:
            if "message" in mes[1]:
                for i in range(0, 4):
                    self.broadcast(mes[1])
        self.emptyMessage()

    def emptyMessage(self) -> None:
        self.messages = []

    def run(self):
        print("STARTING MODE")
        self.set_welcome_data()
        print("STARTING MODE FINISHED")
        self.emptyMessage()
        while True:
            self.get_food()
            self.broadcast("dead\n")
            self.broadcast("Elevation underway\n")
            self.did_i_rcv_broadcast()
            pass
