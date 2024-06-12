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
    delete_client_from_list(server->pending_clients, client, false);
    add_client_to_list(server->graphic_clients, client);
}

bool_t WARN_RESULT convert_pending_client_to_ai(server_t *server,
    client_t *client, char *name)
{
    client_ai_t *new_client = create_client_ai(client->fd, client->buffer_in,
        (position_t){0, 0, NONE});

    if (new_client == NULL)
        return false;
    // TODO : UPDATE POSITION WITH EGG
    new_client->fd = client->fd;
    new_client->team_name = my_strdup(name);
    if (server->ai_clients->size == 0)
        server->ai_clients->head = new_client;
    else
        add_client_ai_to_list(server->ai_clients, new_client);
    delete_client_from_list(server->pending_clients, client, false);
    return true;
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
    for (int i = 0; server->option->names[i] != NULL; i++) {
        if (my_strcmp(server->option->names[i], name) == 0) {
            convert_pending_client_to_ai(server, client, name);
            free(name);
            return;
        }
    }
}
