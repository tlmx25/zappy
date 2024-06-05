/*
** EPITECH PROJECT, 2024
** server
** File description:
** parse_client_nb
*/

#include <stdio.h>
#include "option.h"
#include "my.h"

int parse_clients_nb(option_t *option, const char **av, int i)
{
    if (av[i + 1] == NULL) {
        dprintf(STDERR_FILENO, "Error: -c option requires an argument\n");
        return -1;
    }
    if (my_str_isnum(av[i + 1]) == 0) {
        dprintf(STDERR_FILENO, "Error: invalid argument for -c option\n");
        return -1;
    }
    option->clients_nb = my_getnbr(av[i + 1]);
    return (i + 2);
}
