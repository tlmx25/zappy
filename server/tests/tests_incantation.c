/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_incantation
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    char *tmp = "./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 2 -f 100";

    return my_str_to_word_array(tmp, " ");
}


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

Test(incantation_command, incantation_command_no_object)
{
    server_t *server_s = create_server(get_args());
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    tile->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);


    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client2->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "ko\n"), 0);
    delete_server(server_s);
}

Test(incantation_command, incantation_main_player_dead)
{
    server_t *server_s = create_server(get_args());
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    (void)client1;
    tile->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);


    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client2->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "ko\n"), 0);
    delete_server(server_s);
}

Test(incantation_end, incantation_end)
{
    server_t *server_s = create_server(get_args());

    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    tile->object.linemate = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "Current level: 2\n"), 0);
    delete_server(server_s);
}

Test(incantation_end, incantation_end_max)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team1", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team1", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client6 = create_client_ai(6, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client7 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});

    tile->object.linemate = 10;
    tile->object.deraumere = 10;
    tile->object.sibur = 10;
    tile->object.mendiane = 10;
    tile->object.phiras = 10;
    tile->object.thystame = 10;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);
    add_client_ai_to_list(server_s->ai_clients, client6);
    add_client_ai_to_list(server_s->ai_clients, client7);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
        tmp->level = 7;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);
    incantation->players = add_players_on_incantation(5, incantation->players);
    incantation->players = add_players_on_incantation(6, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client6->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client7->buff_out, "Current level: 8\n"), 0);
    delete_server(server_s);
}

Test(incantation_end, incantation_end_player_died)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team1", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team1", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client6 = create_client_ai(6, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client7 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client8 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});

    tile->object.linemate = 10;
    tile->object.deraumere = 10;
    tile->object.sibur = 10;
    tile->object.mendiane = 10;
    tile->object.phiras = 10;
    tile->object.thystame = 10;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);
    add_client_ai_to_list(server_s->ai_clients, client6);
    add_client_ai_to_list(server_s->ai_clients, client7);
    add_client_ai_to_list(server_s->ai_clients, client8);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
        tmp->level = 7;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);
    incantation->players = add_players_on_incantation(55, incantation->players);
    incantation->players = add_players_on_incantation(15, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "ko\n"), 0);
    delete_server(server_s);
}