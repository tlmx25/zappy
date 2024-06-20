/*
** EPITECH PROJECT, 2024
** server
** File description:
** look_command
*/

#include "commands_ai.h"

static char *add_object_to_look(char *buffer, int nbr, char *object)
{
    if (nbr == 0)
        return buffer;
    if (buffer && buffer[my_strlen(buffer) - 1] != ' ')
        buffer = my_strcat_free(buffer, " ", true, false);
    for (int i = 0; i < nbr; i++) {
        buffer = my_strcat_free(buffer, object, true, false);
        if (i < nbr - 1)
            buffer = my_strcat_free(buffer, " ", true, false);
    }
    return buffer;
}

static char *get_tile_content(tile_t *tile, client_ai_list_t *player_list)
{
    char *buffer = NULL;
    int nb_players = 0;

    for (client_ai_t *tmp = player_list->head; tmp; tmp = tmp->next) {
        if (tmp->position.x == tile->coordinate.x &&
        tmp->position.y == tile->coordinate.y)
            nb_players++;
    }
    buffer = add_object_to_look(buffer, nb_players, "player");
    buffer = add_object_to_look(buffer, tile->object.food, "food");
    buffer = add_object_to_look(buffer, tile->object.linemate, "linemate");
    buffer = add_object_to_look(buffer, tile->object.deraumere, "deraumere");
    buffer = add_object_to_look(buffer, tile->object.sibur, "sibur");
    buffer = add_object_to_look(buffer, tile->object.mendiane, "mendiane");
    buffer = add_object_to_look(buffer, tile->object.phiras, "phiras");
    buffer = add_object_to_look(buffer, tile->object.thystame, "thystame");
    buffer = my_strcat_free(buffer, ",", true, false);
    return buffer;
}

static tile_t *get_tile_by_pos(server_t *server, position_t position)
{
    int x = position.x;
    int y = position.y;

    if (x < 0)
        x = server->option->width + x;
    if (y < 0)
        y = server->option->height + y;
    if (x >= server->option->width)
        x = x % server->option->width;
    if (y >= server->option->height)
        y = y % server->option->height;
    return &server->world->tiles[y * server->option->width + x];
}

static char *multi_move(direction_t direction,
    position_t position, server_t *server, int nb_moves)
{
    char *buffer = NULL;

    position.direction = direction;
    for (int i = 0; i < nb_moves; i++) {
        buffer = my_strcat_free(buffer, get_tile_content(get_tile_by_pos(
        server, position), server->ai_clients), true, true);
        position = get_next_position(server, position);
    }
    return buffer;
}

static position_t get_next_start_line(position_t position, int line_number,
    server_t *server)
{
    position_t new_pos = position;

    for (int i = 0; i < line_number; i++)
        new_pos = get_next_position(server, new_pos);
    new_pos.direction = turn_left(new_pos.direction);
    for (int i = 0; i < line_number; i++)
        new_pos = get_next_position(server, new_pos);
    new_pos.direction = turn_left(new_pos.direction);
    new_pos.direction = turn_left(new_pos.direction);
    return new_pos;
}

void look_command(server_t *server, client_ai_t *client)
{
    char *buffer = my_strdup("[ ");
    position_t tmp_position;

    for (size_t i = 0; i <= client->level; i++) {
        tmp_position = get_next_start_line(client->position, (int)i, server);
        buffer = my_strcat_free(buffer,
        multi_move(tmp_position.direction, tmp_position,
        server, (int)i * 2 + 1), true, true);
    }
    buffer[my_strlen(buffer) - 1] = '\0';
    buffer = my_strcat_free(buffer, " ]", true, false);
    debug_print("Client AI %i looked around in {%i, %i, %c} : %s\n",
    client->num_player, client->position.x, client->position.y,
    get_direction_char(client->position.direction), buffer);
    add_to_buffer(&client->buff_out, buffer, true);
}
