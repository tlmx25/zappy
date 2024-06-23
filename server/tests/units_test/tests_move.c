/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_move
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

Test(forward_command, forward_command)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    forward_command(server_s, client1);
    cr_assert_eq(client1->position.x, 0);
    cr_assert_eq(client1->position.y, 9);
    cr_assert_eq(client1->position.direction, NORTH);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    delete_server(server_s);
}

Test(forward_command, forward_command_south)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, SOUTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    forward_command(server_s, client1);
    cr_assert_eq(client1->position.x, 0);
    cr_assert_eq(client1->position.y, 1);
    cr_assert_eq(client1->position.direction, SOUTH);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    delete_server(server_s);
}

Test(right_command, right_command)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    right_command(server_s, client1);
    cr_assert_eq(client1->position.x, 0);
    cr_assert_eq(client1->position.y, 0);
    cr_assert_eq(client1->position.direction, EAST);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    delete_server(server_s);
}

Test(left_command, left_command)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    left_command(server_s, client1);
    cr_assert_eq(client1->position.x, 0);
    cr_assert_eq(client1->position.y, 0);
    cr_assert_eq(client1->position.direction, WEST);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    delete_server(server_s);
}

Test(forward_command, forward_command_south_2)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 9, SOUTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    forward_command(server_s, client1);
    cr_assert_eq(client1->position.x, 0);
    cr_assert_eq(client1->position.y, 0);
    cr_assert_eq(client1->position.direction, SOUTH);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    delete_server(server_s);
}