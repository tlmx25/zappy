##
## EPITECH PROJECT, 2023
## zappy
## File description:
## ITrantor.py
##

from abc import ABC, abstractmethod
from src.FlagParser import FlagParser

class ITrantor(ABC):
    
    # Gestion de messages
    
    @abstractmethod
    def receive(self):
        pass
    
    @abstractmethod
    def send(self, command : str):
        pass
    
    #Commandes
    
    @abstractmethod
    def move_forward(self) -> str:
        pass
    
    @abstractmethod
    def move_left(self) -> str:
        pass
    
    @abstractmethod
    def turn_left(self) -> str:
        pass
    
    @abstractmethod
    def move_right(self) -> str:
        pass
    
    @abstractmethod
    def turn_right(self) -> str:
        pass
    
    @abstractmethod
    def move_behind(self) -> str:
        pass
    
    @abstractmethod
    def take_object(self, object: str) -> str:
        pass
    
    @abstractmethod
    def look(self) -> dict:
        pass

    @abstractmethod
    def inventory(self) -> str:
        pass
    
    @abstractmethod
    def broadcast(self, message : str) -> str:
        pass
    
    @abstractmethod
    def set_object(self, object : str) -> str:
        pass
    
    @abstractmethod
    def incantation(self) -> str:
        pass
    
    @abstractmethod
    def fork(self) -> str:
        pass
    
    @abstractmethod
    def eject(self) -> str:
        pass

    # IA

    @abstractmethod
    def run(self):
        pass
    
    @abstractmethod
    def set_starting_data(self, parser: FlagParser):
        pass