class Broadcast:
    def __init__(self, server, action, Command):
        self.server = server
        self.command = Command
        self.action = action
        self.method_pointers = {
            "Assemble": action.assemble,
            "Resource": action.found_resource,
            "Elevation": action.elevation
        }
    def parse_broadcast(self, response):
        if 'Broadcast' in response:
            message = response.split(" ")[1]
            if message in self.method_pointers:
                return self.method_pointers[message]
        else:
            return None

    def broadcast(self, message):
        self.server.send("Broadcast " + message)
        while not self.server.check_read():
            pass
        response = self.server.recv()
        return self.parse_broadcast(response)