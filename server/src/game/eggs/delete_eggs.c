/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_eggs
*/

#include "eggs.h"

void delete_egg(egg_t *egg)
{
    if (egg == NULL)
        return;
    if (egg->team_name != NULL)
        free(egg->team_name);
    free(egg);
}

void delete_egg_from_list(egg_list_t *list, egg_t *egg, int delete_egg_bool)
{
    egg_t *tmp = list->head;

    for (; tmp != NULL && tmp != egg; tmp = tmp->next);
    if (tmp == NULL)
        return;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp == list->head)
        list->head = tmp->next;
    if (tmp == list->tail)
        list->tail = tmp->prev;
    if (delete_egg_bool)
        delete_egg(tmp);
}

void clear_egg_list(egg_list_t *list)
{
    egg_t *tmp = list->head;
    egg_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        delete_egg(tmp);
        tmp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_eggs_list(egg_list_t *list)
{
    clear_egg_list(list);
    free(list);
}

void delete_egg_by_team_position(egg_list_t *list, char *team_name,
    position_t pos)
{
    egg_t *tmp = list->head;
    egg_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (my_strcmp(tmp->team_name, team_name) == 0 &&
            tmp->pos.x == pos.x && tmp->pos.y == pos.y) {
            delete_egg_from_list(list, tmp, 1);
            return;
        }
        tmp = next;
    }
}
