/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** time_cmd.c
*/

#include "server.h"

static int check_num(char const *cmd, client_t *client)
{
    if (my_str_isnum(PLNUM(cmd)) == 0) {
        add_to_buffer(&client->buffer_out, "sbp\n", false);
        return -1;
    }
    return atoi(PLNUM(cmd));
}

void cmd_sgt(server_t *server, client_t *client, char UNUSED const **command)
{
    char *response = NULL;

    response = malloc(sizeof(char) * 2048);
    sprintf(response, "sgt %d\n", server->option->freq);
    add_to_buffer(&client->buffer_out, response, true);
}

void cmd_sst(server_t *server, client_t *client, char const **command)
{
    int freq = check_num(command[1], client);
    char *response = NULL;

    if (freq < 0)
        return add_to_buffer(&client->buffer_out, "sbp\n", false);
    server->option->freq = freq;
    response = malloc(sizeof(char) * 2048);
    sprintf(response, "sst %d\n", freq);
    add_to_buffer(&client->buffer_out, response, true);
}
