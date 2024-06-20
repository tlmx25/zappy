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

/**
 * @brief inventory structure
 *
 * the inventory structure is used to store the information about the inventory
 * of a client or tile
 */
typedef struct inventory_s {
    int food; /** food quantity */
    int linemate; /** linemate quantity */
    int deraumere; /** deraumere quantity */
    int sibur; /** sibur quantity */
    int mendiane; /** mendiane quantity */
    int phiras; /** phiras quantity */
    int thystame; /** thystame quantity */
} inventory_t;

/**
 * @brief direction enum
 *
 * the direction enum is used to store the direction of a client
 */
typedef enum {
    NORTH, /** north direction */
    EAST, /** east direction */
    SOUTH, /** south direction */
    WEST, /** west direction */
    NONE /** no direction */
} direction_t;

/**
 * @brief position structure
 *
 * the position structure is used to store the information about the position
 * of a client
 */
typedef struct position_s {
    int x; /** x position */
    int y; /** y position */
    direction_t direction; /** direction associate with tge position */
} position_t;


/**
 * @brief client_ai structure
 *
 * the client_ai structure is used to store the information about a AI client
 * (not classic client, it's a player)
 */
typedef struct client_ai_s {
    int fd; /** file descriptor of the client */
    char *team_name; /** team name of the client */
    int num_player; /** num of the player */
    char *buff_in; /** buffer in of the client, this is where the data
    we receive is stored, different action is stored with '\n' for separator */
    char *buff_out; /** buffer out of the client, this is where the data
     we send is stored */
    struct client_ai_s *next; /** next client (for the linked list) */
    struct client_ai_s *prev; /** previous client (for the linked list) */
    int to_disconnect; /** if 1 the client will be disconnected
    by the sevrer
 */
    position_t position; /** position of the client */
    size_t level; /** level of the client */
    size_t TTL; /** time to live of the client*/
    int action; /** is the actual action performed by the client depend
    of TTEA to execute */
    char *option; /** it's option for some command of the client */
    size_t TTEA; /** is the time remaining before the end of the action */
    inventory_t inventory; /** inventory of the client */
} client_ai_t;

/**
 * @brief client_ai list structure
 *
 * the client_ai list structure is used to store the list of the clients
 */
typedef struct client_ai_list_s {
    client_ai_t *head; /** head of the client list */
    client_ai_t *tail; /** tail of the client list */
    int size; /** size of the client list */
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

/**
 * @brief send a message to all clients
 * @param list list of clients
 * @param msg message to send
 */
void send_to_all_ai(client_ai_list_t *list, char *msg);

/**
 * @brief send a message to all clients except one
 * @param list list of clients
 * @param msg message to send
 * @param client client to not send the message to
 */
void send_to_other_ai(client_ai_list_t *list, char *msg, client_ai_t *client);

/**
 * @brief get a client by his num_player
 * @param list list of clients
 * @param num num(id) of the client
 * @return client_ai_t* client found, NULL if not found
 */
client_ai_t *get_client_ai_by_num(client_ai_list_t *ai, int id);

/**
 * @brief count the number of clients by team and level
 * @param ai list of clients
 * @param team_name team name to count
 * @param level level to count
 * @return return the number of clients matching the team and level
 */
size_t count_client_ai_by_team_level(client_ai_list_t *ai, char *team_name,
    size_t level);
#endif //SERVER_CLIENT_AI_H
