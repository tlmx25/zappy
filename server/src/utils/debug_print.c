/*
** EPITECH PROJECT, 2024
** server
** File description:
** debug_print
*/

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

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
    time_t current_time;
    struct tm * local_time_info;

    if (debug_active() == 1) {
        time(&current_time);
        local_time_info = localtime(&current_time);
        printf("\033[34m[DEBUG %02d:%02d:%02d]\033[0m ",
            local_time_info->tm_hour,
            local_time_info->tm_min,
            local_time_info->tm_sec);
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}
