from ai.src.Server import Server
from ai.src.FlagParser import FlagParser
import sys




class Queen:
    def __init__(self, server: Server):
        self.world_dimension = [0, 0]
        self.free_slots_team = 0
        self.connected_worker = 0
        self.is_dead = False
        self.broadcast_ids = []

        #self.commandSend = []
        #self.server = server
        #self.command = Command.Command(server)
        #self.level = 1
        #self.needFood = False
        #self.survive = Survive.Survive(self.command, self.server, self.level)

    def run(self):
        while not self.is_dead:
            pass

    def set_welcome_data(self, server: Server, parser: FlagParser):
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
