/*
** EPITECH PROJECT, 2024
** server
** File description:
** debug_print
*/

#include <stdarg.h>
#include <stdio.h>

int activate_debug_mode(int activate)
{
    static int debug = 0;

    if (activate != -1)
        debug = activate;
    return debug;
}

int debug_active(void)
{
    return activate_debug_mode(-1);
}

void debug_print(const char *format, ...)
{
    va_list args;

    if (debug_active() == 1) {
        printf("\033[34m[DEBUG]\033[0m ");
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}
