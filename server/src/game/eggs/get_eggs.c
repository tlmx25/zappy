/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_eggs
*/

#include "eggs.h"

egg_t *get_egg_by_team_position(egg_list_t *list, char *team_name,
    position_t pos)
{
    egg_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->team_name, team_name) == 0 &&
            tmp->pos.x == pos.x && tmp->pos.y == pos.y)
            return tmp;
    }
    return NULL;
}

egg_t *get_egg_by_team(egg_list_t *list, char *team_name)
{
    egg_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->team_name, team_name) == 0)
            return tmp;
    }
    return NULL;
}

egg_t *get_egg_by_position(egg_list_t *list, position_t pos)
{
    egg_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->pos.x == pos.x && tmp->pos.y == pos.y)
            return tmp;
    }
    return NULL;
}
