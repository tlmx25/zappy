/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_server
*/

#include "server.h"

void delete_server(server_t *server)
{
    if (server == NULL)
        return;
    close(server->socket);
    if (server->graphic_clients)
        delete_client_list(server->graphic_clients);
    if (server->ai_clients)
        delete_client_ai_list(server->ai_clients);
    if (server->pending_clients)
        delete_client_list(server->pending_clients);
    if (server->select_config)
        free(server->select_config);
    if (server->option)
        delete_option(server->option);
    if (server->world)
        delete_world(server->world);
    free(server);
}
