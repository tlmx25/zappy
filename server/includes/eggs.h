/*
** EPITECH PROJECT, 2024
** server
** File description:
** eggs
*/

#pragma once

#ifndef SERVER_EGGS_H
    #define SERVER_EGGS_H
    #include "server.h"

typedef struct egg_s {
    position_t pos;
    char *team_name;
    struct egg_s *next;
    struct egg_s *prev;
} egg_t;

typedef struct egg_list_s {
    egg_t *head;
    egg_t *tail;
    int size;
} egg_list_t;

/**
 * @brief Create a new egg
 *
 * @param pos position of the egg
 * @param team_name name of the team
 * @return egg_t*
 */
egg_t *create_egg(position_t pos, char *team_name);

/**
 * @brief Create a new egg list
 *
 * @return egg_list_t*
 */
egg_list_t *create_egg_list(void);

/**
 * @brief Add an egg to the list
 *
 * @param list list of eggs
 * @param egg egg to add
 */
void add_egg_to_list(egg_list_t *list, egg_t *egg);

/**
 * @brief Create an egg and add it to the list
 *
 * @param list list of eggs
 * @param pos position of the egg
 * @param team_name name of the team
 */
void create_add_egg_to_list(egg_list_t *list, position_t pos, char *team_name);

/**
 * @brief Delete an egg
 *
 * @param egg egg to delete
 */
void delete_egg(egg_t *egg);

/**
 * @brief Delete an egg from the list
 *
 * @param list list of eggs
 * @param egg egg to delete
 * @param delete_egg_bool boolean to delete the egg
 */
void delete_egg_from_list(egg_list_t *list, egg_t *egg, int delete_egg_bool);

/**
 * @brief Clear the egg list
 *
 * @param list list of eggs
 */
void clear_egg_list(egg_list_t *list);

/**
 * @brief Delete the egg list
 *
 * @param list list of eggs
 */
void delete_eggs_list(egg_list_t *list);

/**
 * @brief Delete an egg by team name and position
 *
 * @param list list of eggs
 * @param team_name name of the team
 * @param pos position of the egg
 */
void delete_egg_by_team_position(egg_list_t *list, char *team_name,
    position_t pos);

/**
 * @brief Get an egg by team name and position
 * @param list list of eggs
 * @param team_name team name of the eggs
 * @param pos position of the egg
 * @return egg_t* egg found, NULL if not found
 */
egg_t *get_egg_by_team_position(egg_list_t *list, char *team_name,
    position_t pos);

/**
 *
 * @param list Get an egg by team name
 * @param team_name team name of the egg
 * @return egg_t* egg found, NULL if not found
 */
egg_t *get_egg_by_team(egg_list_t *list, char *team_name);

/**
 * @brief Get an egg by position
 * @param list list of eggs
 * @param pos position of the egg
 * @return egg_t * if found or NULL if not found
 */
egg_t *get_egg_by_position(egg_list_t *list, position_t pos);
#endif //SERVER_EGGS_H
