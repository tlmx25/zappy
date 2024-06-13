/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init_game.c
*/

#include <string.h>
#include <time.h>
#include "server.h"
#include "world.h"

bool init_game(server_t *server)
{
    debug_print("Init game\n");
    server->world = malloc(sizeof(world_t));
    if (server->world == NULL)
        return false;
    if (init_world(server) == false)
        return false;
    if (team_init(server) == false)
        return false;
    return true;
}
