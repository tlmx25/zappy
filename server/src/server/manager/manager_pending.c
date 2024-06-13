/*
** EPITECH PROJECT, 2024
** server
** File description:
** manager_pending
*/

#include "client_ai.h"
#include "server.h"

static void is_graphic(server_t *server, client_t *client)
{
    debug_print("Client %d is a graphic client\n", client->fd);
    delete_client_from_list(server->pending_clients, client, false);
    free(client->buffer_in);
    client->team_name = my_strdup("GRAPHIC");
    client->buffer_in = NULL;
    add_client_to_list(server->graphic_clients, client);
}

static void debug_pending_to_ai(client_t *client, client_ai_t *new_client)
{
    debug_print("Client %d is a AI client, team [%s], is player id is [%i]",
    client->fd, new_client->team_name, new_client->num_player);
    printf(" and his position is [%i, %i]\n", new_client->position.x,
    new_client->position.y);
}

static direction_t get_random_direction(void)
{
    int random = rand() % 4;

    if (random == 0)
        return NORTH;
    if (random == 1)
        return EAST;
    if (random == 2)
        return SOUTH;
    return WEST;
}

bool convert_pending_client_to_ai(server_t *server,
    client_t *client, char *name)
{
    client_ai_t *new_client = create_client_ai(client->fd, name,
        (position_t){0, 0, NONE});
    position_t pos = {0, 0, NONE};

    if (new_client == NULL)
        return false;
    if (get_egg_by_team(server->world->eggs, name) != NULL) {
        pos = get_egg_by_team(server->world->eggs, name)->pos;
        new_client->position = pos;
        delete_egg_by_team_position(server->world->eggs, name, pos);
    }
    new_client->fd = client->fd;
    add_client_ai_to_list(server->ai_clients, new_client);
    debug_pending_to_ai(client, new_client);
    client_is_converted(server->pending_clients, client);
    return true;
}

static void error_pending_client(client_t *client, char *name)
{
    add_to_buffer(&client->buffer_out, "ko\n", false);
    debug_print("Client %d is not a valid client : [%s]\n", client->fd, name);
    free(name);
    free(client->buffer_in);
    client->buffer_in = NULL;
}

void manage_pending_client(server_t *server, client_t *client)
{
    char *name = my_clean_string(client->buffer_in, "\n", 0);

    if (client->buffer_in == NULL)
        return;
    if (my_strcmp(name, "GRAPHIC") == 0) {
        is_graphic(server, client);
        free(name);
        return;
    }
    if (check_team_name(server, name)) {
        convert_pending_client_to_ai(server, client, name);
        free(name);
        return;
    }
    error_pending_client(client, name);
}
