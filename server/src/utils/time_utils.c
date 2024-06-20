/*
** EPITECH PROJECT, 2024
** server
** File description:
** time_utils
*/

#include "time_utils.h"

timeval_t get_current_time(void)
{
    timeval_t tv;

    gettimeofday(&tv, NULL);
    return tv;
}

double get_seconds_elapsed(timeval_t start)
{
    timeval_t now;
    double tmp1;
    double tmp2;
    double elapsed;

    gettimeofday(&now, NULL);
    tmp1 = (now.tv_sec - start.tv_sec);
    tmp2 = (now.tv_usec - start.tv_usec) / 1e6;
    elapsed = tmp1 + tmp2;
    return elapsed;
}
