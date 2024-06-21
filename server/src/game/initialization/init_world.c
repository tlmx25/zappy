/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init_world.c
*/

#include <time.h>
#include "server.h"
#include "world.h"

static void second_repartion_ressources(server_t *server,
    inventory_t *inventory, int i, int r_to_spawn)
{
    if (r_to_spawn == 4 && inventory->mendiane > 0) {
        server->world->tiles[i].object.mendiane++;
        inventory->mendiane--;
    }
    if (r_to_spawn == 5 && inventory->phiras > 0) {
        server->world->tiles[i].object.phiras++;
        inventory->phiras--;
    }
    if (r_to_spawn == 6 && inventory->thystame > 0) {
        server->world->tiles[i].object.thystame++;
        inventory->thystame--;
    }
}

static void repartion_ressources(server_t *server, inventory_t *inventory,
    int i, int r_to_spawn)
{
    if (r_to_spawn == 0 && inventory->food > 0) {
        server->world->tiles[i].object.food++;
        inventory->food--;
    }
    if (r_to_spawn == 1 && inventory->linemate > 0) {
        server->world->tiles[i].object.linemate++;
        inventory->linemate--;
    }
    if (r_to_spawn == 2 && inventory->deraumere > 0) {
        server->world->tiles[i].object.deraumere++;
        inventory->deraumere--;
    }
    if (r_to_spawn == 3 && inventory->sibur > 0) {
        server->world->tiles[i].object.sibur++;
        inventory->sibur--;
    }
    second_repartion_ressources(server, inventory, i, r_to_spawn);
}

static void init_ressources(inventory_t *inventory, server_t *server)
{
    inventory->food = server->option->width * server->option->height * 0.5;
    inventory->linemate = server->option->width * server->option->height * 0.3;
    inventory->deraumere = server->option->width *
        server->option->height * 0.15;
    inventory->sibur = server->option->width * server->option->height * 0.1;
    inventory->mendiane = server->option->width * server->option->height * 0.1;
    inventory->phiras = server->option->width * server->option->height * 0.08;
    inventory->thystame = server->option->width *
        server->option->height * 0.05;
}

static void stabilize_ressources(inventory_t *inventory, server_t *server)
{
    for (int i = 0; i < server->option->width * server->option->height; i++) {
        inventory->food -= server->world->tiles[i].object.food;
        inventory->linemate -= server->world->tiles[i].object.linemate;
        inventory->deraumere -= server->world->tiles[i].object.deraumere;
        inventory->sibur -= server->world->tiles[i].object.sibur;
        inventory->mendiane -= server->world->tiles[i].object.mendiane;
        inventory->phiras -= server->world->tiles[i].object.phiras;
        inventory->thystame -= server->world->tiles[i].object.thystame;
    }
}

void distribute_ressources_meteor(server_t *server)
{
    inventory_t inventory = {0};
    int i = 0;
    int r_to_spawn = 0;

    debug_print("Distribute ressources meteor shower\n");
    init_ressources(&inventory, server);
    stabilize_ressources(&inventory, server);
    srand(time(NULL));
    debug_print("food: %i linemate: %i deraumere: %i sibur: %i mendiane: %i phiras: %i thystame: %i\n",
        inventory.food, inventory.linemate, inventory.deraumere, inventory.sibur,
        inventory.mendiane, inventory.phiras, inventory.thystame);
    while (inventory.food > 0 || inventory.linemate > 0 || inventory.deraumere
        > 0 || inventory.sibur > 0 || inventory.mendiane > 0 ||
        inventory.phiras > 0 || inventory.thystame > 0) {
        i = rand() % (server->option->width * server->option->height);
        r_to_spawn = rand() % 7;
        repartion_ressources(server, &inventory, i, r_to_spawn);
    }
}

void distribute_ressources(server_t *server)
{
    inventory_t inventory = {0};
    int i = 0;
    int r_to_spawn = 0;

    debug_print("Distribute ressources on map\n");
    init_ressources(&inventory, server);
    srand(time(NULL));
    while (inventory.food > 0 || inventory.linemate > 0 || inventory.deraumere
        > 0 || inventory.sibur > 0 || inventory.mendiane > 0 ||
        inventory.phiras > 0 || inventory.thystame > 0) {
        i = rand() % (server->option->width * server->option->height);
        r_to_spawn = rand() % 7;
        repartion_ressources(server, &inventory, i, r_to_spawn);
    }
}

bool init_world(server_t *server)
{
    int *object_ptr = 0;
    int i = 0;

    server->world->tiles = malloc(sizeof(tile_t) * server->option->width *
        server->option->height);
    if (server->world->tiles == NULL)
        return false;
    for (i = 0; i < server->option->width * server->option->height; i++) {
        server->world->tiles[i].coordinate.x = i % server->option->width;
        server->world->tiles[i].coordinate.y = i / server->option->width;
        server->world->tiles[i].coordinate.direction = NONE;
        object_ptr = (int *)&server->world->tiles[i].object;
        for (size_t j = 0; j < sizeof(inventory_t) / sizeof(int); j++)
            object_ptr[j] = 0;
        server->world->tiles[i].ai = 0;
    }
    distribute_ressources(server);
    return true;
}

bool delete_world(world_t *world)
{
    debug_print("Delete world\n");
    for (int i = 0; i < world->nbr_teams; i++)
        free(world->teams[i].name);
    free(world->teams);
    free(world->tiles);
    delete_eggs_list(world->eggs);
    free(world);
    return true;
}
