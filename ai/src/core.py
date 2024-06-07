from Command import Command
from Server import Server
from Survive import Survive


class Core:

    def __init__(self, server: Server):
        self.commandSend = []
        self.server = server
        self.command = Command(server)
        self.commandQueue = []
        self.level = 1
        self.needFood = False
        self.survive = Survive(self.command, self.server, self.level)

    def run(self):
        while True:
            inventory_response = self.command.inventory()
            self.survive.need_food(inventory_response)
            self.survive.search_resources(inventory_response)
            # else:
            #     action_response = perform_incantation(inventory_response, level)
            #     if action_response == "Elevation underway":
            #         level += 1
