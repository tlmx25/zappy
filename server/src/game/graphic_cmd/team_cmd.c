/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team_cmd.c
*/

#include "server.h"

void cmd_tna(server_t *server, client_t *client, char UNUSED const **command)
{
    char *response = NULL;

    for (int i = 0; i < server->world->nbr_teams; i++) {
        response = malloc(sizeof(char) * 2048);
        sprintf(response, "tna %s\n", server->world->teams[i].name);
        add_to_buffer(&client->buffer_out, response, true);
    }
}
