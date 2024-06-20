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

size_t count_client_ai_by_team_level(client_ai_list_t *ai, char *team_name,
    size_t level)
{
    client_ai_t *tmp = ai->head;
    int count = 0;

    while (tmp) {
        if (my_strcmp(tmp->team_name, team_name) == 0 &&
        tmp->level == level)
            count++;
        tmp = tmp->next;
    }
    return count;
}
