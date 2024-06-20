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

/**
* @brief A structure to represent an egg in the game.
*
* This structure represents an egg in the game. Each egg has a position,
* a team name, an id, and pointers to the next and previous eggs in the list.
*/
typedef struct egg_s {
    position_t pos; /**< The position of the egg in the game world. */
    char *team_name; /**< The name of the team that the egg belongs to. */
    int id; /**< The unique identifier for the egg. */
    struct egg_s *next; /**< A pointer to the next egg in the list. */
    struct egg_s *prev; /**< A pointer to the previous egg in the list. */
} egg_t;

/**
* @brief A structure to represent a list of eggs.
*
* This structure represents a list of eggs in the game. It contains pointers
* to the head and tail of the list, and the size of the list.
*/
typedef struct egg_list_s {
    egg_t *head; /**< A pointer to the first egg in the list. */
    egg_t *tail; /**< A pointer to the last egg in the list. */
    int size; /**< The number of eggs in the list. */
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

/**
 * @brief Count the number of eggs by team name
 * @param list list of eggs
 * @param team_name team name of the eggs
 * @return int number of eggs
 */
int count_eggs_by_team(egg_list_t *list, char *team_name);
#endif //SERVER_EGGS_H
