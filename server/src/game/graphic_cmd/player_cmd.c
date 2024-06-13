/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_cmd.c
*/

#include "server.h"

void cmd_ppo(server_t *server, client_t *client, char const **command)
{
    int player_id = atoi(command[1]);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    for (int i = 0; i < server->ai_clients->size; i++) {
        if (server->ai_clients->head->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            sprintf(response, "ppo %d %d %d %d\n", player_id,
                server->ai_clients->head->position.x,
                server->ai_clients->head->position.y,
                server->ai_clients->head->position.direction);
            add_to_buffer(&client->buffer_out, response, true);
            server->ai_clients->head = tmp;
            return;
        }
        server->ai_clients->head = server->ai_clients->head->next;
    }
    server->ai_clients->head = tmp;
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}

void cmd_plv(server_t *server, client_t *client, char const **command)
{
    int player_id = atoi(command[1]);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    for (int i = 0; i < server->ai_clients->size; i++) {
        if (server->ai_clients->head->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            sprintf(response, "plv %d %lu\n", player_id,
                server->ai_clients->head->level);
            add_to_buffer(&client->buffer_out, response, true);
            server->ai_clients->head = tmp;
            return;
        }
        server->ai_clients->head = server->ai_clients->head->next;
    }
    server->ai_clients->head = tmp;
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}

static char *cmd_pin_create_response(server_t *server, char *response,
    int player_id)
{
    sprintf(response, "pin %d %d %d %d %d %d %d %d %d %d\n", player_id,
        server->ai_clients->head->position.x,
        server->ai_clients->head->position.y,
        server->ai_clients->head->inventory.food,
        server->ai_clients->head->inventory.linemate,
        server->ai_clients->head->inventory.deraumere,
        server->ai_clients->head->inventory.sibur,
        server->ai_clients->head->inventory.mendiane,
        server->ai_clients->head->inventory.phiras,
        server->ai_clients->head->inventory.thystame);
    return response;
}

void cmd_pin(server_t *server, client_t *client, char const **command)
{
    int player_id = atoi(command[1]);
    client_ai_t *tmp = server->ai_clients->head;
    char *response = NULL;

    for (int i = 0; i < server->ai_clients->size; i++) {
        if (server->ai_clients->head->num_player == player_id) {
            response = malloc(sizeof(char) * 2048);
            response = cmd_pin_create_response(server, response, player_id);
            add_to_buffer(&client->buffer_out, response, true);
            server->ai_clients->head = tmp;
            return;
        }
        server->ai_clients->head = server->ai_clients->head->next;
    }
    server->ai_clients->head = tmp;
    add_to_buffer(&client->buffer_out, "sbp\n", false);
}
