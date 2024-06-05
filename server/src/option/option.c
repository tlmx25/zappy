/*
** EPITECH PROJECT, 2024
** server
** File description:
** option
*/

#include <stdio.h>
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

static int check_is_valid_option(char const *flag)
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

static void *invalid_option(option_t *option, const char **av, int i)
{
    dprintf(STDERR_FILENO, "Error: invalid option %s\n", av[i]);
    delete_option(option);
    return NULL;
}

static option_t *check_option(option_t *option)
{
    int error = 0;

    if (option->width == -1)
        error = dprintf(2, "width is not specify\n");
    if (option->port == -1)
        error = dprintf(2, "port is not specify\n");
    if (option->height == -1)
        error = dprintf(2, "height is not specify\n");
    if (option->clients_nb == -1)
        error = dprintf(2, "clients_nb is not specify\n");
    if (option->freq == -1)
        error = dprintf(2, "freq is not specify\n");
    if (option->names == NULL)
        error = dprintf(2, "names is not specify\n");
    if (error) {
        delete_option(option);
        return NULL;
    }
    return option;
}

option_t *parse_option(const char **av)
{
    option_t *option = init_option();
    int index;

    if (option == NULL)
        return NULL;
    for (int i = 1; av[i];) {
        index = check_is_valid_option(av[i]);
        if (index == -1)
            return invalid_option(option, av, i);
        i = option_tab[index].func(option, av, i);
        if (i == -1) {
            delete_option(option);
            return NULL;
        }
    }
    return check_option(option);
}

void dump_option(option_t *option)
{
    printf("port: %d\n", option->port);
    printf("width: %d\n", option->width);
    printf("height: %d\n", option->height);
    printf("clients_nb: %d\n", option->clients_nb);
    printf("freq: %d\n", option->freq);
    for (int i = 0; option->names && option->names[i]; i++)
        printf("name %i: %s\n", i, option->names[i]);
}
