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

static void debug_pending_to_ai(client_t *client, client_ai_t *new_client,
    server_t *server)
{
    int nb_egg = count_eggs_by_team(server->world->eggs,
        new_client->team_name);
    char tmp[1024];

    debug_print("Client %d is a AI client, team [%s], is player id is [%i]",
    client->fd, new_client->team_name, new_client->num_player);
    printf(" and his position is [%i, %i]\n", new_client->position.x,
    new_client->position.y);
    snprintf(tmp, 1024, "%i\n%i %i\n", nb_egg,
    new_client->position.x, new_client->position.y);
    add_to_buffer(&new_client->buff_out, tmp, false);
}

static client_ai_t *check_eggs(int fd, char *name, client_t *client,
    server_t *server)
{
    int eggs = count_eggs_by_team(server->world->eggs, name);

    if (eggs == 0) {
        add_to_buffer(&client->buffer_out, "ko\n", false);
        debug_print("Client %d try to become ai [%s] but not have eggs\n",
        client->fd, name);
        free(client->buffer_in);
        client->buffer_in = NULL;
        return NULL;
    }
    return create_client_ai(fd, name, (position_t){0, 0, 0});
}

bool convert_pending_client_to_ai(server_t *server,
    client_t *client, char *name)
{
    client_ai_t *new_client = check_eggs(client->fd, name, client, server);
    position_t pos;

    if (new_client == NULL)
        return false;
    pos = get_egg_by_team(server->world->eggs, name)->pos;
    new_client->position = pos;
    delete_egg_by_team_position(server->world->eggs, name, pos);
    new_client->fd = client->fd;
    add_client_ai_to_list(server->ai_clients, new_client);
    debug_pending_to_ai(client, new_client, server);
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
