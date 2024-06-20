/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world.h
*/

#ifndef ZAPPY_WORLD_H
    #define ZAPPY_WORLD_H
    #include "server.h"
    #include "eggs.h"
    #include "incantation.h"

typedef struct egg_list_s egg_list_t;
typedef struct server_s server_t;

/**
* @brief A structure to represent a tile in the game world.
*
* This structure represents a tile in the game world. It contains the
 * coordinates of the tile,
* an inventory of objects on the tile, and the number of AI on the tile.
*/
typedef struct tile_s {
    position_t coordinate; /**< The coordinates of the tile in the
 * game world. */
    inventory_t object; /**< The inventory of objects on the tile. */
    size_t ai; /**< The number of AI on the tile. */
} tile_t;

/**
* @brief A structure to represent a team in the game.
*
* This structure represents a team in the game. It contains the name of the
 * team,
* the maximum number of clients that can join the team, and the current
 * number of clients in the team.
*/
typedef struct team_s {
    char *name; /**< The name of the team. */
    int max_clients; /**< The maximum number of clients that can join the
 * team. */
    int current_clients; /**< The current number of clients in the team. */
} team_t;

/**
* @brief A structure to represent the world in the game.
*
* This structure represents the world in the game. It contains the
 * number of teams,
* a pointer to the tiles in the world, a pointer to the teams in the world,
* a pointer to the list of eggs in the world, and a pointer to the list of
 * incantations in the world.
*/
typedef struct world_s {
    int nbr_teams; /**< The number of teams in the world. */
    tile_t *tiles; /**< A pointer to the tiles in the world. */
    team_t *teams; /**< A pointer to the teams in the world. */
    egg_list_t *eggs; /**< A pointer to the list of eggs in the world. */
    incantation_list_t *incantations; /**< A pointer to the list of
 * incantations in the world. */
} world_t;

/**
 * @brief Init the map of the game with the width and height of the server
 * @param server the server
 * @return bool true if the map is correctly initialized, false otherwise
 */
bool init_game(server_t *server);

/**
 * @brief Init all informations about the teams
 * @param server the server
 * @return bool true if the teams are correctly initialized, false otherwise
 */
bool team_init(server_t *server);

/**
 * @brief Init the world
 * @param server the server
 * @return bool true if the world is correctly initialized, false otherwise
 */
bool init_world(server_t *server);

/**
 * @brief Delete the world
 * @param world the world to delete
 * @return bool true if the world is correctly deleted, false otherwise
 */
bool delete_world(world_t *world);

/**
 * @brief finish the incantation
 * @param server server for info about the game
 * @param incantation incantation to finish
 */
void incantation_end(server_t *server, incantation_t *incantation);
#endif //ZAPPY_WORLD_H
