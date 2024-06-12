/*
** EPITECH PROJECT, 2024
** server
** File description:
** client_ai
*/

#pragma once

#ifndef SERVER_CLIENT_AI_H
    #define SERVER_CLIENT_AI_H
    #include <stddef.h>
    #define WARN_RESULT __attribute__((warn_unused_result))

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE
} direction_t;

typedef struct position_s {
    int x;
    int y;
    direction_t direction;
} position_t;

typedef struct client_ai_s {
    int fd;
    char *team_name;
    int num_player;
    char *buff_in;
    char *buff_out;
    struct client_ai_s *next;
    struct client_ai_s *prev;
    int to_disconnect;
    position_t position;
    size_t level;
    size_t TTL;
    char *action;
    size_t TTEA;
    inventory_t inventory;
} client_ai_t;

typedef struct client_ai_list_s {
    client_ai_t *head;
    client_ai_t *tail;
    int size;
} client_ai_list_t;

/**
 * @brief Create a new client
 * @param fd fd of the socket
 * @param team_name team name of the client
 * @param position position of the client
 * @return client_ai_t* new client
 */
client_ai_t *create_client_ai(int fd, char *team_name, position_t position);

/**
 * @brief Add a client to the list
 * @param list list of clients
 * @param client client to add
 */
void add_client_ai_to_list(client_ai_list_t *list, client_ai_t *client);

/**
 * @brief Create a new client list
 * @param list list to create
 */
client_ai_list_t *create_client_ai_list(void);

/**
 * @brief Create and add a client to the list
 * @param list list of clients
 * @param fd fd of the socket
 * @param team_name team name of the client
 * @param position position of the client
 */
void create_add_client_ai(client_ai_list_t *list, int fd, char *team_name,
    position_t position);

/**
 * @brief delete and free a ai client
 * @param client
 */
void delete_client_ai(client_ai_t *client);

/**
 * @brief delete and free a ai client from a list
 * @param list list of clients
 * @param client client to delete
 * @param delete_client_bool boolean to delete the client
 */
void delete_client_ai_from_list(client_ai_list_t *list, client_ai_t *client,
    int delete_client_bool);

/**
 * @brief clear a list of clients
 * @param list list of clients to clear
 */
void clear_client_ai_list(client_ai_list_t *list);

/**
 * @brief delete and free a list of clients
 * @param list list of clients to delete
 */
void delete_client_ai_list(client_ai_list_t *list);

/**
 * @brief delete and free a client from a list with a num
 * @param list list of clients
 * @param num num of the client to delete
 */
void delete_client_ai_by_num(client_ai_list_t *list, int num);
#endif //SERVER_CLIENT_AI_H
