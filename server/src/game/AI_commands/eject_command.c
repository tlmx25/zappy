/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject_command.c
*/

#include "server.h"
#include "commands_ai.h"

static void ai_ejection(server_t *server, client_ai_t *em,
    client_ai_t *rc)
{
    position_t new_pos = em->position;

    new_pos = get_next_position(server, new_pos);
    new_pos.direction = rc->position.direction;
    rc->position = new_pos;
}

static void send_eject(server_t *server, client_ai_t *em, client_ai_t *rc)
{
    char buffer[1024] = {0};
    int dir = get_dir(em, rc);

    snprintf(buffer, 1024, "eject: %i\n", dir);
    add_to_buffer(&rc->buff_out, buffer, false);
    send_to_all_graphic_arg(server->graphic_clients,
    "ppo %i %i %i %i\n", rc->num_player, rc->position.x,
    rc->position.y, rc->position.direction + 1);
}

void verif_ai(server_t *server, client_ai_t *client)
{
    client_ai_t *tmp_ai = server->ai_clients->head;
    int x = client->position.x;
    int y = client->position.y;

    for (; tmp_ai != NULL; tmp_ai = tmp_ai->next)
        if ((tmp_ai->position.x == x) && (tmp_ai->position.y == y) &&
            tmp_ai != client) {
            ai_ejection(server, client, tmp_ai);
            debug_print(
            "Client AI %i has been ejected by client AI %i {%i, %i, %c}\n",
                tmp_ai->num_player, client->num_player, tmp_ai->position.x,
                tmp_ai->position.y,
                get_direction_char(tmp_ai->position.direction));
            send_eject(server, client, tmp_ai);
        }
}

static void verif_egg(server_t *server, client_ai_t *client)
{
    egg_t *tmp_egg = server->world->eggs->head;
    int x = client->position.x;
    int y = client->position.y;

    for (; tmp_egg != NULL; tmp_egg = tmp_egg->next)
        if ((tmp_egg->pos.x == x) && (tmp_egg->pos.y == y)) {
            debug_print("Egg %i has been destruct by client AI %i\n",
                tmp_egg->id, client->num_player);
            send_to_all_graphic_arg(server->graphic_clients, "edi %i\n",
                tmp_egg->id);
            delete_egg_from_list(server->world->eggs, tmp_egg, true);
        }
}

void eject_command(server_t *server, client_ai_t *client)
{
    verif_ai(server, client);
    verif_egg(server, client);
    send_to_all_graphic_arg(server->graphic_clients, "pex %i\n",
    client->num_player);
    return add_to_buffer(&client->buff_out, "ok\n", false);
}
