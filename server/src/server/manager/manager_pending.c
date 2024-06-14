/*
** EPITECH PROJECT, 2024
** server
** File description:
** manager_pending
*/

#include "graphique_cmd.h"
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
    cmd_msz(server, client, NULL);
    cmd_sgt(server, client, NULL);
    cmd_mct(server, client, NULL);
    cmd_tna(server, client, NULL);
    enw_all_egg(server, client);
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

static void send_data_graphic(server_t *server, client_ai_t *client,
    egg_t *egg)
{
    char buffer[2048] = {0};

    send_to_all_graphic_arg(server->graphic_clients, "pnw %i %i %i %i %i %s\n",
    client->num_player, client->position.x, client->position.y,
    client->position.direction + 1, client->level, client->team_name);
    cmd_pin_create_response(client, buffer, client->num_player);
    send_to_all_graphic(server->graphic_clients, buffer);
    send_to_all_graphic_arg(server->graphic_clients, "ebo %i\n", egg->id);
    delete_egg_from_list(server->world->eggs, egg, true);
}

bool convert_pending_client_to_ai(server_t *server,
    client_t *client, char *name)
{
    client_ai_t *new_client = check_eggs(client->fd, name, client, server);
    egg_t *egg;

    if (new_client == NULL)
        return false;
    egg = get_egg_by_team(server->world->eggs, name);
    new_client->position = egg->pos;
    new_client->fd = client->fd;
    add_client_ai_to_list(server->ai_clients, new_client);
    debug_pending_to_ai(client, new_client, server);
    client_is_converted(server->pending_clients, client);
    send_data_graphic(server, new_client, egg);
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
