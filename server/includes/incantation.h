/*
** EPITECH PROJECT, 2024
** server
** File description:
** incantation
*/

#pragma once

#ifndef SERVER_INCANTATION_H
    #define SERVER_INCANTATION_H
    #include <stdio.h>
    #include <stdlib.h>
    #include "my.h"
    #include "client_ai.h"

typedef struct incantation_s {
    int main_player;
    int *players;
    size_t level_target;
    position_t position;
    size_t TTE;
    struct incantation_s *next;
    struct incantation_s *prev;
} incantation_t;

typedef struct incantation_list_s {
    incantation_t *head;
    incantation_t *tail;
    int size;
} incantation_list_t;

/**
 * @brief create new incantation structure
 * @param main_player player that started the incantation
 * @param level_target level that the incantation is targeting
 * @return return the new incantation structure or NULL if malloc failed
 */
incantation_t *create_incantation(int main_player, size_t level_target,
    position_t position);

/**
 * @brief create new incantation list structure
 * @return return the new incantation list structure or NULL if malloc failed
 */
incantation_list_t *create_incantation_list(void);

/**
 * @brief add incantation to the incantation list
 * @param list the incantation list
 * @param incantation the incantation to add
 */
void add_incantation_to_list(incantation_list_t *list,
    incantation_t *incantation);

/**
 * @brief add player to the incantation
 * @param incantation the incantation
 * @param player the player to add
 */
void add_player_to_incantation(incantation_t *incantation, int player);

/**
 * @brief delete incantation
 * @param incantation the incantation to delete
 */
void delete_incantation(incantation_t *incantation);

/**
 * @brief delete incantation from the incantation list
 * @param list the incantation list
 * @param incantation the incantation to delete
 */
void delete_incantation_from_list(incantation_list_t *list,
    incantation_t *incantation);

/**
 * @brief clear the incantation list
 * @param list the incantation list
 */
void clear_incantation_list(incantation_list_t *list);

/**
 * @brief delete the incantation list
 * @param list the incantation list
 */
void delete_incantation_list(incantation_list_t *list);
#endif //SERVER_INCANTATION_H
