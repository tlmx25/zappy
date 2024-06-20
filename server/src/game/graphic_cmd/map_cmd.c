/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map_cmd.c
*/

#include "server.h"

void cmd_msz(server_t *server, client_t *client, char UNUSED const **command)
{
    char *response = NULL;

    response = malloc(sizeof(char) * 2048);
    sprintf(response, "msz %d %d\n", server->option->width,
        server->option->height);
    add_to_buffer(&client->buffer_out, response, true);
}

void cmd_mct(server_t *server, client_t *client, char UNUSED const **command)
{
    char *response = NULL;
    tile_t *tile = NULL;

    for (int i = 0; i < server->option->width * server->option->height; i++) {
        tile = &server->world->tiles[i];
        response = malloc(sizeof(char) * 4096);
        sprintf(response, "bct %d %d %d %d %d %d %d %d %d\n",
            i % server->option->width,
            i / server->option->width, tile->object.food,
            tile->object.linemate,
            tile->object.deraumere, tile->object.sibur, tile->object.mendiane,
            tile->object.phiras, tile->object.thystame);
        add_to_buffer(&client->buffer_out, response, true);
    }
}

void cmd_bct(server_t *server, client_t *client, char const **command)
{
    int x = 0;
    int y = 0;
    char response[2048] = {0};
    tile_t *tile = &server->world->tiles[y * x];

    if (my_str_isnum(command[1]) == 0 || my_str_isnum(command[2]) == 0) {
        add_to_buffer(&client->buffer_out, "sbp\n", false);
        return;
    }
    x = atoi(command[1]);
    y = atoi(command[2]);
    snprintf(response, 2048, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        tile->object.food,
        tile->object.linemate, tile->object.deraumere, tile->object.sibur,
        tile->object.mendiane, tile->object.phiras, tile->object.thystame);
    add_to_buffer(&client->buffer_out, response, true);
}
