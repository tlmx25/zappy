/*
** EPITECH PROJECT, 2024
** server
** File description:
** option
*/

#ifndef SERVER_OPTION_H
    #define SERVER_OPTION_H
    #include <unistd.h>

/**
* @brief A structure to represent server options.
*
* This structure represents server options. It contains the port number,
* the width and height of the world, the number of clients, the
 * frequency of the game,
* and the names of the teams.
*/
typedef struct option_s {
    int port; /**< The port number for the server. */
    int width; /**< The width of the world. */
    int height; /**< The height of the world. */
    int clients_nb; /**< The number of clients. */
    int freq; /**< The frequency of the game. */
    char **names; /**< The names of the teams. */
} option_t;

/**
* @brief A structure to represent a mapping between option flags
* and their parsing functions.
*
* This structure represents a mapping between option flags and their
 * parsing functions.
* It contains a flag string and a function pointer to the corresponding
 * parsing function.
*/
typedef struct option_tab_s {
    char *flag; /**< The option flag. */
    int (*func)(option_t *option, const char **av, int i); /**< The function to
   parse the option. return the number of argument to skip*/
} option_tab_t;


/**
 * @brief delete an option struct
 * @param option option to delete
 */
void delete_option(option_t *option);

/**
 * @brief parse the option from the command line
 * @param av command line
 * @return option_t* the option struct or NULL if error
 */
option_t *parse_option(const char **av);

/**
 * @brief parse the port option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_port(option_t *option, const char **av, int i);

/**
 * @brief parse the width option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_width(option_t *option, const char **av, int i);

/**
 * @brief parse the height option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_height(option_t *option, const char **av, int i);

/**
 * @brief parse the name option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_name(option_t *option, const char **av, int i);

/**
 * @brief parse the clients_nb option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_clients_nb(option_t *option, const char **av, int i);

/**
 * @brief parse the freq option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int I the new index, -1 if error
 */
int parse_freq(option_t *option, const char **av, int i);

/**
 * @brief dump the option struct
 * @param option option struct to dump
 */
void dump_option(option_t *option);
#endif //SERVER_OPTION_H
