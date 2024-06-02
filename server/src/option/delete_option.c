/*
** EPITECH PROJECT, 2024
** server
** File description:
** delete_option
*/

#include <stdlib.h>
#include "option.h"
#include "my.h"

void delete_option(option_t *option)
{
    if (option == NULL)
        return;
    if (option->names != NULL)
        free_tab(option->names);
    free(option);
}
