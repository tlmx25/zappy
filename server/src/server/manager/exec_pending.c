/*
** EPITECH PROJECT, 2024
** server
** File description:
** exec_pending
*/

#include "server.h"

void exec_pending(server_t *server)
{
    for (client_t *tmp = server->pending_clients->head; tmp; tmp = tmp->next) {
        if (tmp->buffer_in != NULL) {
            manage_pending_client(server, tmp);
        }
    }
}
