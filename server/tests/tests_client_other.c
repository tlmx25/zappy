/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_client_other
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "client.h"

Test(create_client, should_create_valid_client)
{
    int fd = 1;

    client_t *client = create_client(fd);

    cr_assert_not_null(client);
    cr_assert_eq(client->fd, fd);
    cr_assert_eq(client->team_name, NULL);
    cr_assert_eq(client->buffer_in, NULL);
    cr_assert_eq(my_strcmp(client->buffer_out, "WELCOME\n"), 0);
    cr_assert_eq(client->next, NULL);
    cr_assert_eq(client->prev, NULL);
}

Test(create_client_list, should_create_empty_list)
{
    client_list_t *list = create_client_list();

    cr_assert_not_null(list);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(add_client_to_list, should_add_client_to_empty_list)
{
    client_list_t *list = create_client_list();
    client_t *client = create_client(1);

    add_client_to_list(list, client);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, client);
    cr_assert_eq(list->tail, client);
}

Test(add_client_to_list, should_add_client_to_non_empty_list)
{
    client_list_t *list = create_client_list();
    client_t *client1 = create_client(1);
    client_t *client2 = create_client(2);

    add_client_to_list(list, client1);
    add_client_to_list(list, client2);
    add_client_to_list(NULL, client2);
    add_client_to_list(list, NULL);

    cr_assert_eq(list->size, 2);
    cr_assert_eq(list->head, client1);
    cr_assert_eq(list->tail, client2);
    cr_assert_eq(client1->next, client2);
    cr_assert_eq(client2->prev, client1);
}

Test(create_add_client, should_create_and_add_client_to_list)
{
    client_list_t *list = create_client_list();
    int fd = 1;

    create_add_client(list, fd);

    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_eq(list->head, list->tail);
    cr_assert_eq(list->head->fd, fd);
    cr_assert_eq(list->head->next, NULL);
    cr_assert_eq(list->head->prev, NULL);
}

Test(delete_client, should_delete_client)
{
    client_t *client = create_client(1);

    client->buffer_in = my_strdup("test");
    client->buffer_out = my_strdup("test");
    client->team_name = my_strdup("test");
    delete_client(client);
}

Test(delete_client, should_delete_null_client)
{
    delete_client(NULL);
}

Test(delete_client_list, should_delete_list)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);

    delete_client_list(list);
    delete_client_list(NULL);
}

Test(delete_client_from_list, should_delete_client_from_list)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);
    client_t *client = list->head;

    delete_client_from_list(list, client, 1);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, list->tail);
    cr_assert_eq(list->head, list->tail);
}

Test(delete_client_from_list, delete_null_client)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);

    delete_client_from_list(list, NULL, 1);

    cr_assert_eq(list->size, 2);
    delete_client_list(list);
}

Test(delete_client_from_list, delete_client_not_in_list)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);
    client_t *client = create_client(3);

    delete_client_from_list(list, client, 1);

    cr_assert_eq(list->size, 2);
    delete_client_list(list);
}

Test(delete_client_from_list, delete_middle_client)
{
    // client_list_t *list = create_client_list();
    // // client_t *client = create_client(2);
    // // create_add_client(list, 1);
    // // add_client_to_list(list, client);
    // // create_add_client(list, 3);

    // delete_client_from_list(list, client, 0);

    // cr_assert_eq(list->size, 2);
    // delete_client_list(list);
}

Test(delete_client_from_list, delete_last_client)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);
    client_t *client = list->tail;

    delete_client_from_list(list, client, 1);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, list->tail);
    delete_client_list(list);
}

Test(delete_client_by_fd, should_delete_client_by_fd)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);

    delete_client_by_fd(list, 1, 1);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head->fd, 2);
    delete_client_list(list);
}

Test(delete_client_by_fd, should_not_delete_client_by_fd)
{
    client_list_t *list = create_client_list();
    create_add_client(list, 1);
    create_add_client(list, 2);

    delete_client_by_fd(list, 3, 1);

    cr_assert_eq(list->size, 2);
    delete_client_list(list);
}


Test(get_client_by_fd, should_return_client_with_given_fd)
{
    client_list_t *list = create_client_list();
    add_client_to_list(list, create_client(1));
    add_client_to_list(list, create_client(2));

    client_t *client = get_client_by_fd(list, 1);

    cr_assert_not_null(client);
    cr_assert_eq(client->fd, 1);
}

Test(get_client_by_fd, should_return_null_if_no_client_with_given_fd)
{
    client_list_t *list = create_client_list();
    add_client_to_list(list, create_client(1));

    client_t *client = get_client_by_fd(list, 2);

    cr_assert_null(client);
}

