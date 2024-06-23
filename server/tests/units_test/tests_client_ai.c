/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_client_ai
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "client_ai.h"

Test(create_client_ai, should_create_valid_client_ai)
{
    int fd = 1;
    char *team_name = "team1";
    position_t position = {0, 0, NORTH};

    client_ai_t *client = create_client_ai(fd, team_name, position);

    cr_assert_not_null(client);
    cr_assert_eq(client->fd, fd);
    cr_assert_str_eq(client->team_name, team_name);
    cr_assert_eq(client->position.x, position.x);
    cr_assert_eq(client->position.y, position.y);
    cr_assert_eq(client->position.direction, NORTH);
    cr_assert_eq(client->level, 1);
    cr_assert_eq(client->TTL, 126);
    cr_assert_null(client->option);
}


Test(add_client_ai_to_list, should_add_client_to_empty_list)
{
    client_ai_list_t *list = create_client_ai_list();
    client_ai_t *client = create_client_ai(1, "team1", (position_t){0, 0, SOUTH});

    add_client_ai_to_list(list, client);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, client);
    cr_assert_eq(list->tail, client);
}

Test(add_client_ai_to_list, should_add_client_to_non_empty_list)
{
    client_ai_list_t *list = create_client_ai_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){1, 1, EAST});

    add_client_ai_to_list(list, client1);
    add_client_ai_to_list(list, client2);

    cr_assert_eq(list->size, 2);
    cr_assert_eq(list->head, client1);
    cr_assert_eq(list->tail, client2);
    cr_assert_eq(client1->next, client2);
    cr_assert_eq(client2->prev, client1);
}

Test(create_client_ai_list, should_create_empty_list)
{
    client_ai_list_t *list = create_client_ai_list();

    cr_assert_not_null(list);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);
    cr_assert_eq(list->size, 0);
}

Test(create_add_client_ai, should_create_and_add_client_to_list)
{
    client_ai_list_t *list = create_client_ai_list();

    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});

    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_eq(list->head, list->tail);
}

Test(clear_client_ai_list, should_clear_list)
{
    client_ai_list_t *list = create_client_ai_list();
    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});
    create_add_client_ai(list, 2, "team2", (position_t){1, 1, EAST});

    clear_client_ai_list(list);

    cr_assert_eq(list->size, 0);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);
}

Test(clear_client_ai_list, clear_null_list)
{
    client_ai_list_t *list = NULL;

    clear_client_ai_list(list);

    cr_assert_null(list);
}

Test(delete_client_ai, should_delete_client)
{
    client_ai_t *client = create_client_ai(1, "team1", (position_t){0, 0, WEST});

    client->option = malloc(sizeof(char) * 10);
    client->buff_in = malloc(sizeof(char) * 10);
    client->buff_out = malloc(sizeof(char) * 10);
    delete_client_ai(client);
}

Test(delete_client_ai, clear_null_ai)
{
    client_ai_t *client = NULL;

    delete_client_ai(client);
}

Test(delete_client_ai_from_list, send_null_list)
{

    delete_client_ai_from_list(NULL, NULL, 1);

}

Test(delete_client_ai_from_list, should_delete_client_from_list)
{
    client_ai_list_t *list = create_client_ai_list();
    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});
    create_add_client_ai(list, 2, "team2", (position_t){1, 1, EAST});

    delete_client_ai_from_list(list, list->head, 1);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, list->tail);
}

Test(delete_client_ai_by_num, should_delete_client_by_number)
{
    client_ai_list_t *list = create_client_ai_list();

    if (list == NULL)
        return;
    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});
    create_add_client_ai(list, 2, "team2", (position_t){1, 1, EAST});

    delete_client_ai_by_num(list, 1);

    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->head, list->tail);
}

Test(delete_client_ai_by_num, should_delete_client_by_number_middle)
{
    client_ai_list_t *list = create_client_ai_list();

    if (list == NULL)
        return;
    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});
    create_add_client_ai(list, 2, "team2", (position_t){1, 1, EAST});
    create_add_client_ai(list, 2, "team3", (position_t){1, 1, EAST});

    delete_client_ai_by_num(list, 1);

    cr_assert_eq(list->size, 2);
    cr_assert_str_eq(list->head->team_name, "team1");
    cr_assert_str_eq(list->tail->team_name, "team3");

}

Test(add_client_ai_to_list, add_null_client)
{
    client_ai_list_t *list = create_client_ai_list();
    client_ai_t *client = NULL;

    add_client_ai_to_list(list, client);

    cr_assert_eq(list->size, 0);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);
}

Test(delete_client_ai_list, delete_list)
{
    client_ai_list_t *list = create_client_ai_list();

    if (list == NULL)
        return;
    create_add_client_ai(list, 1, "team1", (position_t){0, 0, WEST});
    create_add_client_ai(list, 2, "team2", (position_t){1, 1, EAST});
    delete_client_ai_list(list);
}

Test(delete_client_ai_list, delete_list_null)
{
    delete_client_ai_list(NULL);
}

#include <criterion/criterion.h>
#include "server.h"

Test(get_client_ai_by_num, should_return_client_with_given_num)
{
    client_ai_list_t *list = create_client_ai_list();
    add_client_ai_to_list(list, create_client_ai(1, "team1", (position_t){0, 0, WEST}));
    add_client_ai_to_list(list, create_client_ai(2, "team2", (position_t){1, 1, EAST}));

    client_ai_t *client = get_client_ai_by_num(list, 1);

    cr_assert_not_null(client);
    cr_assert_eq(client->num_player, 1);
}

Test(get_client_ai_by_num, should_return_null_if_no_client_with_given_num)
{
    client_ai_list_t *list = create_client_ai_list();
    add_client_ai_to_list(list, create_client_ai(1, "team1", (position_t){0, 0, SOUTH}));

    client_ai_t *client = get_client_ai_by_num(list, 2);

    cr_assert_null(client);
}

Test(get_client_ai_by_num, should_return_null_if_list_is_null)
{
    client_ai_t *client = get_client_ai_by_num(NULL, 1);

    cr_assert_null(client);
}

Test(count_client_ai_by_team_level, should_return_correct_count)
{
    client_ai_list_t *list = create_client_ai_list();
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){1, 1, EAST});
    client1->level = 2;
    client2->level = 2;
    add_client_ai_to_list(list, client1);
    add_client_ai_to_list(list, client2);

    size_t count = count_client_ai_by_team_level(list, "team1", 2);
    count_client_ai_by_team_level(list, NULL, 2);

    cr_assert_eq(count, 2);
}

Test(count_client_ai_by_team_level, should_return_zero_if_no_clients_with_given_team_and_level)
{
    client_ai_list_t *list = create_client_ai_list();
    add_client_ai_to_list(list, create_client_ai(1, "team1", (position_t){0, 0, NORTH}));

    size_t count = count_client_ai_by_team_level(list, "team2", 2);

    cr_assert_eq(count, 0);
}

Test(count_client_ai_by_team_level, should_return_zero_if_list_is_null)
{
    size_t count = count_client_ai_by_team_level(NULL, "team1", 2);

    cr_assert_eq(count, 0);
}