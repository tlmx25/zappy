/*
** EPITECH PROJECT, 2024
** server
** File description:
** debug_option
*/

#include "server.h"

int parse_debug(UNUSED option_t *option, UNUSED const char **av, int i)
{
    activate_debug_mode(1);
    return (i + 1);
}
