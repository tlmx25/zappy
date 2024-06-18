/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** object_command.c
*/

#include <string.h>
#include "server.h"

size_t getobject(char *object)
{
    if (strcmp(object, "food") == 0)
        return 0;
    if (strcmp(object, "linemate") == 0)
        return 1;
    if (strcmp(object, "deraumere") == 0)
        return 2;
    if (strcmp(object, "sibur") == 0)
        return 3;
    if (strcmp(object, "mendiane") == 0)
        return 4;
    if (strcmp(object, "phiras") == 0)
        return 5;
    if (strcmp(object, "thystame") == 0)
        return 6;
    return -1;
}

void take_command(server_t *server, client_ai_t *client)
{
    int x = client->position.x;
    int y = client->position.y;
    int i = 0;
    int obj = getobject(client->option);

    if (getobject(client->option) == -1)
        add_to_buffer();

}

void set_command(server_t *server, client_ai_t *client)
{
}
