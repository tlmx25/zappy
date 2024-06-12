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

static void add_new_client(server_t *server, client_t *new_client)
{
    add_client_to_list(server->pending_clients, new_client);
    debug_print("New client connected fd: %i\n", new_client->fd);
}

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
    add_new_client(server, new_client);
    free(address);
}

static void read_list(server_t *server)
{
    read_pending_graphic_list(server, server->pending_clients);
    read_pending_graphic_list(server, server->graphic_clients);
    read_ai_list(server, server->ai_clients);
}

static void write_list(server_t *server)
{
    write_pending_graphic_list(server, server->pending_clients);
    write_pending_graphic_list(server, server->graphic_clients);
    write_ai_list(server, server->ai_clients);
}

static void exec_list(server_t *server)
{
    // exec_pending(server);
    exec_graphic_list(server);
}

void manage_server(server_t *server)
{
    if (FD_ISSET(server->socket, &server->select_config->readfds))
        accept_new_client(server);
    read_list(server);
    exec_list(server);
    write_list(server);
}
