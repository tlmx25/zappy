/*
** EPITECH PROJECT, 2024
** server
** File description:
** read_write_ai_client
*/

#include "server.h"

static void error_read(client_ai_t *tmp)
{
    tmp->buff_in = read_socket(tmp->fd);
    if (tmp->buff_in == NULL) {
        tmp->to_disconnect = true;
    }
}

void read_ai_list(server_t *server, client_ai_list_t *list)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (FD_ISSET(tmp->fd, &server->select_config->readfds)) {
            error_read(tmp);
        }
        tmp = next;
    }
}

void write_ai_list(server_t *server, client_ai_list_t *list)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->buff_out != NULL && FD_ISSET(tmp->fd,
        &server->select_config->writefds)) {
            write_socket(tmp->fd, tmp->buff_out);
            free(tmp->buff_out);
            tmp->buff_out = NULL;
        }
        if (tmp->to_disconnect == true) {
            debug_print("Client AI disconnected fd: %i\n", tmp->fd);
            delete_client_ai_from_list(list, tmp, true);
        }
        tmp = next;
    }
}
