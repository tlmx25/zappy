/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** debug.h
*/

#ifndef ZAPPY_DEBUG_H
    #define ZAPPY_DEBUG_H

    #include <stdarg.h>
    #include <stdio.h>

    int activate_debug_mode(int activate);
    int debug_active(void);
    void debug_print(const char *format, ...);

#endif //ZAPPY_DEBUG_H