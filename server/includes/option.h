/*
** EPITECH PROJECT, 2024
** server
** File description:
** option
*/

#ifndef SERVER_OPTION_H
    #define SERVER_OPTION_H
    #include <unistd.h>

typedef struct option_s {
    int port;
    int width;
    int height;
    int clients_nb;
    int freq;
    char **names;
} option_t;

typedef struct option_tab_s {
    char *flag;
    int (*func)(option_t *option, const char **av, int i);
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

/**
 * @brief parse debug option
 * @param option option struct
 * @param av command line
 * @param i index of the option
 * @return int new index
 */
int parse_debug(option_t *option, const char **av, int i);
#endif //SERVER_OPTION_H
