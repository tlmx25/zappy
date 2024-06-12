/*
** EPITECH PROJECT, 2024
** server
** File description:
** exec_ai
*/

#include "server.h"

static int check_death(server_t *server, client_ai_t *tmp)
{
    tmp->TTL--;
    if (tmp->TTL == 0) {
        if (tmp->inventory.food != 0) {
            tmp->inventory.food--;
            tmp->TTL = 126;
        } else {
            add_to_buffer(&tmp->buff_out, "dead\n", false);
            return 1;
        }
    }
    return 0;
}

void exec_ai_list(server_t *server)
{
    client_ai_t *tmp = server->ai_clients->head;

    for (; tmp; tmp = tmp->next) {
        check_death(server, tmp);
    }
}
