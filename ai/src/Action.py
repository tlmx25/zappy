class Action:
    def __init__(self, command, server):
        self.command = command
        self.server = server

    def deplacement(self, look_response, inventory, needed_resource):
        count = 0
        size = 3
        forward = 0
        position = 0

        tab = look_response.split(",")
        for i in tab:
            if needed_resource in i:
                break
            count += 1

        if count == 0:
            return
        for i in range(0, count):
            forward += 1
            if count >= size:
                count -= size
                size += 2
            else:
                break

        while forward != 0:
            self.command.mooveForward()
            forward -= 1

        position = size // 2
        if count < position:
            self.command.mooveRight()
            while count != position:
                self.command.mooveForward()
                count += 1

        elif count > position:
            self.command.mooveLeft()
            while count != position:
                self.command.mooveForward()
                count -= 1

    def take_object(self, objects):
        self.command.takeObject(objects)

    def assemble(self):
        pass

    def found_resource(self):
        pass

    def elevation(self):
        pass