/*
** EPITECH PROJECT, 2024
** server
** File description:
** client
*/


#ifndef SERVER_CLIENT_H
    #define SERVER_CLIENT_H
    #include "my.h"


typedef struct client_s {
    int fd;
    char *team_name;
    char *buffer_in;
    char *buffer_out;
    int to_disconnect;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct client_list_s {
    client_t *head;
    client_t *tail;
    int size;
} client_list_t;

/**
 * @brief Create a new client
 *
 * @param fd fd of the client
 * @return client_t* the new client
 */
client_t *create_client(int fd);

/**
 * @brief Create a new client list
 *
 * @return client_list_t* the new client list
 */
client_list_t *create_client_list(void);

/**
 * @brief delete a client from a list
 *
 * @param  client client to delete
 */
void delete_client(client_t *client);

/**
 * @brief add a client to a list
 * @param list list to add the client to
 * @param client client to add
 */
void add_client_to_list(client_list_t *list, client_t *client);

/**
 * @brief create and add a client to a list
 * @param list list to add the client to
 * @param fd new client fd
 */
void create_add_client(client_list_t *list, int fd);

/**
 * @brief clear and delete client list
 * @param list list to delete
 */
void delete_client_list(client_list_t *list);

/**
 * @brief clear list of clients
 * @param list list to clear
 */
void clear_client_list(client_list_t *list);

/**
 * @brief delete a client from a list
 * @param list list to delete the client from
 * @param client client to delete
 * @param delete_client_bool if 1 delete, if 0 just remove it from the list
 */
void delete_client_from_list(client_list_t *list, client_t *client
    , int delete_client_bool);

/**
 * @brief delete a client from a list with a fd
 * @param list list to delete the client from
 * @param fd fd of the client to delete
 * @param delete_client if 1 delete the client, if 0 just remove it
 */
void delete_client_by_fd(client_list_t *list, int fd, int delete_client);

/**
 * @brief get a client from a list with a fd
 * @param list list to get the client from
 * @param fd fd of the client to get
 * @param delete_client if 1 delete the client, if 0 just remove it
 * @return client_t* the client, NULL if not found
 */
client_t *get_client_by_fd(client_list_t *list, int fd);
#endif //SERVER_CLIENT_H
