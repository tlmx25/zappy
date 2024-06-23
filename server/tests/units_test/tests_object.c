/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_object
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    char *tmp = "./zappy_server -p 4249 -x 10 -y 10 -n team1 team2 -c 2 -f 100";

    return my_str_to_word_array(tmp, " ");
}

Test(object_command, take_command)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.food = 10;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("food");
    take_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.food, 9);
    delete_server(server_s);
}

Test(object_command, take_command_no_object)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("linemate");
    take_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    delete_server(server_s);
}

Test(object_command, set_command_no_object)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.food = 2;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("food");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.food, 3);
    delete_server(server_s);
}

Test(set_command, set_command_no_object)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    get_tile_by_pos(server_s, (position_t){0, 0, NORTH})->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("thystame");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    delete_server(server_s);
}


Test(set_command, set_command_mendiane)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.mendiane = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.mendiane = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("mendiane");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.mendiane, 6);
    delete_server(server_s);
}

Test(set_command, set_command_thysane)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.thystame = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.thystame = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("thystame");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.thystame, 6);
    delete_server(server_s);
}

Test(set_command, set_command_linemate)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.linemate = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.linemate = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("linemate");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.linemate, 6);
    delete_server(server_s);
}

Test(set_command, set_command_demaure)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.deraumere = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.deraumere = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("deraumere");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.deraumere, 6);
    delete_server(server_s);
}

Test(set_command, set_command_sibur)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.sibur = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.sibur = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("sibur");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.sibur, 6);
    delete_server(server_s);
}

Test(set_command, set_command_phiras)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.phiras = 5;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->inventory.phiras = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("phiras");
    set_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ok\n"), 0);
    cr_assert_eq(tile->object.phiras, 6);
    delete_server(server_s);
}

Test(take_command, test_option_null)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.food = 10;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = NULL;
    take_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    cr_assert_eq(tile->object.food, 10);
    delete_server(server_s);
}

Test(take_command, test_option_unknown)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = get_tile_by_pos(server_s, (position_t){0, 0, NORTH});
    tile->object.food = 10;
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    client1->option = my_strdup("unknown");
    take_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    cr_assert_eq(tile->object.food, 10);
    delete_server(server_s);
}