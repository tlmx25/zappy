##
## EPITECH PROJECT, 2023
## zappy
## File description:
## FlagParser.py
##

class FlagParser:
    """
    The FlagParser class is used to parse flag arguments at program startup. It retrieves values and prevents
    errors in the arguments.
    """

    def __init__(self, ac, av):
        """
        Init class values.
        @param ac: number of arguments at ai execution.
        @type ac: int
        @param av: list of arguments [-h, 127.0.0.1, ...]
        @param av: list
        @return: None
        """
        self.ac = ac
        self.av = av
        self.host = "localhost"
        self.port = 0
        self.team = ""
    
    def get_host(self) -> str:
        """
        Return host contained in FlragParser.
        @return : host
        @rtype : str
        """
        return self.host
    
    def set_host(self, host):
        """
        Define new host in FlagParser class
        @param host : New host to set
        @type host : str
        @return : None
        """
        self.host = host

    def get_port(self) -> int:
        """
        Return port contained in FlragParser.
        @return : port
        @rtype : int
        """
        return self.port
    
    def set_port(self, port):
        """
        Define new port in FlagParser class
        @param port : New port to set
        @type port : int
        @return : None
        """
        self.port = int(port)
    
    def get_team(self) -> str:
        """
        Return team contained in FlragParser.
        @return : team
        @rtype : str
        """
        return self.team
    
    def set_team(self, team):
        """
        Define new team in FlagParser class
        @param team : New team to set
        @type team : str
        @return : None
        """
        self.team = team
    
    def display_help(self):
        """
        Display how to use zappy_ai.
        @return: Boolean to indicate the program to exit if False
        @rtype: Bool
        """
        print("USAGE : ./zappy_ai -p port -n name -h machine")
        return False
        
    def parse_flag(self):
        """
        Parse flag given in argv at ai starting to define flag values (host, port, team) and prevent
        from flag error.
        @return : False to exit 84 or True to continue
        @rtype : Bool
        """
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