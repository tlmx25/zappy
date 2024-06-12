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

/**
 * @brief Activate or deactivate debug mode
 * @param activate 1 to activate, 0 to deactivate
 */
int activate_debug_mode(int activate);

/**
 * @brief Check if debug mode is active
 * @return 1 if active, 0 if not
 */
int debug_active(void);

/**
 * @brief Print a debug message
 * @param format format of the message
 */
void debug_print(const char *format, ...);

#endif //ZAPPY_DEBUG_H