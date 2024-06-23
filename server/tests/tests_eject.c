/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_eject
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    char *tmp = "./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 2 -f 100";

    return my_str_to_word_array(tmp, " ");
}

Test(eject_command, eject_command_player_NORTH)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    eject_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        if (tmp == client1){
            cr_assert_eq(tmp->position.x, 0);
            cr_assert_eq(tmp->position.y, 0);
            continue;
        }
        cr_assert_eq(tmp->position.x, 0);
        cr_assert_eq(tmp->position.y, 9);
    }
    delete_server(server_s);
}

Test(eject_command, eject_command_player_EAST)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    eject_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        if (tmp == client1){
            cr_assert_eq(tmp->position.x, 0);
            cr_assert_eq(tmp->position.y, 0);
            continue;
        }
        cr_assert_eq(tmp->position.x, 1);
        cr_assert_eq(tmp->position.y, 0);

    }
    delete_server(server_s);
}

Test(eject_command, delete_egg)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, EAST});

    add_client_ai_to_list(server_s->ai_clients, client1);
    client1->buff_out = NULL;
    egg_t *egg = create_egg((position_t){0, 0, EAST}, "team2");
    add_egg_to_list(server_s->world->eggs, egg);

    eject_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(get_egg_by_team_position(server_s->world->eggs, "team2", (position_t){0, 0, EAST}), NULL);
    delete_server(server_s);
}