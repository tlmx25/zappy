/*
** EPITECH PROJECT, 2024
** server
** File description:
** parse_width
*/

#include <stdio.h>
#include "option.h"
#include "my.h"

int parse_width(option_t *option, const char **av, int i)
{
    if (av[i + 1] == NULL) {
        dprintf(2, "width is not specify\n");
        return -1;
    }
    if (!my_str_isnum(av[i + 1])) {
        dprintf(2, "invalid width format\n");
        return -1;
    }
    option->width = my_getnbr(av[i + 1]);
    return (i + 2);
}

int parse_height(option_t *option, const char **av, int i)
{
    if (av[i + 1] == NULL) {
        dprintf(2, "height is not specify\n");
        return -1;
    }
    if (!my_str_isnum(av[i + 1])) {
        dprintf(2, "invalid height format\n");
        return -1;
    }
    option->height = my_getnbr(av[i + 1]);
    return (i + 2);
}
