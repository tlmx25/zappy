/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_cmd.c
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

void cmd_ppo(server_t *server, client_t *client, char const **command)
{
    int player_id = check_num(command[1], client);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    if (player_id == -1)
        return;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            sprintf(response, "ppo %d %d %d %d\n", player_id,
                tmp->position.x, tmp->position.y, tmp->position.direction + 1);
            add_to_buffer(&client->buffer_out, response, true);
            return;
        }
    }
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}

void cmd_plv(server_t *server, client_t *client, char const **command)
{
    int player_id = check_num(command[1], client);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    if (player_id == -1)
        return;
    for (; tmp; tmp = tmp->next) {
        if (tmp->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            sprintf(response, "plv %d %lu\n", player_id,
                tmp->level);
            add_to_buffer(&client->buffer_out, response, true);
            return;
        }
    }
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}

char *cmd_pin_create_response(client_ai_t *client, char *response,
    int player_id)
{
    sprintf(response, "pin %d %d %d %d %d %d %d %d %d %d\n", player_id,
            client->position.x,
            client->position.y,
            client->inventory.food,
            client->inventory.linemate,
            client->inventory.deraumere,
            client->inventory.sibur,
            client->inventory.mendiane,
            client->inventory.phiras,
            client->inventory.thystame);
    return response;
}

void cmd_pin(server_t *server, client_t *client, char const **command)
{
    int player_id = check_num(command[1], client);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    if (player_id == -1)
        return;
    for (; tmp; tmp = tmp->next) {
        if (tmp->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            response = cmd_pin_create_response(tmp, response, player_id);
            add_to_buffer(&client->buffer_out, response, true);
            return;
        }
    }
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}
