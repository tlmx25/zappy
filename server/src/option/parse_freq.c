/*
** EPITECH PROJECT, 2024
** server
** File description:
** parse_freq
*/

#include <stdio.h>
#include "option.h"
#include "my.h"

int parse_freq(option_t *option, const char **av, int i)
{
    if (av[i + 1] == NULL) {
        dprintf(2, "freq is not specify\n");
        return -1;
    }
    if (!my_str_isnum(av[i + 1])) {
        dprintf(2, "invalid freq format\n");
        return -1;
    }
    option->freq = my_getnbr(av[i + 1]);
    return (i + 2);
}
