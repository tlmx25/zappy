/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** graphique_cmd.h
*/

#ifndef GRAPHIQUE_CMD_H
    #define GRAPHIQUE_CMD_H
    #include "server.h"

/**
 * @brief send the size of the map to the client
 * @param server the server
 * @param client the client
 * @param command the command msz with no arguments
 */
void cmd_msz(server_t *server, client_t *client, char const **command);

/**
 * @brief send the content of a tile to the client
 * @param server the server
 * @param client the client
 * @param command the command bct with the arguments X Y
 */
void cmd_bct(server_t *server, client_t *client, char const **command);

/**
 * @brief send the content of all the tiles to the client
 * @param server the server
 * @param client the client
 * @param command the command mct with no arguments
 */
void cmd_mct(server_t *server, client_t *client, char const **command);

#endif // GRAPHIQUE_CMD_H
