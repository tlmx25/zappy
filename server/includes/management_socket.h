/*
** EPITECH PROJECT, 2024
** PRIVATE_TEAMS
** File description:
** management_socket
*/

#pragma once

#ifndef PRIVATE_TEAMS_MANAGEMENT_SOCKET_H
    #define PRIVATE_TEAMS_MANAGEMENT_SOCKET_H
    #define ERROR 84
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/types.h>

/**
* @brief A structure to represent a select configuration.
*
* This structure represents a select configuration. It contains file
 * descriptor sets for reading and writing,
* a flag to indicate the use of timeout, the maximum file descriptor
 * number, and a timeval structure for timeout.
*/
typedef struct select_s {
    fd_set readfds; /**< File descriptor set for reading. */
    fd_set writefds; /**< File descriptor set for writing. */
    char use_timeout; /**< Flag to indicate the use of timeout. */
    int max_fd; /**< The maximum file descriptor number. */
    struct timeval timeout; /**< Timeval structure for timeout. */
} select_t;

/**
 * @brief create new select struct
 *
 * @return select_t*
 */
select_t *init_select(void);

/**
 * @brief add a fd to the select struct
 *
 * @param fd fd to add
 * @param select select struct
 */
void add_to_select(select_t *select, int fd);

/**
 * @brief reset the select struct
 *
 * @param select select struct to reset
 */
void reset_select(select_t *select);

/**
 * @brief execute the select
 *
 * @param select_config select struct
 * @return int 0 if success, 84 if error
 */
int exec_select(select_t *select_config);

#endif //PRIVATE_TEAMS_MANAGEMENT_SOCKET_H
