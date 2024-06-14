/*
** EPITECH PROJECT, 2024
** server
** File description:
** fork_command
*/

#include "commands_ai.h"

void fork_command(server_t *server, client_ai_t *client)
{
    position_t position = client->position;
    egg_t *egg;

    position.direction = rand() % 4;
    egg = create_egg(position, client->team_name);
    if (egg == NULL)
        return;
    add_egg_to_list(server->world->eggs, egg);
    add_to_buffer(&client->buff_out, "ok\n", false);
    debug_print("Ai : %i, fork an egg at {%i, %i, %c}\n", client->num_player,
    position.x, position.y, get_direction_char(position.direction));
    send_to_all_graphic_arg(server->graphic_clients, "enw %i %i %i %i\n",
    egg->id, client->num_player, position.x, position.y);
}

void prefork_command(server_t *server, client_ai_t *client)
{
    debug_print("AI : %i, started fork an egg at {%i, %i, %c}\n",\
    client->num_player, client->position.x, client->position.y,
    get_direction_char(client->position.direction));
    send_to_all_graphic_arg(server->graphic_clients, "pfk %i\n",
    client->num_player);
}
