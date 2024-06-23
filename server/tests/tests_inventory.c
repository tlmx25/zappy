/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_inventory
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

static char **get_args(void)
{
    char *tmp = "./zappy_server -p 4243 -x 10 -y 10 -n team1 team2 -c 2 -f 100";

    return my_str_to_word_array(tmp, " ");
}

Test(inventory_command, inventory_command)
{
    server_t *server_s = create_server(get_args());

    if (server_s == NULL)
        cr_assert_fail("error malloc server\n");
    init_game(server_s);
    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client1->inventory.food = 1;
    client1->inventory.linemate = 2;
    client1->inventory.deraumere = 3;
    client1->inventory.sibur = 4;
    client1->inventory.mendiane = 5;
    client1->inventory.phiras = 6;
    client1->inventory.thystame = 7;
    client1->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);

    inventory_command(server_s, client1);
    cr_assert_eq(my_strcmp(client1->buff_out, "[food 1, linemate 2, deraumere 3, sibur 4, mendiane 5, phiras 6, thystame 7]\n"), 0);
    delete_server(server_s);
}