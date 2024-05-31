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
    #include "client.h"
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
    client_list_t *ai_clients;
} server_t;

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
 * @brief Create a new server
 *
 * @param port port of the server
 * @return server_t*
 */
server_t *create_server(int port);

/**
 * @brief Delete a server
 *
 * @param server server to delete
 */
void delete_server(server_t *server);
#endif //SERVER_SERVER_H
