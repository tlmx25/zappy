/*
** EPITECH PROJECT, 2024
** server
** File description:
** remove_tile_incant
*/

#include "commands_ai.h"

void remove_object(tile_t *tile, incantation_requirements_t *requirement,
    client_ai_t *client, client_list_t *clients)
{
    tile->object.linemate -= requirement->linemate;
    tile->object.deraumere -= requirement->deraumere;
    tile->object.sibur -= requirement->sibur;
    tile->object.mendiane -= requirement->mendiane;
    tile->object.phiras -= requirement->phiras;
    tile->object.thystame -= requirement->thystame;
    client->TTEA = 0;
    client->action = -1;
    client->level++;
    send_to_all_graphic_arg(clients,
    "bct %i %i %i %i %i %i %i %i %i\n", client->position.x,
    client->position.y, tile->object.food, tile->object.linemate,
    tile->object.deraumere, tile->object.sibur, tile->object.mendiane,
    tile->object.phiras, tile->object.thystame);
}

char *int_array_to_str(int *array)
{
    char buffer[4096] = {0};
    int index;

    if (array == NULL)
        return NULL;
    for (int i = 0; array[i] != -1; i++) {
        index = my_strlen(buffer);
        snprintf(buffer + index, 4096 - index, " %d", array[i]);
    }
    return my_strdup(buffer);
}
