##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ITrantor.py
##

from abc import ABC, abstractmethod
from ai.src.FlagParser import FlagParser

class ITrantor(ABC):
    """
    An interface that defines the required methods for any class implementing this interface.
    """
    
    @abstractmethod
    def receive(self) -> str:
        """
        Receive a message from server and parse message : death, incantation, messages, cmd.
        @return: command response or None
        @rtype: str
        """
        pass
    
    @abstractmethod
    def send(self, command : str) -> str:
        """
        Send a command to the server and get response.
        @param command: The command to be sent.
        @type command: str
        @return: response of the command.
        @rtype: str
        """
        pass

    @abstractmethod
    def move_forward(self) -> str:
        """
        Send forward command to server.
        @return: response of the command (ok/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def move_left(self) -> str:
        """
        Sends commands to the server to turn left and move forward.
        @return: server response (ok/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def turn_left(self) -> str:
        """
        Sends commands to the server to turn left.
        @return: server response (ok/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def move_right(self) -> str:
        """
        Sends commands to the server to turn right and move forward.
        @return: server response (ok/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def turn_right(self) -> str:
        """
        Sends commands to the server to turn right.
        @return: server response (ok/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def move_behind(self) -> str:
        """
        Sends commands to the server to turn 2 times right and move forward.
        @return: server response.
        @rtype: str
        """
        pass
    
    @abstractmethod
    def take_object(self, object: str) -> str:
        """
        Sends commands to the server to take an object on the tile.
        @param object: object to take (food, linemate, ...)
        @type object: str
        @return: server response (ok/ko/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def look(self) -> dict:
        """
        Sends commands to the server to get informations in our vision field (player, ressources, ...)
        @return: content in our vision field -> {0 : {player : 0, food : 0, ...}, ...}
        @rtype: dict
        """
        pass

    @abstractmethod
    def inventory(self) -> str:
        """
        Sends commands to the server to get informations on our ressources (food, minerals) and update
        trantor_inventory.
        @return: server response (inventory/dead)
        @rtype: str
        """
        pass
    
    @abstractmethod
    def broadcast(self, message : str) -> str:
        """
        Sends commands to the server to send message to all players.
        @param message: message to send.
        @type message: str
        @return: server response (ok/ko/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def set_object(self, object : str) -> str:
        """
        Sends commands to lay on object on the ground.
        @param object: object to drop.
        @type object: str
        @return: server response (ok/ko/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def incantation(self) -> str:
        """
        Sends commands to start an incantation.
        @return: server response (Elevation - Level/ko/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def fork(self) -> str:
        """
        Sends commands to create a new slot for the team.
        @return: server response (ok/ko/dead).
        @rtype: str
        """
        pass
    
    @abstractmethod
    def eject(self) -> str:
        """
        Sends commands to eject player that are on the same tile.
        @return: server response (ok/ko/dead).
        @rtype: str
        """
        pass

    @abstractmethod
    def connect_nbr(self):
        """
        Send commands to update team free slots.
        @return None
        """
        pass

    @abstractmethod
    def run(self):
        """
        Starting point for AI instructions.
        @return: None
        """
        pass
    
    @abstractmethod
    def set_starting_data(self, parser: FlagParser):
        """
        Function use to set starting data for AI when sending team (map + slots)
        @param parser: arg parser that contains team name (only for main program)
        @param type: FlagParser
        @return: None
        """
        pass