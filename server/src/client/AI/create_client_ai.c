/*
** EPITECH PROJECT, 2024
** server
** File description:
** create_client_ai
*/

#include <stdlib.h>
#include "client_ai.h"
#include "my.h"

static void init_client_ai(client_ai_t *client)
{
    client->action = -1;
    client->TTEA = 0;
    client->inventory.food = 9;
    client->inventory.linemate = 0;
    client->inventory.deraumere = 0;
    client->inventory.sibur = 0;
    client->inventory.mendiane = 0;
    client->inventory.phiras = 0;
    client->inventory.thystame = 0;
    client->to_disconnect = 0;
}

client_ai_t *create_client_ai(int fd, char *team_name, position_t position)
{
    static int num_player = 0;
    client_ai_t *client = malloc(sizeof(client_ai_t));

    if (client == NULL)
        return NULL;
    client->fd = fd;
    client->team_name = my_strdup(team_name);
    client->num_player = num_player;
    num_player++;
    client->buff_in = NULL;
    client->buff_out = NULL;
    client->next = NULL;
    client->prev = NULL;
    client->position = position;
    client->level = 1;
    client->TTL = 126;
    init_client_ai(client);
    return client;
}

void add_client_ai_to_list(client_ai_list_t *list, client_ai_t *client)
{
    if (list == NULL || client == NULL)
        return;
    if (list->head == NULL) {
        list->head = client;
        list->tail = client;
        list->size = 1;
    } else {
        list->tail->next = client;
        client->prev = list->tail;
        list->tail = client;
        list->size++;
    }
}

client_ai_list_t *create_client_ai_list(void)
{
    client_ai_list_t *list = malloc(sizeof(client_ai_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void create_add_client_ai(client_ai_list_t *list, int fd, char *team_name,
    position_t position)
{
    client_ai_t *client = create_client_ai(fd, team_name, position);

    if (client == NULL)
        return;
    add_client_ai_to_list(list, client);
}
