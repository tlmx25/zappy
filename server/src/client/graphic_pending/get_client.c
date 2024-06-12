/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_client
*/

#include <stdlib.h>
#include "client.h"

client_t *get_client_by_fd(client_list_t *list, int fd)
{
    client_t *tmp = list->head;

    for (; tmp != NULL && tmp->fd != fd; tmp = tmp->next);
    return tmp;
}

void client_is_converted(client_list_t  *list, client_t *client)
{
    if (client == NULL)
        return;
    delete_client_from_list(list, client, 0);
    if (client->buffer_in != NULL)
        free(client->buffer_in);
    if (client->buffer_out != NULL)
        free(client->buffer_out);
    free(client);
}
