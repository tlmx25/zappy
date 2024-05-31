/*
** EPITECH PROJECT, 2024
** server
** File description:
** option
*/

#include <stdlib.h>
#include "option.h"
#include "my.h"

static const option_tab_t option_tab[] = {
    {"-p", &parse_port},
    {"-x", &parse_width},
    {"-y", &parse_height},
    {"-n", &parse_name},
    {"-c", &parse_clients_nb},
    {"-f", &parse_freq},
    {NULL, NULL}
};

static int check_is_valid_option(option_t *option, char const *flag)
{
    for (int i = 0; option_tab[i].flag; i++) {
        if (my_strcmp(option_tab[i].flag, flag) == 0)
            return i;
    }
    return -1;
}

static option_t *init_option(void)
{
    option_t *option = calloc(1, sizeof(option_t));

    if (option == NULL)
        return NULL;
    option->port = -1;
    option->width = -1;
    option->height = -1;
    option->clients_nb = -1;
    option->freq = -1;
    option->names = NULL;
    return option;
}

option_t *parse_option(const char **av)
{
    option_t *option = init_option();

    if (option == NULL)
        return NULL;
    for (int i = 1; av[i];) {
//        if () {
//            free_option(option);
//            return NULL;
//        }
    }
    return option;
}
