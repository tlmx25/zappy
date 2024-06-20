/*
** EPITECH PROJECT, 2024
** server
** File description:
** client
*/


#ifndef SERVER_CLIENT_H
    #define SERVER_CLIENT_H
    #include "my.h"


/**
 * @brief client structure
 *
 * this structure is used to store the information about a classic client
 * (not AI client)
 */
typedef struct client_s {
    int fd; /** file descriptor of the client */
    char *team_name; /** team name of the client */
    char *buffer_in; /** buffer in of the client, this is where the data
    we receive is stored */
    char *buffer_out; /** buffer out of the client, this is where the data
     we send is stored */
    int to_disconnect; /** if 1 the client will be disconnected
    by the sevrer */
    struct client_s *next; /** next client (for the linked list) */
    struct client_s *prev; /** previous client (for the linked list) */
} client_t;

/**
 * @brief client list structure
 *
 * this structure is used to store the list of the clients
 */
typedef struct client_list_s {
    client_t *head; /** head of the client list */
    client_t *tail; /** tail of the client list */
    int size; /** size of the client list */
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

/**
 * @brief send message to all client in the list
 * @param list
 * @param msg
 */
void send_to_all_graphic(client_list_t *list, char *msg);

/**
 * @brief send message to all client in the list with format
 * @param list list of clients
 * @param format format of the message
 * @param ... variable arguments
 */
void send_to_all_graphic_arg(client_list_t *list, char *format, ...);

/**
 * @brief deleting client from list without close fd
 * @param list list of clients
 * @param client client to delete
 */
void client_is_converted(client_list_t *list, client_t *client);
#endif //SERVER_CLIENT_H
