/*
** EPITECH PROJECT, 2024
** server
** File description:
** preincant_command
*/

#include "commands_ai.h"

static int *add_players_on_incantation(int num, int *players)
{
    int *save = players;
    int size = 0;

    if (players == NULL) {
        players = malloc(sizeof(int) * 2);
        players[0] = num;
        players[1] = -1;
        return players;
    }
    for (; players[size] != -1; size++);
    players = realloc(players, sizeof(int) * (size + 2));
    if (players == NULL)
        return save;
    players[size] = num;
    players[size + 1] = -1;
    return players;
}

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

static void notify_preincant(server_t *server, int *players,
    client_ai_t *client)
{
    char *players_str = int_array_to_str(players);

    if (players_str == NULL)
        return;
    send_to_all_graphic_arg(server->graphic_clients, "pic %d %d %d %s\n",
    client->position.x, client->position.y, client->level, players_str);
    debug_print("Player %i start incantation at {%i, %i} with players %s\n",
    client->num_player, client->position.x, client->position.y, players_str);
    free(players_str);
}

static void failed_preincantation(client_ai_t *client)
{

    add_to_buffer(&client->buff_out, "ko\n", false);
    client->action = -1;
    client->TTEA = 0;
    debug_print("Player %i failed to incant\n", client->num_player);
}

static int *load_player(server_t *server, client_ai_t *client)
{
    int *players = NULL;

    for (client_ai_t *tmp = server->ai_clients->head; tmp; tmp = tmp->next) {
        if (tmp->num_player == client->num_player)
            continue;
        if (tmp->position.x == client->position.x && tmp->position.y ==
        client->position.y && tmp->level == client->level) {
            add_to_buffer(&tmp->buff_out, "Elevation underway\n", false);
            tmp->action = client->action;
            tmp->TTEA = client->TTEA + 300;
            players = add_players_on_incantation(tmp->num_player, players);
        }
    }
    add_to_buffer(&client->buff_out, "Elevation underway\n", false);
    client->TTEA += 300;
    return players;
}

void incantation_precommand(server_t *server, client_ai_t *client)
{
    tile_t *tile = get_tile_by_pos(server, client->position);
    size_t incantation_level = client->level;
    bool can_incant = check_requirement(tile,
    server->ai_clients, incantation_level);
    int *players = NULL;
    incantation_t *incantation;

    if (can_incant == false)
        return failed_preincantation(client);
    players = load_player(server, client);
    incantation = create_incantation(client->num_player,
    incantation_level + 1, client->position);
    if (incantation == NULL)
        return failed_preincantation(client);
    add_incantation_to_list(server->world->incantations, incantation);
    incantation->players = players;
    notify_preincant(server, players, client);
}
