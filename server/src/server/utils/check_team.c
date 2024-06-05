/*
** EPITECH PROJECT, 2024
** server
** File description:
** check_team
*/

#include "server.h"

int check_team_name(server_t *server, char *team_name)
{
    char **server_teams = server->option->names;

    for (int i = 0; server_teams[i] != NULL; i++) {
        if (my_strcmp(server_teams[i], team_name) == 0)
            return 1;
    }
    return 0;
}
