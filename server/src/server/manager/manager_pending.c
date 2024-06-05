/*
** EPITECH PROJECT, 2024
** server
** File description:
** manager_pending
*/

#include "server.h"


static void is_graphic(server_t *server, client_t *client)
{
    delete_client_from_list(server->pending_clients, client, false);
    add_client_to_list(server->graphic_clients, client);
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
    //TODO: client ai et converter
}
