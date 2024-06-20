/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/


#ifndef SERVER_SERVER_H
    #define SERVER_SERVER_H
    #define ERROR 84
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "option.h"
    #include "client.h"
    #include "client_ai.h"
    #include "management_socket.h"

typedef enum {
    false,
    true
} bool_t;

/**
* @brief A structure to represent a server.
*
* This structure represents a server. It contains a flag to indicate if the
 * server is running,
* the port number, the socket, a select configuration, lists of pending
 * clients, graphic clients, and AI clients,
* server options, and the world.
*/
typedef struct server_s {
    bool is_running; /**< Flag to indicate if the server is running. */
    int port; /**< The port number for the server. */
    int socket; /**< The socket for the server. */
    select_t *select_config; /**< The select configuration for the server. */
    client_list_t *pending_clients; /**< List of pending clients. */
    client_list_t *graphic_clients; /**< List of graphic clients. */
    client_ai_list_t *ai_clients; /**< List of AI clients. */
    option_t *option; /**< Server options. */
    world_t *world; /**< The world for the server. */
} server_t;

/**
* @brief A structure to represent a command.
*
* This structure represents a command. It contains the command string, a
 * function pointer to execute the command,
* and the number of arguments required for the command.
*/
typedef struct command_s {
    char *command; /**< The command string. */
    void (*func)(server_t *server, client_t *client, char const **command); /**
 * < Function to execute the command. */
    int nb_args; /**< The number of arguments required for the command. */
} command_t;

typedef struct command_ai_s {
    char *command;
    void (*func)(server_t *server, client_ai_t *client, char const **command);
    int nb_args;
} command_ai_t;

/**
 * @brief read message from a socket
 * @param fd fd of the socket
 * @return char* containing the message or NULL if error
 */
char *read_socket(int fd);

/**
 * @brief write message to a socket
 * @param fd fd of the socket
 * @param str message to write
 * @return int 0 if success, 84 if error
 */
int write_socket(int fd, char *str);

/**
 * @brief Create a new server and parse option
 * @param av information from the command line (option)
 * @return server_t* the server or NULL if error
 */
server_t *create_server(char **av);

/**
 * @brief Delete a server
 *
 * @param server server to delete
 */
void delete_server(server_t *server);

/**
 * @brief run the server
 * @param server server to run
 */
void run_server(server_t *server);

/**
 * @brief manage server, read and write on socket of client and
 * accept new client
 * @param server server to manage
 */
void manage_server(server_t *server);

/**
 * @brief check if name is in team list
 * @param server the server containing option
 * @param team_name the name of the team to check
 * @return int , 1 if the team exist or 0 if not
 */
int check_team_name(server_t *server, char *team_name);

/**
 * @brief read request from list (pending or graphic) and add it to buffer_in
 * @param server server for info and context
 * @param list list to read from
 */
void read_pending_graphic_list(server_t *server, client_list_t *list);

/**
 * @brief write request from buffer_out from the list (pending or graphic)
 * @param server server for info and context
 * @param list list to write from
 */
void write_pending_graphic_list(server_t *server, client_list_t *list);

/**
 * @brief read ai list and add it to buffer_in
 * @param server server for info and context
 * @param list list to read from
 */
void read_ai_list(server_t *server, client_ai_list_t *list);

/**
 * @brief write ai list from buffer_out
 * @param server server for info and context
 * @param list list to write from
 */
void write_ai_list(server_t *server, client_ai_list_t *list);

/**
 * @brief add a string to a buffer, add '\n' at the end if not present
 * @param buffer pointer to the buffer to add request
 * @param str string to add to the buffer
 * @param free_str if true, free str after adding it to buffer
 */
void add_to_buffer(char **buffer, char *str, bool_t free_str);

/**
 * @brief execute the command of the client graphic
 * @param server server for info and context
 */
void exec_graphic_list(server_t *server);
#endif //SERVER_SERVER_H
