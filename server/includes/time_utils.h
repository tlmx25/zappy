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

/**
 * @brief get the current time
 * @return time_t the current time
 */
struct timeval get_current_time();

/**
 * @brief get the seconds elapsed since the start_time
 * @param start_time the start time
 * @return double the seconds elapsed
 */
double get_seconds_elapsed(struct timeval start);
#endif //SERVER_TIME_UTILS_H
