/*
** EPITECH PROJECT, 2024
** server
** File description:
** connect_nbr_command
*/

#include "server.h"

void connect_nbr_command(server_t *server, client_ai_t *client)
{
    int nb_eggs_team = count_eggs_by_team(server->world->eggs,
    client->team_name);
    char buff[64];

    snprintf(buff, 64, "%d\n", nb_eggs_team);
    add_to_buffer(&client->buff_out, buff, false);
}
