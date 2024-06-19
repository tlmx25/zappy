import sys
from ai.src.Server import Server

class Stalker:
    def __init__(self, name, server: Server):
        self.name = name
        self.server = server

    def run(self):
        while True:
            if self.server.check_read():
                response = self.server.recv()
                if response == "dead\n":
                    return
                elif response == "alive\n":
                    self.server.send("LOOK\n")
                    response = self.server.recv()
                    if response == "ok\n":
                        response = self.server.recv()
                        if response == "ko\n":
                            return
                    else:
                        return

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
