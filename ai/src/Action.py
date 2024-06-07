class Action:
    def __init__(self, command):
        self.command = command
        self.commandQueue = []

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
            self.commandQueue.append("Forward")
            forward -= 1

        position = size // 2
        if count < position:
            while count != position:
                self.command.mooveRight()
                self.commandQueue.append("Right")
                count += 1

        elif count > position:
            while count != position:
                self.command.mooveLeft()
                self.commandQueue.append("Left")
                count -= 1
        return self.commandQueue
