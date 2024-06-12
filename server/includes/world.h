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

typedef struct server_s server_t;

/**
 * @brief Init the map of the game with the width and height of the server
 * @param server the server
 * @return bool true if the map is correctly initialized, false otherwise
 */
bool init_game(server_t *server);

/**
 * @brief Delete the world
 * @param world the world to delete
 * @return bool true if the world is correctly deleted, false otherwise
 */
bool delete_world(world_t *world);

#endif //ZAPPY_WORLD_H
