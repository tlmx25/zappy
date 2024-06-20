/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_client_ai
*/

#include "server.h"

client_ai_t *get_client_ai_by_num(client_ai_list_t *ai, int id)
{
    client_ai_t *tmp = ai->head;

    while (tmp) {
        if (tmp->num_player == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
