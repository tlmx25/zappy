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

static int count_players_on_tile(client_ai_list_t *clients,
    position_t position, size_t level)
{
    int nb_players = 0;

    for (client_ai_t *tmp = clients->head; tmp; tmp = tmp->next) {
        if (tmp->position.x == position.x && tmp->position.y == position.y
        && tmp->level == level && tmp->action == -1)
            nb_players++;
    }
    return nb_players;
}

bool check_requirement(tile_t *tile, client_ai_list_t *clients, size_t level,
    bool final)
{
    incantation_requirements_t *requirement = &REQUIREMENT[level];
    int nb_players = count_players_on_tile(clients, tile->coordinate, level);

    if ((nb_players + 1 < requirement->players) && !final)
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

bool check_final_requirement(tile_t *tile,
    client_ai_list_t *clients, size_t level, int *players)
{
    bool can_incant = check_requirement(tile, clients, level, true);
    int count = 0;
    client_ai_t *tmp;
    incantation_requirements_t *requirement = &REQUIREMENT[level];

    if (!can_incant)
        return false;
    for (int i = 0; players && players[i] != -1; i++) {
        tmp = get_client_ai_by_num(clients, players[i]);
        if (tmp)
            count++;
    }
    if (count + 1 < requirement->players)
        return false;
    return true;
}

static void send_message_to_incantation_players(server_t *server, int *players,
    char *message)
{
    client_ai_t *tmp = NULL;

    for (int i = 0; players && players[i] != -1; i++) {
        tmp = get_client_ai_by_num(server->ai_clients, players[i]);
        if (tmp)
            add_to_buffer(&tmp->buff_out, message, false);
    }
}

static void set_player(int *players, client_ai_list_t *clients,
    client_list_t *graph)
{
    client_ai_t *tmp = NULL;

    for (int i = 0; players && players[i] != -1; i++) {
        tmp = get_client_ai_by_num(clients, players[i]);
        if (tmp) {
            tmp->action = -1;
            tmp->TTEA = 0;
            tmp->level++;
            send_to_all_graphic_arg(graph, "plv %i %i\n", tmp->num_player,
            tmp->level);
        }
    }
}

void notify_incant(server_t *server, int *players, client_ai_t *client)
{
    char *players_str = int_array_to_str(players);
    char buffer[32];

    set_player(players, server->ai_clients, server->graphic_clients);
    debug_print("Incantation players: [%s] its finish %i -> %i\n", players_str,
    client->level - 1, client->level);
    snprintf(buffer, 32, "Current level: %ld\n", client->level);
    send_message_to_incantation_players(server, players, buffer);
    add_to_buffer(&client->buff_out, buffer, false);
    send_to_all_graphic_arg(server->graphic_clients, "pie %i %i 1\n",
    client->position.x, client->position.y);
    free(players_str);
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

void check_win_incantation(server_t *server)
{
    char **names = server->option->names;

    for (int i = 0; names[i]; i++) {
        if (count_client_ai_by_team_level(server->ai_clients,
        names[i], 8) >= 6) {
            send_to_all_graphic_arg(server->graphic_clients,
            "seg %s\n", names[i]);
            return;
        }
    }
}

void incantation_end(server_t *server, incantation_t *incantation)
{
    client_ai_t *client = get_client_ai_by_num(server->ai_clients,
    incantation->main_player);

    if (client == NULL)
        return failed_incantation(server, client, incantation,
        "main player dead");
    if (!check_final_requirement(get_tile_by_pos(server, client->position),
    server->ai_clients, client->level, incantation->players))
        return failed_incantation(server, client, incantation,
        "requirement not met");
    remove_object(get_tile_by_pos(server, client->position),
    &REQUIREMENT[client->level], client, server->graphic_clients);
    send_to_all_graphic_arg(server->graphic_clients, "plv %i %i\n",
    client->num_player, client->level);
    notify_incant(server, incantation->players, client);
    if (client->level == 8)
        check_win_incantation(server);
    delete_incantation_from_list(server->world->incantations, incantation);
}
