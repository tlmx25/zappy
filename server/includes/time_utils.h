/*
** EPITECH PROJECT, 2024
** server
** File description:
** time_utils
*/

#pragma once

#ifndef SERVER_TIME_UTILS_H
    #define SERVER_TIME_UTILS_H
    #include <time.h>
    #include <sys/time.h>
    #include <unistd.h>

typedef struct timeval timeval_t;

/**
 * @brief get the current time
 * @return time_t the current time
 */
timeval_t get_current_time(void);

/**
 * @brief get the seconds elapsed since the start_time
 * @param start_time the start time
 * @return double the seconds elapsed
 */
double get_seconds_elapsed(timeval_t start);
#endif //SERVER_TIME_UTILS_H
