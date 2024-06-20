/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject_command.c
*/

#include "server.h"

static void ai_ejection(server_t *server, client_ai_t *client,
    direction_t direction)
{
    if (direction == NORTH)
        client->position.y = (client->position.y - 1) % server->option->height;
    if (direction == SOUTH)
        client->position.y = (client->position.y + 1) % server->option->height;
    if (direction == EAST)
        client->position.x = (client->position.x - 1) % server->option->width;
    if (direction == WEST)
        client->position.x = (client->position.x + 1) % server->option->width;
}

bool verif_ai(server_t *server, client_ai_t *client)
{
    direction_t direction = client->position.direction;
    client_ai_t *tmp_ai = server->ai_clients->head;
    int x = client->position.x;
    int y = client->position.y;

    for (; tmp_ai != NULL; tmp_ai = tmp_ai->next)
        if ((tmp_ai->position.x == x) && (tmp_ai->position.y == y) &&
            tmp_ai != client) {
            ai_ejection(server, tmp_ai, direction);
            debug_print("Client AI %i has been ejected by client AI %i\n",
                tmp_ai->num_player, client->num_player);
            add_to_buffer(&client->buff_out, "ok\n", false);
            return true;
        }
    return false;
}

bool verif_egg(server_t *server, client_ai_t *client)
{
    egg_t *tmp_egg = server->world->eggs->head;
    int x = client->position.x;
    int y = client->position.y;

    for (; tmp_egg != NULL; tmp_egg = tmp_egg->next)
        if ((tmp_egg->pos.x == x) && (tmp_egg->pos.y == y)) {
            debug_print("Egg %i has been destruct by client AI %i\n",
                tmp_egg->id, client->num_player);
            delete_egg_from_list(server->world->eggs, tmp_egg, true);
            add_to_buffer(&client->buff_out, "ok\n", false);
            return true;
        }
    return false;
}

void eject_command(server_t *server, client_ai_t *client)
{
    if (verif_ai(server, client) == true)
        return;
    if (verif_egg(server, client) == true)
        return;
    return add_to_buffer(&client->buff_out, "ko\n", false);
}
