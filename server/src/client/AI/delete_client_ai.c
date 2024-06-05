/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_client_ai
*/

#include "server.h"
#include "client_ai.h"

void delete_client_ai(client_ai_t *client)
{
    if (client == NULL)
        return;
    if (client->team_name)
        free(client->team_name);
    if (client->buff_in)
        free(client->buff_in);
    if (client->buff_out)
        free(client->buff_out);
    if (client->action)
        free(client->action);
    free(client);
}

void delete_client_from_ai_list(client_ai_list_t *list, client_ai_t *client,
    int delete_client_bool)
{
    client_ai_t *tmp = list->head;

    for(; tmp != NULL && tmp != client; tmp = tmp->next);
    if (tmp == NULL)
        return;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp == list->head)
        list->head = tmp->next;
    if (tmp == list->tail)
        list->tail = tmp->prev;
    if (delete_client_bool)
        delete_client_ai(tmp);
}

void clear_client_ai_list(client_ai_list_t *list)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        delete_client_ai(tmp);
        tmp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_client_ai_list(client_ai_list_t *list)
{
    clear_client_ai_list(list);
    free(list);
}

void delete_client_ai_by_num(client_ai_list_t *list, int num)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->num_player == num) {
            delete_client_from_ai_list(list, tmp, 1);
            return;
        }
        tmp = next;
    }
}
