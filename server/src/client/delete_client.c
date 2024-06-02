/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_client
*/

#include <stdlib.h>
#include <unistd.h>
#include "client.h"

void delete_client(client_t *client)
{
    if (client == NULL)
        return;
    close(client->fd);
    if (client->buffer_in != NULL)
        free(client->buffer_in);
    if (client->buffer_out != NULL)
        free(client->buffer_out);
    free(client);
}

void clear_client_list(client_list_t *list)
{
    client_t *tmp = list->head;
    client_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        delete_client(tmp);
        tmp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_client_list(client_list_t *list)
{
    clear_client_list(list);
    free(list);
}

void delete_client_from_list(client_list_t *list, client_t *client,
int delete_client_bool)
{
    client_t *tmp = list->head;

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
    list->size--;
    if (delete_client_bool)
        delete_client(tmp);
}

void delete_client_by_fd(client_list_t *list, int fd, int delete_client)
{
    client_t *tmp = list->head;
    client_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->fd == fd) {
            delete_client_from_list(list, tmp, delete_client);
            return;
        }
        tmp = next;
    }
}
