/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_broadcast
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "commands_ai.h"

Test(broadcast_command, send_message)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){1, 1, EAST});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 4, Hello\n"), 0);
}

Test(broadcast_command, send_message_2)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){4, 4, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){7, 4, WEST});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 1, Hello\n"), 0);
}

Test(broadcast_command, send_message_3)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){4, 4, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){4, 7, SOUTH});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 5, Hello\n"), 0);
}

Test(broadcast_command, send_message_4)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){1, 4, SOUTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){5, 1, NORTH});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 4, Hello\n"), 0);
}

Test(broadcast_command, send_message_5)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){4, 4, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){1, 4, WEST});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 5, Hello\n"), 0);
}

Test(broadcast_command, send_message_6)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){4, 4, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){1, 7, SOUTH});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 4, Hello\n"), 0);
}

Test(broadcast_command, send_message_7)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){7, 7, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){4, 4, SOUTH});
    client1->option = strdup("Hello");

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(my_strcmp(client2->buff_out, "message 2, Hello\n"), 0);
}

Test(broadcast_command, send_message_8)
{
    server_t *server_s = malloc(sizeof(server_t));

    server_s->ai_clients = create_client_ai_list();
    server_s->graphic_clients = create_client_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){7, 7, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){4, 4, SOUTH});
    client1->option = NULL;

    client1->buff_out = NULL;
    client2->buff_out = NULL;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);

    broadcast_command(server_s, client1);
    cr_assert_eq(client2->buff_out, NULL);
}