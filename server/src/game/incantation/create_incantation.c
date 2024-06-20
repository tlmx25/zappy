/*
** EPITECH PROJECT, 2024
** server
** File description:
** create_incantation
*/

#include "incantation.h"
#include "client_ai.h"

incantation_t *create_incantation(int main_player, size_t level_target,
    position_t position)
{
    incantation_t *new = malloc(sizeof(incantation_t));

    if (new == NULL)
        return NULL;
    new->main_player = main_player;
    new->players = NULL;
    new->level_target = level_target;
    new->TTE = 300;
    new->position = position;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

incantation_list_t *create_incantation_list(void)
{
    incantation_list_t *new = malloc(sizeof(incantation_list_t));

    if (new == NULL)
        return NULL;
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

void add_incantation_to_list(incantation_list_t *list,
    incantation_t *incantation)
{
    if (list == NULL || incantation == NULL)
        return;
    if (list->head == NULL) {
        list->head = incantation;
        list->tail = incantation;
        list->size = 1;
    } else {
        list->tail->next = incantation;
        incantation->prev = list->tail;
        list->tail = incantation;
    }
}

void add_player_to_incantation(incantation_t *incantation, int player)
{
    int *save = incantation->players;
    int size = 0;

    if (incantation->players == NULL) {
        incantation->players = malloc(sizeof(int) * 2);
        incantation->players[0] = player;
        incantation->players[1] = -1;
        return;
    }
    for (; incantation->players[size] != -1; size++);
    incantation->players = realloc(incantation->players,
    sizeof(int) * (size + 2));
    if (incantation->players == NULL) {
        incantation->players = save;
        return;
    }
    incantation->players[size] = player;
    incantation->players[size + 1] = -1;
}
