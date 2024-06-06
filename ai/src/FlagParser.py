##
## EPITECH PROJECT, 2023
## zappy
## File description:
## FlagParser.py
##

class FlagParser:
    def __init__(self, ac, av):
        self.ac = ac
        self.av = av
        self.host = "localhost"
        self.port = 0
        self.team = ""
    
    def get_host(self) -> str:
        return self.host
    
    def set_host(self, host):
        self.host = host

    def get_port(self) -> int:
        return self.port
    
    def set_port(self, port):
        self.port = int(port)
    
    def get_team(self) -> str:
        return self.team
    
    def set_team(self, team):
        self.team = team
    
    def display_help(self):
        print("USAGE : ./zappy_ai -p port -n name -h machine")
        return False
        
    def parse_flag(self):
        if (self.ac == 2 and self.av[1] == "-help"):
            self.display_help()
            exit(0)
        if (self.ac < 5 or (self.ac % 2 != 1 and self.ac >= 5)):
            return self.display_help()
        if not "-p" in self.av or not "-n" in self.av:
            return self.display_help()
        for i in range(1, len(self.av), 2):
            match self.av[i]:
                case "-p":
                    self.set_port(self.av[i + 1])
                case "-n":
                    self.set_team(self.av[i + 1])
                case "-h":
                    self.set_host(self.av[i + 1])
                case _:
                    return self.display_help()
        return True  

#To check parser result : print("Parser result {Port : " + str(self.port) + " Host : " + self.host + " Team : " + self.team + "}")