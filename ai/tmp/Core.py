from src import Command as Command
from src import Server as Server
from src import Survive as Survive
from src import FlagParser as FlagParser
import sys


class Core:
    def __init__(self, server: Server.Server):
        self.world_dimension = []
        self.free_slots_team = 0

        self.commandSend = []
        self.server = server
        self.command = Command.Command(server)
        self.level = 1
        self.needFood = False
        self.survive = Survive.Survive(self.command, self.server, self.level)

    def run(self):
        while True:
            if self.server.check_read():
                # TODO: parse server response (broadcast)
                pass

            inventory_response = self.command.inventory()
            self.survive.need_food(inventory_response)
            self.survive.search_resources(inventory_response)

    def set_welcome_data(self, server: Server.Server, parser: FlagParser.FlagParser):
        response = ""
        try:
            if (server.check_read() and server.recv() == "WELCOME\n" and server.check_send()):
                server.send(parser.get_team() + "\n")
                response = server.recv()
                if (response == "ko\n"):
                    return
                splited_r = response.replace('\n', ' ').split(" ")
                self.free_slots_team = int(splited_r[0])
                for i in range (1, 2):
                    self.world_dimension.append(splited_r[i])
        except Exception as e:
            print(e, file=sys.stderr)
            raise Exception("Core: Error while sending welcome data.")