/*
** EPITECH PROJECT, 2024
** server
** File description:
** time_utils
*/

#include "time_utils.h"

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}

double get_seconds_elapsed(struct timeval start) {
    struct timeval now;
    gettimeofday(&now, NULL);

    double elapsed = (now.tv_sec - start.tv_sec) + (now.tv_usec - start.tv_usec) / 1e6;
    return elapsed;
}
