/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init_game.c
*/

#include <string.h>
#include "server.h"
#include "world.h"

static bool init_map(server_t *server)
{
    int *object_ptr = 0;

    server->world->tiles = malloc(sizeof(tile_t) * server->option->width *
        server->option->height);
    if (server->world->tiles == NULL)
        return false;
    for (int i = 0; i < server->option->width * server->option->height; i++) {
        server->world->tiles[i].coordinate.x = i % server->option->width;
        server->world->tiles[i].coordinate.y = i / server->option->width;
        server->world->tiles[i].coordinate.direction = NONE;
        object_ptr = (int*)&server->world->tiles[i].object;
        for (size_t j = 0; j < sizeof(inventory_t) / sizeof(int); j++)
            object_ptr[j] = 0;
        server->world->tiles[i].egg = false;
        server->world->tiles[i].ai = 0;
    }
    return true;
}

static bool team_init(server_t *server)
{
    int nbr_teams = 0;

    for (nbr_teams = 0; server->option->names[nbr_teams] != NULL; nbr_teams++);
    server->world->teams = malloc(sizeof(team_t) * nbr_teams);
    if (server->world->teams == NULL)
        return (false);
    for (int i = 0; i < nbr_teams; i++) {
        server->world->teams[i].name = strdup(server->option->names[i]);
        server->world->teams[i].max_clients = server->option->clients_nb;
        server->world->teams[i].current_clients = 0;
    }
    return true;
}

bool init_game(server_t *server)
{
    server->world = malloc(sizeof(world_t));
    if (server->world == NULL)
        return false;
    if (init_map(server) == false)
        return false;
    if (team_init(server) == false)
        return false;
    return true;
}