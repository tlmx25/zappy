/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world.h
*/

#ifndef ZAPPY_WORLD_H
    #define ZAPPY_WORLD_H
    #include "server.h"

typedef struct tile_s {
    position_t coordinate;
    inventory_t object;
    bool egg;
    size_t ai;
} tile_t;

typedef struct team_s {
    char *name;
    int max_clients;
    int current_clients;
} team_t;

typedef struct world_s {
    tile_t *tiles;
    team_t *teams;
} world_t;

#endif //ZAPPY_WORLD_H