Test(get_client_by_fd, should_return_null_if_list_is_null)
{
    client_t *client = get_client_by_fd(NULL, 1);

    cr_assert_null(client);
}

Test(client_is_converted, should_remove_client_from_list_and_free_it)
{

    client_list_t *list = create_client_list();
    client_t *client = create_client(1);
    add_client_to_list(list, client);
    client->buffer_in = my_strdup("la");

    client_is_converted(list, client);

    cr_assert_eq(list->size, 0);
}

Test(client_is_converted, should_do_nothing_if_client_is_null)
{

    client_list_t *list = create_client_list();
    add_client_to_list(list, create_client(1));

    client_is_converted(list, NULL);

    cr_assert_eq(list->size, 1);
}

#include <criterion/criterion.h>
#include "server.h"

Test(send_to_all_graphic, should_send_message_to_all_clients_in_list)
{
    client_list_t *list = create_client_list();
    add_client_to_list(list, create_client(1));
    add_client_to_list(list, create_client(2));

    for (client_t *tmp = list->head; tmp; tmp = tmp->next)
        tmp->buffer_out = NULL;
    send_to_all_graphic(list, "test message");

    cr_assert_eq(my_strcmp(list->head->buffer_out, "test message\n"), 0);
    cr_assert_eq(my_strcmp(list->head->next->buffer_out, "test message\n"), 0);
}

Test(send_to_all_graphic, should_not_crash_when_list_is_null)
{
    send_to_all_graphic(NULL, "test message");
    // If the test reaches this point without crashing, it passes
}

Test(send_to_all_graphic_arg, should_send_formatted_message_to_all_clients_in_list)
{
    client_list_t *list = create_client_list();
    add_client_to_list(list, create_client(1));
    add_client_to_list(list, create_client(2));

    for (client_t *tmp = list->head; tmp; tmp = tmp->next)
        tmp->buffer_out = NULL;
    send_to_all_graphic_arg(list, "test %s", "message");

    cr_assert_eq(my_strcmp(list->head->buffer_out, "test message\n"), 0);
    cr_assert_eq(my_strcmp(list->head->next->buffer_out, "test message\n"), 0);
}

Test(send_to_all_ai, should_send_message_to_all_ai_clients_in_list)
{
    client_ai_list_t *list = create_client_ai_list();
    add_client_ai_to_list(list, create_client_ai(1, "team1", (position_t){0, 0, NORTH}));
    add_client_ai_to_list(list, create_client_ai(2, "team2", (position_t){1, 1, SOUTH}));

    for (client_ai_t *tmp = list->head; tmp; tmp = tmp->next)
        tmp->buff_out = NULL;
    send_to_all_ai(list, "test message\n");

    cr_assert_eq(my_strcmp(list->head->buff_out, "test message\n"), 0);
    cr_assert_eq(my_strcmp(list->head->next->buff_out, "test message\n"), 0);
}

Test(send_to_other_ai, should_send_message_to_all_ai_clients_except_one)
{
    client_ai_list_t *list = create_client_ai_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, EAST});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){1, 1, SOUTH});
    add_client_ai_to_list(list, client1);
    add_client_ai_to_list(list, client2);

    client1->buff_out = NULL;
    send_to_other_ai(list, "test message", client1);

    cr_assert_eq(client1->buff_out, NULL);
    cr_assert_eq(my_strcmp(client2->buff_out, "test message\n"), 0);
}

Test(send_to_all_graphic_arg, send_null_list)
{
    send_to_all_graphic_arg(NULL, "test %s", "message");
    // If the test reaches this point without crashing, it passes
}

Test(send_to_all_ai, send_null_list)
{
    send_to_all_ai(NULL, "test message\n");
    // If the test reaches this point without crashing, it passes
}

Test(send_to_other_ai, send_null_list)
{
    send_to_other_ai(NULL, "test message", NULL);
    // If the test reaches this point without crashing, it passes
}

void fct(struct server_s *server, struct client_s *client, char const **command)
{
    (void)server;
    (void)command;
    client->buffer_out = my_strdup("test message\n");
}

Test(send_to_all_graphic_func, should_send_message_to_all_graphic_clients)
{
    server_t server = {0};
    server.graphic_clients = create_client_list();
    add_client_to_list(server.graphic_clients, create_client(1));
    add_client_to_list(server.graphic_clients, create_client(2));

    for (client_t *tmp = server.graphic_clients->head; tmp; tmp = tmp->next)
        tmp->buffer_out = NULL;
    send_to_all_graphic_func(&server, NULL, fct);

    cr_assert_eq(my_strcmp(server.graphic_clients->head->buffer_out, "test message\n"), 0);
    cr_assert_eq(my_strcmp(server.graphic_clients->head->next->buffer_out, "test message\n"), 0);
}