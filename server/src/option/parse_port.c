/*
** EPITECH PROJECT, 2024
** server
** File description:
** parse_port
*/

#include "option.h"
#include "my.h"
#include <stdio.h>

int parse_port(option_t *option, const char **av, int i)
{
    if (av[i + 1] == NULL) {
        dprintf(2, "port is not specify\n");
        return -1;
    }
    if (!my_str_isnum(av[i + 1])) {
        dprintf(2, "invalid port format\n");
        return -1;
    }
    option->port = my_getnbr(av[i + 1]);
    return (i + 2);
}
