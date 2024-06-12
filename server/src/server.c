/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#include "server.h"

static void set_fds(server_t *server)
{
    reset_select(server->select_config);
    add_to_select(server->select_config, server->socket);
    add_to_select(server->select_config, STDIN_FILENO);
    for (client_ai_t *tmp = server->ai_clients->head; tmp; tmp = tmp->next)
        add_to_select(server->select_config, tmp->fd);
    for (client_t *tmp = server->graphic_clients->head; tmp; tmp = tmp->next)
        add_to_select(server->select_config, tmp->fd);
    for (client_t *tmp = server->pending_clients->head; tmp; tmp = tmp->next)
        add_to_select(server->select_config, tmp->fd);
}

static void read_command(server_t *server)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (!FD_ISSET(STDIN_FILENO, &server->select_config->readfds))
        return;
    read = getline(&line, &len, stdin);
    if (read == -1)
        return;
    if (my_strcmp(line, "stop\n") == 0)
        server->is_running = false;
    free(line);
}

void run_server(server_t *server)
{
    while (server->is_running) {
        set_fds(server);
        if (exec_select(server->select_config) == ERROR)
            return;
        read_command(server);
        manage_server(server);
    }
}
