/*
** EPITECH PROJECT, 2024
** server
** File description:
** create_client
*/

#include <stdlib.h>
#include "my.h"
#include "client.h"

client_t *create_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return NULL;
    client->fd = fd;
    client->buffer_in = NULL;
    client->buffer_out = my_strdup("WELCOME\n");
    client->next = NULL;
    client->prev = NULL;
    client->to_disconnect = 0;
    return client;
}

client_list_t *create_client_list(void)
{
    client_list_t *list = malloc(sizeof(client_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_client_to_list(client_list_t *list, client_t *client)
{
    if (list->head == NULL) {
        list->head = client;
        list->tail = client;
        client->next = NULL;
        client->prev = NULL;
    } else {
        list->tail->next = client;
        client->prev = list->tail;
        list->tail = client;
        client->next = NULL;
    }
    list->size++;
}

void create_add_client(client_list_t *list, int fd)
{
    client_t *client = create_client(fd);

    if (client == NULL)
        return;
    add_client_to_list(list, client);
}
