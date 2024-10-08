/*
** EPITECH PROJECT, 2024
** server
** File description:
** right_left_forward_command
*/

#include "commands_ai.h"

static void movement_notification(server_t *server, client_ai_t *client)
{
    char buff[2048];

    snprintf(buff, 2048, "ppo %i %i %i %i\n", client->num_player,
    client->position.x, client->position.y, client->position.direction + 1);
    send_to_all_graphic(server->graphic_clients, buff);
}

char get_direction_char(direction_t direction)
{
    if (direction == NORTH)
        return 'N';
    if (direction == EAST)
        return 'E';
    if (direction == SOUTH)
        return 'S';
    if (direction == WEST)
        return 'W';
    return 'N';
}

void right_command(UNUSED server_t *server, client_ai_t *client)
{
    client->position.direction = turn_right(client->position.direction);
    add_to_buffer(&client->buff_out, "ok\n", false);
    debug_print("Client AI %i turned right, new direction : %c\n",
    client->num_player, get_direction_char(client->position.direction));
    movement_notification(server, client);
}

void left_command(UNUSED server_t *server, client_ai_t *client)
{
    client->position.direction = turn_left(client->position.direction);
    add_to_buffer(&client->buff_out, "ok\n", false);
    debug_print("Client AI %i turned left, new direction : %c\n",
    client->num_player, get_direction_char(client->position.direction));
    movement_notification(server, client);
}

void forward_command(UNUSED server_t *server, client_ai_t *client)
{
    client->position = get_next_position(server, client->position);
    add_to_buffer(&client->buff_out, "ok\n", false);
    debug_print("Client AI %i moved forward, new position : [%i, %i]\n",
    client->num_player, client->position.x, client->position.y);
    movement_notification(server, client);
}
