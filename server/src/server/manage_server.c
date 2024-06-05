/*
** EPITECH PROJECT, 2024
** server
** File description:
** manage_server
*/

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "server.h"

static void accept_new_client(server_t *server)
{
    int new_socket = 0;
    struct sockaddr_in *address;
    int addrlen = sizeof(struct sockaddr);
    client_t *new_client = NULL;

    if (!FD_ISSET(server->socket, &server->select_config->readfds))
        return;
    address = calloc(sizeof(struct sockaddr_in), 1);
    if (address == NULL)
        return;
    new_socket = accept(server->socket, (struct sockaddr *)address,
                        (socklen_t *)&addrlen);
    if (new_socket == -1)
        return free(address);
    server->select_config->max_fd = (server->select_config->max_fd <
                                     new_socket) ? new_socket : server->select_config->max_fd;
    new_client = create_client(new_socket);
    add_client_to_list(server->pending_clients, new_client);
    free(address);
}

void manage_server(server_t *server)
{
    if (FD_ISSET(server->socket, &server->select_config->readfds)) {
        accept_new_client(server);
    }

}
