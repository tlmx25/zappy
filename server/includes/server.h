/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#ifndef SERVER_SERVER_H
    #define SERVER_SERVER_H
    #define ERROR 84
    #define UNUSED __attribute__((unused))
    #define FREQ(x) (x / server->option->freq)
    #define PLNUM(x) (x[0] == '#') ? &x[1] : x
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include "option.h"
    #include "client.h"
    #include "client_ai.h"
    #include "management_socket.h"
    #include "world.h"
    #include "time_utils.h"

typedef struct server_s {
    bool is_running;
    int port;
    int socket;
    select_t *select_config;
    client_list_t *pending_clients;
    client_list_t *graphic_clients;
    client_ai_list_t *ai_clients;
    option_t *option;
    world_t *world;
} server_t;

typedef struct command_s {
    char *command;
    void (*func)(server_t *server, client_t *client, char const **command);
    int nb_args;
} command_t;

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
void add_to_buffer(char **buffer, char *str, bool free_str);

/**
 * @brief execute the command of the client graphic
 * @param server server for info and context
 */
void exec_graphic_list(server_t *server);

/**
 * @brief manage request of pending client client
 * @param server server
 * @param client client to manage request
 */
void manage_pending_client(server_t *server, client_t *client);

/**
 * @brief exec action from pending client
 * @param server
 */
void exec_pending(server_t *server);

/**
 * @brief activate debug mode
 * @param activate 1 to activate, 0 to deactivate or -1 to get the status
 * @return int 1 if activated, 0 if deactivated
 */
int activate_debug_mode(int activate);

/**
 * @brief check if debug mode is active
 * @return int 1 if activated, 0 if deactivated
 */
int debug_active(void);

/**
 * @brief print a debug message
 * @param format format of the message
 * @param ... arguments of the message
 */
void debug_print(const char *format, ...);

/**
 * @brief manage request of client ai
 * @param server
 */
void exec_ai_list(server_t *server);

/**
 * @brief distribute ressources to the world
 * @param server server containing the world
 */
void distribute_ressources(server_t *server);

/**
 * @brief get the next position of a client depending on the direction
 * @param server server for info and context
 * @param pos position of the client
 * @return new position of the client
 */
position_t get_next_position(server_t *server, position_t pos);

/**
 * @brief get new direction after turning right
 * @param direction actual direction
 * @return return new direction
 */
direction_t turn_right(direction_t direction);

/**
 * @brief get new direction after turning left
 * @param direction actual direction
 * @return return new direction
 */
direction_t turn_left(direction_t direction);
#endif //SERVER_SERVER_H
