/*
** EPITECH PROJECT, 2024
** server
** File description:
** parse_name
*/

#include <stdio.h>
#include <stdlib.h>
#include "option.h"
#include "my.h"

int parse_name(option_t *option, const char **av, int i)
{
    int nb_names = i + 1;

    if (av[i + 1] == NULL || av[i + 1][0] == '-') {
        dprintf(2, "names is not specify\n");
        return -1;
    }
    for (; av[nb_names] != NULL && av[nb_names][0] != '-'; nb_names++);
    option->names = malloc(sizeof(char *) * (nb_names - i + 1));
    if (option->names == NULL)
        return -1;
    for (int j = i + 1; j < nb_names; j++)
        option->names[j - i - 1] = my_strdup(av[j]);
    option->names[nb_names - i - 1] = NULL;
    return (nb_names);
}
