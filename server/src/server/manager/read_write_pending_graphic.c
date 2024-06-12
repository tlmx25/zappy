/*
** EPITECH PROJECT, 2024
** server
** File description:
** manage_pending_graphic
*/

#include "server.h"

void read_pending_graphic_list(server_t *server, client_list_t *list)
{
    client_t *tmp = list->head;
    client_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (FD_ISSET(tmp->fd, &server->select_config->readfds))
            tmp->buffer_in = read_socket(tmp->fd);
        tmp = next;
    }
}

void write_pending_graphic_list(server_t *server, client_list_t *list)
{
    client_t *tmp = list->head;
    client_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->buffer_out != NULL && FD_ISSET(tmp->fd,
        &server->select_config->writefds)) {
            write_socket(tmp->fd, tmp->buffer_out);
            free(tmp->buffer_out);
            tmp->buffer_out = NULL;
        }
        tmp = next;
    }
}
