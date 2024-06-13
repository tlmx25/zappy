/*
** EPITECH PROJECT, 2024
** server
** File description:
** exec_ai
*/

#include "server.h"

static const command_ai_t commands[] = {

    {NULL, NULL}
};

static int check_death(server_t *server, client_ai_t *tmp)
{
    tmp->TTL--;
    tmp->TTL = (tmp->TTL <= 0) ? 0 : tmp->TTL;
    if (tmp->TTL == 0) {
        if (tmp->inventory.food != 0) {
            tmp->inventory.food--;
            debug_print("Client AI %i TTL has %i food left\n",
            tmp->num_player, tmp->inventory.food);
            tmp->TTL = 126;
        } else {
            add_to_buffer(&tmp->buff_out, "dead\n", false);
            send_to_all_graphic_arg(server->graphic_clients, "pdi %i\n",
            tmp->num_player);
            debug_print("Client AI %i is dead\n", tmp->num_player);
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
