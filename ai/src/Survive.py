from Action import Action

resources_needed = {
    1: {"nb_players": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    2: {"nb_players": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    3: {"nb_players": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    4: {"nb_players": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    5: {"nb_players": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    6: {"nb_players": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    7: {"nb_players": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}
resource_density = {
    "food": 0.5,
    "linemate": 0.3,
    "deraumere": 0.15,
    "sibur": 0.1,
    "mendiane": 0.1,
    "phiras": 0.08,
    "thystame": 0.05
}


class Survive:
    def __init__(self, command, server, level):
        self.needFood = False
        self.action = Action(command)
        self.command = command
        self.server = server
        self.level = level

    def parse_inventory(self, inventory):
        items = inventory[1:-1].split(", ")
        inventory_dict = {}
        for item in items:
            resource, quantity = item.split()
            inventory_dict[resource] = int(quantity)
        return inventory_dict

    def need_food(self, inventory):
        food_amount = int(inventory.split(",")[0].split()[1])
        if food_amount < 10:
            self.needFood = True
            return True
        self.needFood = False
        return False

    def what_i_need(self, inventory):

        rarest_resource = None

        if self.needFood:
            return "food"
        else:
            for resource, density in sorted(resource_density.items(), key=lambda item: item[1]):
                if inventory[resource] < resources_needed[self.level][resource]:
                    rarest_resource = resource
                    break

            return rarest_resource

    def search_resources(self, inventory_response):
        inventory = self.parse_inventory(inventory_response)
        look_response = self.command.look()
        needed_resource = self.what_i_need(inventory)
        if needed_resource:
            self.action.deplacement(look_response, inventory, needed_resource)
        # la réponse de la commande look est une liste de cases de la forme [player, food,,,], la vision change en fonction du niveau d'élévation du joueur
        # on peut donc déterminer la position des ressources en fonction de l'emplacement dans le tableau
        # a chaque élévation le joueur voit plus loin et plus large
        # on peut donc déterminer les ressources à proximité et se déplacer vers elles

    def perform_incantation(self, inventory, level):
        current_resources = self.parse_inventory(inventory)
        if all(current_resources[res] >= qty for res, qty in resources_needed[level].items()):
            return self.server.send("Incantation")
        return None
