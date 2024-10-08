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
void cmd_msz(server_t *server, client_t *client, char UNUSED const **command);

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
void cmd_mct(server_t *server, client_t *client, char UNUSED const **command);

/**
 * @brief send the position of a player to the client
 * @param server the server
 * @param client the client
 * @param command the command ppo with the arguments player_id
 */
void cmd_ppo(server_t *server, client_t *client, char const **command);

/**
 * @brief send the level of a player to the client
 * @param server the server
 * @param client the client
 * @param command the command plv with the arguments player_id
 */
void cmd_plv(server_t *server, client_t *client, char const **command);

/**
 * @brief send the inventory of a player to the client
 * @param server the server
 * @param client the client
 * @param command the command pin with the arguments player_id
 */
void cmd_pin(server_t *server, client_t *client, char const **command);

/**
 * @brief send the name of all the teams to the client
 * @param server the server
 * @param client the client
 * @param command the command tna with no arguments
 */
void cmd_tna(server_t *server, client_t *client, char UNUSED const **command);

/**
 * @brief send the time unit to the client
 * @param server the server
 * @param client the client
 * @param command the command sgt with no arguments
 */
void cmd_sgt(server_t *server, client_t *client, char UNUSED const **command);

/**
 * @brief modify the time unit of the server, and send it to the client
 * @param server the server
 * @param client the client
 * @param command the command sst with the new time unit
 */
void cmd_sst(server_t *server, client_t *client, char const **command);

/*
 * @brief send all the egg on the map to the client with enw
 * @param server the server
 * @param client the client
 */
void enw_all_egg(server_t *server, client_t *client);

/**
 * @brief
 * @param client
 * @param response
 * @param player_id
 * @return
 */
char *cmd_pin_create_response(client_ai_t *client, char *response,
    int player_id);
#endif // GRAPHIQUE_CMD_H
