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

typedef struct command_ai_s {
    char *command;
    size_t TTEA;
    void (*func)(server_t *server, client_ai_t *client);
} command_ai_t;

/**
 * @brief execute the forward command
 *
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void forward_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the left command
 *
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void left_command(server_t *server, client_ai_t *client);

/**
 * @brief execute the right command
 *
 * @param server struct containing server infos
 * @param client client who sent the command
 */
void right_command(server_t *server, client_ai_t *client);

/**
 * @brief execute connect_nbr command (return the number of eggs of the team)
 * @param server server for infos about the game
 * @param client client who sent the command
 */
void connect_nbr_command(server_t *server, client_ai_t *client);

/**
 * @brief execute Inventory command
 * @param server server for infos about the game
 * @param client client who sent the command
 */
void inventory_command(server_t *server, client_ai_t *client);

/**
 * @brief convert direction to char
 * @param direction direction to convert
 * @return direction char (N, E, S, W)
 */
char get_direction_char(direction_t direction);

/**
 * @brief execute fork command
 * @param server server for info about the game
 * @param client client who sent the command
 */
void fork_command(server_t *server, client_ai_t *client);
#endif //SERVER_COMMANDS_AI_H
