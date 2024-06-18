import sys

from ai.src.Server import Server
from ai.src.worker.Action import Action
class Worker:
    def __init__(self, argv, server: Server):
        self._worker = None
        self.id = argv[1]
        self.team_name = argv[2]
        self.server = server
        self.direction = None
        self.action = Action(self.server, 0)

    def waiting_to_start(self):
        self.server.send("Broadcast Worker,READY\n")
        while not self.server.check_read():
            pass
        response = self.server.recv()
        while not self.server.check_send():
            pass
        response = self.server.recv()
        if "message" and "FARM" in response:
            parts = response.split(",")[0].split(" ")
            self.direction = parts[1]
            return
        else:
            raise Exception("Core: Error while waiting to start.")

    def starting_mode(self):
        self.action.setOrientation(int(self.direction))
        self.action.goToQueen()
        self.action.setWhereToGo()
        self.action.setGoodPosition()
        self.action.setFarmingPosition(int(self.id))

    def run(self):
        self.starting_mode()
        while True:
            if self.action.state == 0:
                self.action.goToQueen()
            lookRespond = self.action.look()
            if lookRespond is None:
                continue
            self.action.takeObjectPlayerTile(lookRespond)

    def set_welcome_data(self):
        response = ""
        try:
            if self.server.check_read() and self.server.recv() == "WELCOME\n" and self.server.check_send():
                self.server.send(self.team_name + "\n")
                response = self.server.recv()
                if response == "ko\n":
                    return
        except Exception as e:
            print(e, file=sys.stderr)
            raise Exception("Core: Error while sending welcome data.")
