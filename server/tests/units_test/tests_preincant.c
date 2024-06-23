/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_preincant
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    srand(time(NULL));
    char tmp[512];

    int port = (rand() % 5000) + 1000;
    snprintf(tmp, 512, "./zappy_server -p %i -x 10 -y 10 -n team1 team2 -c 2 -f 100", port);

    return my_str_to_word_array(tmp, " ");
}

Test(incantation_precommand, incantation_precommand_fail)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.linemate = 0;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    incantation_precommand(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    delete_server(server_s);
}

Test(incantation_precommand, incantation_precommand_success)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.linemate = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.deraumere = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.sibur = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.mendiane = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.phiras = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.thystame = 1;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    incantation_precommand(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "Elevation underway\n"), 0);
    delete_server(server_s);
}

Test(incantation_precommand, incantation_precommand_success_multiple_player)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.linemate = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.deraumere = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.sibur = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.mendiane = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.phiras = 1;
    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.thystame = 1;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client3 = create_client_ai(3, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client4 = create_client_ai(4, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    incantation_precommand(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "Elevation underway\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "Elevation underway\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "Elevation underway\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "Elevation underway\n"), 0);
    delete_server(server_s);
}