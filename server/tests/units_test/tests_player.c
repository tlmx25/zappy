/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_player
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "graphique_cmd.h"
#include "server.h"

static char **get_args(void)
{
    srand(time(NULL));
    char tmp[512];

    int port = (rand() % 5000) + 1000;
    snprintf(tmp, 512, "./zappy_server -p %i -x 10 -y 10 -n team1 team2 -c 2 -f 100", port);

    return my_str_to_word_array(tmp, " ");
}


Test(cmd_ppo, cmd_ppo)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){5, 6, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);

    client_t *clientg = create_client(1);
    add_client_to_list(server_s->graphic_clients, clientg);

    client1->buff_out = NULL;
    clientg->buffer_out = NULL;
    char **args = my_str_to_word_array("ppo 0", " ");
    cmd_ppo(server_s, clientg, (char const **)args);
    cr_assert_eq(my_strcmp(clientg->buffer_out, "ppo 0 5 6 1\n"), 0);
    free_tab(args);
    delete_server(server_s);
}