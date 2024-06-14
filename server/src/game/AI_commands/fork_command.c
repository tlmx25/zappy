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

    position.direction = rand() % 4;
    create_add_egg_to_list(server->world->eggs, position, client->team_name);
    add_to_buffer(&client->buff_out, "ok\n", false);
    debug_print("Ai : %i, fork a player at {%i, %i, %c}\n", client->num_player,
    position.x, position.y, get_direction_char(position.direction));
}
