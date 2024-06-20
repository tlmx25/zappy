/*
** EPITECH PROJECT, 2024
** server
** File description:
** incantation_command
*/

#include "commands_ai.h"

static incantation_requirements_t REQUIREMENT[] = {
    {0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1},
};

static tile_t *get_tile_by_pos(server_t *server, position_t position)
{
    int x = position.x;
    int y = position.y;

    if (x < 0)
        x = server->option->width + x;
    if (y < 0)
        y = server->option->height + y;
    if (x >= server->option->width)
        x = x % server->option->width;
    if (y >= server->option->height)
        y = y % server->option->height;
    return &server->world->tiles[y * server->option->width + x];
}

char *int_array_to_str(int *array)
{
    char *str = NULL;
    char buffer[4096] = {0};
    int index;

    for (int i = 0; array[i] != -1; i++) {
        index = my_strlen(buffer);
        snprintf(buffer + index, 4096 - index, " %d", array[i]);
    }
    return my_strdup(buffer);
}

static int count_players_on_tile(client_ai_list_t *clients,
    position_t position, size_t level)
{
    int nb_players = 0;

    for (client_ai_t *tmp = clients->head; tmp; tmp = tmp->next) {
        if (tmp->position.x == position.x && tmp->position.y == position.y
        && tmp->level == level)
            nb_players++;
    }
    return nb_players;
}

bool check_requirement(tile_t *tile, client_ai_list_t *clients, size_t level)
{
    incantation_requirements_t *requirement = &REQUIREMENT[level];
    int nb_players = count_players_on_tile(clients, tile->coordinate, level);

    if (nb_players < requirement->players)
        return false;
    if (tile->object.linemate < requirement->linemate)
        return false;
    if (tile->object.deraumere < requirement->deraumere)
        return false;
    if (tile->object.sibur < requirement->sibur)
        return false;
    if (tile->object.mendiane < requirement->mendiane)
        return false;
    if (tile->object.phiras < requirement->phiras)
        return false;
    if (tile->object.thystame < requirement->thystame)
        return false;
    return true;
}

static void send_message_to_incantation_players(server_t *server, int *players,
    char *message)
{
    client_ai_t *tmp = NULL;

    for (int i = 0; players[i] != -1; i++) {
        tmp = get_client_ai_by_num(server->ai_clients, players[i]);
        if (tmp)
            add_to_buffer(&tmp->buff_out, message, false);
    }
}

void notify_incant(server_t *server, int *players, client_ai_t *client)
{
    char *players_str = int_array_to_str(players);
    char buffer[32];
    client_ai_t *tmp = NULL;

    for (int i = 0; players[i] != -1; i++) {
        tmp = get_client_ai_by_num(server->ai_clients, players[i]);
        if (tmp) {
            tmp->action = -1;
            tmp->TTEA = 0;
            tmp->level++;
        }
    }
    debug_print("Incantation players: [%s] its finish %i -> %i\n", players_str,
    client->level - 1, client->level);
    snprintf(buffer, 32, "Current level: %ld\n", client->level);
    send_message_to_incantation_players(server, players, buffer);
    add_to_buffer(&client->buff_out, buffer, false);
    send_to_all_graphic_arg(server->graphic_clients, "pie %i %i 1\n",
    client->position.x, client->position.y);
}

static void failed_incantation(server_t *server, client_ai_t *client,
    incantation_t *incantation, char const *reason)
{
    int *players = incantation->players;
    char *players_str = int_array_to_str(players);

    send_message_to_incantation_players(server, players, "ko\n");
    debug_print("Incantation {%i, %i} failed: [%s], reason: %s\n",
    incantation->position.x, incantation->position.y, players_str, reason);
    if (client)
        add_to_buffer(&client->buff_out, "ko\n", false);
    send_to_all_graphic_arg(server->graphic_clients, "pie %i %i 0\n",
    incantation->position.x, incantation->position.y);
    free(players_str);
}

void incantation_end(server_t *server, incantation_t *incantation)
{
    client_ai_t *client = get_client_ai_by_num(server->ai_clients,
    incantation->main_player);

    if (client == NULL)
        return failed_incantation(server, client, incantation,
        "main player not dead");
    if (!check_requirement(get_tile_by_pos(server, client->position),
    server->ai_clients, client->level))
        return failed_incantation(server, client, incantation,
        "requirement not met");
    notify_incant(server, incantation->players, client);
    client->TTEA = 0;
    client->action = -1;
    client->level++;
    delete_incantation_from_list(server->world->incantations, incantation);
}
