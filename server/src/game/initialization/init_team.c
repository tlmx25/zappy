/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init_team.c
*/

#include <string.h>
#include "server.h"

bool team_init(server_t *server)
{
    for (server->world->nbr_teams = 0;
        server->option->names[server->world->nbr_teams] != NULL;
        server->world->nbr_teams++);
    server->world->teams = malloc(sizeof(team_t) * server->world->nbr_teams);
    if (server->world->teams == NULL)
        return (false);
    for (int i = 0; i < server->world->nbr_teams; i++) {
        server->world->teams[i].name = strdup(server->option->names[i]);
        server->world->teams[i].max_clients = server->option->clients_nb;
        server->world->teams[i].current_clients = 0;
    }
    return true;
}
