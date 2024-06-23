/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_broadcast
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

Test(connect_nbr_command, connect_nbr_command)
{
    server_t *server_s = create_server(get_args());
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);

    connect_nbr_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "2\n"), 0);
    delete_server(server_s);
}