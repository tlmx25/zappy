/*
** EPITECH PROJECT, 2024
** server
** File description:
** commands_ai
*/

#pragma once

#ifndef SERVER_COMMANDS_AI_H
    #define SERVER_COMMANDS_AI_H
    #include "server.h"
    #define OR rc->position.direction
    #define DIR(a, b, c, d) (OR == 0) ? a : (OR == 1) ? b : (OR == 2) ? c : d

/**
 * @brief command_ai structure
 *
 * the command_ai structure is used to store the information about the
 * commands that the AI can send
 */
typedef struct command_ai_s {
    char *command; /** i'ts string represent the command */
    size_t TTEA; /** time to execute the command */
    void (*func)(server_t *server, client_ai_t *client); /** function to
   execute at the end of TTEA*/
    void (*prefunc)(server_t *server, client_ai_t *client); /** function to
 * execute at the start of TTEA */
} command_ai_t;

/**
 * @brief incantation_requirements structure
 *
 * the incantation_requirements structure is used to store the information
 * about the requirements for the incantation
 */
typedef struct incantation_requirements_s {
    int players; /** number of players required */
    int linemate; /** linemate quantity */
    int deraumere; /** deraumere quantity */
    int sibur; /** sibur quantity */
    int mendiane; /** mendiane quantity */
    int phiras; /** phiras quantity */
    int thystame; /** thystame quantity */
} incantation_requirements_t;

/**
 * @brief execute the forward command, move the client depending on
 * the direction
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void forward_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the left command, change the direction of the client to left
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void left_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the right command, change the direction of the
 * client to right
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void right_command(server_t *server, client_ai_t *client);

/**
 * @brief execute connect_nbr command, send the number of free slots
 * @param server server for infos about the game
 * @param client client who sent the command
 */
void connect_nbr_command(server_t *server, client_ai_t *client);

/**
 * @brief execute Inventory command, send the inventory of the client
 * @param server server for infos about the game
 * @param client client who sent the command
 */
void inventory_command(server_t *server, client_ai_t *client);

/**
 * @brief convert direction to char, N, E, S, W
 * @param direction direction to convert
 * @return direction char (N, E, S, W)
 */
char get_direction_char(direction_t direction);

/**
 * @brief execute fork command, create a new egg
 * @param server server for info about the game
 * @param client client who sent the command
 */
void fork_command(server_t *server, client_ai_t *client);

/**
 * @brief excute prefork command for prevent graphic
 * @param server server for info
 * @param client client who sent command fork
 */
void prefork_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the look command, send the content of the tiles
 * @param server server for info about the game
 * @param client client who sent the command
 */
void look_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the take command, take an object from the tile
 * @param server server for info about the game
 * @param client client who sent the command
 */
void take_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the set command, set an object on the tile from the
 * client inventory
 * @param server server for info about the game
 * @param client client who sent the command
 */
void set_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the broadcast command, send a message to all clients with
 * the direction
 * @param server server for info about the game
 * @param client client who sent the command
 */
void broadcast_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the eject command, eject a client from the tile or
 * destroy an egg
 * @param server server for info about the game
 * @param client client who sent the command
 */
void eject_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the incantation command, start the incantation for
 * level up the player
 * @param server server for info about the game
 * @param client client who sent the command
 */
void incantation_precommand(server_t *server, client_ai_t *client);

/**
 * @brief check the requirement for incantation (level up)
 * @param tile tile where the incantation is
 * @param requirement requirement for the incantation
 * @param clients all clients
 * @param level level of the incantation
 * @return true if the incantation can be done, false otherwise
 */
bool check_requirement(tile_t *tile, client_ai_list_t *clients, size_t level);

/**
 * @brief transform an array of int to a string
 * @param array array of int
 * @return array in string format or NULL if error
 */
char *int_array_to_str(int *array);

/**
 * @brief remove the object from tile afet incantation and reset player
 * @param tile tile where the incantation is
 * @param requirement requirement for incantion for remove quatntity of object
 * @param client client who sent the incantation and his reset
 * @param clients list of client for send data to graphic client
 */
void remove_object(tile_t *tile, incantation_requirements_t *requirement,
    client_ai_t *client, client_list_t *clients);
#endif //SERVER_COMMANDS_AI_H
