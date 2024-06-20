/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_client
*/

#include "client.h"

client_t *get_client_by_fd(client_list_t *list, int fd)
{
    client_t *tmp = list->head;

    for (; tmp != NULL && tmp->fd != fd; tmp = tmp->next);
    return tmp;
}
