/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <stdio.h>
#include "server.h"

int main(int ac, char **av)
{
    option_t *option = parse_option((const char **)av);
    if (option == NULL)
        return 84;
    dump_option(option);
    delete_option(option);
    return 0;
}
