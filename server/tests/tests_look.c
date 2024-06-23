/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_look
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    char *tmp = "./zappy_server -p 4247 -x 10 -y 10 -n team1 team2 -c 2 -f 100";

    return my_str_to_word_array(tmp, " ");
}

Test(look_command, look_command)
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

    look_command(server_s, client1);
    int nb_commas = 0;
    for (int i = 0; client1->buff_out[i] != '\0'; i++) {
        if (client1->buff_out[i] == ',')
            nb_commas++;
    }
    cr_assert_eq(nb_commas, 3);
    delete_server(server_s);
}

Test(look_command, look_command_level_3)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);
    client1->level = 3;

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }

    look_command(server_s, client1);
    int nb_commas = 0;
    for (int i = 0; client1->buff_out[i] != '\0'; i++) {
        if (client1->buff_out[i] == ',')
            nb_commas++;
    }
    cr_assert_eq(nb_commas, 15);
    delete_server(server_s);
}

Test(look_command, look_command_player)
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

    look_command(server_s, client1);
    int nb_commas = 0;
    for (int i = 0; client1->buff_out[i] != '\0'; i++) {
        if (client1->buff_out[i] == ',')
            nb_commas++;
    }
    char *start = "[ player";
    cr_assert_eq(my_strncmp(client1->buff_out, start, my_strlen(start)), 0);
    delete_server(server_s);
}