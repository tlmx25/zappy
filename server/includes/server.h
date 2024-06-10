/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/


#ifndef SERVER_SERVER_H
    #define SERVER_SERVER_H
    #define ERROR 84
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "option.h"
    #include "client.h"
    #include "client_ai.h"
    #include "management_socket.h"

typedef enum {
    false,
    true
} bool_t;

typedef struct server_s {
    bool_t is_running;
    int port;
    int socket;
    select_t *select_config;
    client_list_t *pending_clients;
    client_list_t *graphic_clients;
    client_ai_list_t *ai_clients;
    option_t *option;
} server_t;

typedef struct command_s {
    char *command;
    void (*func)(server_t *server, client_t *client, char const **command);
    int nb_args;
} command_t;

/**
 * @brief read message from a socket
 * @param fd fd of the socket
 * @return char* containing the message or NULL if error
 */
char *read_socket(int fd);

/**
 * @brief write message to a socket
 * @param fd fd of the socket
 * @param str message to write
 * @return int 0 if success, 84 if error
 */
int write_socket(int fd, char *str);

/**
 * @brief Create a new server and parse option
 * @param av information from the command line (option)
 * @return server_t* the server or NULL if error
 */
server_t *create_server(char **av)

/**
 * @brief Delete a server
 *
 * @param server server to delete
 */
void delete_server(server_t *server);

/**
 * @brief run the server
 * @param server server to run
 */
void run_server(server_t *server);

/**
 * @brief manage server, read and write on socket of client and
 * accept new client
 * @param server server to manage
 */
void manage_server(server_t *server);

/**
 * @brief check if name is in team list
 * @param server the server containing option
 * @param team_name the name of the team to check
 * @return int , 1 if the team exist or 0 if not
 */
int check_team_name(server_t *server, char *team_name);

#endif //SERVER_SERVER_H
