/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_next_position
*/

#include "server.h"

static void forward_north(server_t *server, position_t *pos)
{
    if (pos->y == 0)
        pos->y = server->option->height - 1;
    else
        pos->y--;
}

static void forward_east(server_t *server, position_t *pos)
{
    if (pos->x == server->option->width - 1)
        pos->x = 0;
    else
        pos->x++;
}

static void forward_south(server_t *server, position_t *pos)
{
    if (pos->y == server->option->height - 1)
        pos->y = 0;
    else
        pos->y++;
}

static void forward_west(server_t *server, position_t *pos)
{
    if (pos->x == 0)
        pos->x = server->option->width - 1;
    else
        pos->x--;
}

position_t get_next_position(server_t *server, position_t pos)
{
    if (pos.direction == NORTH)
        forward_north(server, &pos);
    if (pos.direction == EAST)
        forward_east(server, &pos);
    if (pos.direction == SOUTH)
        forward_south(server, &pos);
    if (pos.direction == WEST)
        forward_west(server, &pos);
    return pos;
}

direction_t turn_right(direction_t direction)
{
    if (direction == NORTH)
        return EAST;
    if (direction == EAST)
        return SOUTH;
    if (direction == SOUTH)
        return WEST;
    if (direction == WEST)
        return NORTH;
    return direction;
}

direction_t turn_left(direction_t direction)
{
    if (direction == NORTH)
        return WEST;
    if (direction == EAST)
        return NORTH;
    if (direction == SOUTH)
        return EAST;
    if (direction == WEST)
        return SOUTH;
    return direction;
}
