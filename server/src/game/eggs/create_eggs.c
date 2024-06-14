/*
** EPITECH PROJECT, 2024
** server
** File description:
** create_eggs
*/

#include "eggs.h"

egg_t *create_egg(position_t pos, char *team_name)
{
    egg_t *new = malloc(sizeof(egg_t));
    static int id = 0;

    if (new == NULL)
        return NULL;
    new->pos = pos;
    new->id = id;
    id++;
    new->team_name = my_strdup(team_name);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

egg_list_t *create_egg_list(void)
{
    egg_list_t *list = malloc(sizeof(egg_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void add_egg_to_list(egg_list_t *list, egg_t *egg)
{
    if (egg == NULL || list == NULL)
        return;
    if (list->head == NULL) {
        list->head = egg;
        list->tail = egg;
        list->size = 1;
    } else {
        list->tail->next = egg;
        egg->prev = list->tail;
        list->tail = egg;
        list->size++;
    }
}

void create_add_egg_to_list(egg_list_t *list, position_t pos, char *team_name)
{
    egg_t *new = create_egg(pos, team_name);

    add_egg_to_list(list, new);
}
