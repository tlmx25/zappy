/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_incantation
*/

#include "incantation.h"

void delete_incantation(incantation_t *incantation)
{
    if (incantation == NULL)
        return;
    if (incantation->players)
        free(incantation->players);
    free(incantation);
}

void delete_incantation_from_list(incantation_list_t *list,
    incantation_t *incantation)
{
    incantation_t *tmp = list->head;

    for (; tmp != NULL && tmp != incantation; tmp = tmp->next);
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
    delete_incantation(tmp);
}

void clear_incantation_list(incantation_list_t *list)
{
    incantation_t *tmp;
    incantation_t *next = NULL;

    if (list == NULL)
        return;
    tmp = list->head;
    while (tmp != NULL) {
        next = tmp->next;
        delete_incantation(tmp);
        tmp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_incantation_list(incantation_list_t *list)
{
    if (list == NULL)
        return;
    clear_incantation_list(list);
    free(list);
}
