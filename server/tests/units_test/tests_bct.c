/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_bct
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "graphique_cmd.h"

static char **get_args(void)
{
    srand(time(NULL));
    char tmp[512];

    int port = (rand() % 5000) + 1000;
    snprintf(tmp, 512, "./zappy_server -p %i -x 10 -y 10 -n team1 team2 -c 2 -f 100", port);

    return my_str_to_word_array(tmp, " ");
}

Test(bct_command, send_message)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error malloc server_s\n");
    init_game(server_s);

    tile_t *tile = get_tile_by_pos(server_s, (position_t){1, 1, NORTH});
    tile->object.food = 10;
    tile->object.linemate = 2;
    tile->object.deraumere = 3;
    tile->object.sibur = 4;
    tile->object.mendiane = 5;
    tile->object.phiras = 6;
    tile->object.thystame = 7;

    server_s->graphic_clients = create_client_list();
    client_t *client1 = create_client(1);
    add_client_to_list(server_s->graphic_clients, client1);
    for (client_t *tmp = server_s->graphic_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buffer_out = NULL;
    }
    char **args = my_str_to_word_array("bct 1 1", " ");

    char *result = "bct 1 1 10 2 3 4 5 6 7\n";
    cmd_bct(server_s, client1, (char const **)args);
    cr_assert_eq(my_strcmp(client1->buffer_out, result), 0);
    free_tab(args);
    delete_server(server_s);
}

Test(cmd_bct, invalid_arg)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error malloc server_s\n");
    init_game(server_s);

    server_s->graphic_clients = create_client_list();
    client_t *client1 = create_client(1);
    add_client_to_list(server_s->graphic_clients, client1);
    for (client_t *tmp = server_s->graphic_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buffer_out = NULL;
    }
    char **args = my_str_to_word_array("bct 1", " ");

    char *result = "sbp\n";
    cmd_bct(server_s, client1, (char const **)args);
    cr_assert_eq(my_strcmp(client1->buffer_out, result), 0);
    free_tab(args);
    delete_server(server_s);
}

Test(cmd_msz, cmd_msz)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error malloc server_s\n");
    init_game(server_s);

    server_s->graphic_clients = create_client_list();
    client_t *client1 = create_client(1);
    add_client_to_list(server_s->graphic_clients, client1);
    for (client_t *tmp = server_s->graphic_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buffer_out = NULL;
    }
    char **args = my_str_to_word_array("msz", " ");

    char *result = "msz 10 10\n";
    cmd_msz(server_s, client1, (char const **)args);
    cr_assert_eq(my_strcmp(client1->buffer_out, result), 0);
    free_tab(args);
    delete_server(server_s);
}

Test(cmd_mct, cmd_mct)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error malloc server_s\n");
    init_game(server_s);

    server_s->graphic_clients = create_client_list();
    client_t *client1 = create_client(1);
    add_client_to_list(server_s->graphic_clients, client1);
    for (client_t *tmp = server_s->graphic_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buffer_out = NULL;
    }
    char **args = my_str_to_word_array("mct", " ");
    cmd_mct(server_s, client1, (char const **)args);
    delete_server(server_s);
}