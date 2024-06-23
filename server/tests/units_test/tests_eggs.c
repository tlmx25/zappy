/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_eggs
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

Test(create_egg, create_egg)
{
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    if (egg == NULL)
        cr_assert_fail("error create_egg\n");

    cr_assert_eq(egg->pos.x, 7);
    cr_assert_eq(egg->pos.y, 8);
    cr_assert_eq(my_strcmp(egg->team_name, "team1"), 0);
    cr_assert_eq(egg->id, 0);
}

Test(add_egg_to_list, add_egg_to_list)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){7, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    cr_assert_eq(eggs->head->id, 0);
    cr_assert_eq(eggs->tail->id, 2);
}

Test(remove_egg_from_list, remove_egg_from_list)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){7, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    delete_egg_from_list(eggs, egg2, true);
    cr_assert_eq(eggs->size, 2);
    cr_assert_eq(eggs->head->id, 0);
    cr_assert_eq(eggs->tail->id, 2);
}

Test(delete_egg_by_team_position, delete_egg_by_team_position)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){7, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    delete_egg_by_team_position(eggs, "team1", (position_t){7, 8, NONE});
    cr_assert_eq(eggs->size, 2);
    cr_assert_eq(eggs->head->id, 1);
    cr_assert_eq(eggs->tail->id, 2);
}

Test(get_egg_by_position, get_egg_by_position)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){6, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){8, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    egg_t *tmp1 = get_egg_by_position(eggs, (position_t){7, 8, NONE});
    egg_t *tmp2 = get_egg_by_position(eggs, (position_t){6, 8, NONE});
    egg_t *tmp3 = get_egg_by_position(eggs, (position_t){8, 8, NONE});

    if (!tmp1 || !tmp2 || !tmp3)
        cr_assert_fail("error get_egg_by_position\n");

    cr_assert_eq(tmp1->id, 0);
    cr_assert_eq(tmp2->id, 1);
    cr_assert_eq(tmp3->id, 2);
}

Test(get_egg_by_team_position, get_egg_by_team_position)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){6, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){8, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    egg_t *tmp1 = get_egg_by_team_position(eggs, "team1", (position_t){7, 8, NONE});
    egg_t *tmp2 = get_egg_by_team_position(eggs, "team1", (position_t){6, 8, NONE});
    egg_t *tmp3 = get_egg_by_team_position(eggs, "team1", (position_t){8, 8, NONE});

    if (!tmp1 || !tmp2 || !tmp3)
        cr_assert_fail("error get_egg_by_team_position\n");

    cr_assert_eq(tmp1->id, 0);
    cr_assert_eq(tmp2->id, 1);
    cr_assert_eq(tmp3->id, 2);
}

Test(get_egg_by_team, get_egg_by_team)
{
    egg_list_t *eggs = create_egg_list();
    egg_t *egg = create_egg((position_t){7, 8, NONE}, "team1");
    egg_t *egg2 = create_egg((position_t){6, 8, NONE}, "team1");
    egg_t *egg3 = create_egg((position_t){8, 8, NONE}, "team1");

    add_egg_to_list(eggs, egg);
    add_egg_to_list(eggs, egg2);
    add_egg_to_list(eggs, egg3);

    cr_assert_eq(eggs->size, 3);
    egg_t *tmp1 = get_egg_by_team(eggs, "team1");
    if (!tmp1)
        cr_assert_fail("error get_egg_by_team\n");

    cr_assert_eq(tmp1->id, 0);
}