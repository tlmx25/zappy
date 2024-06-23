/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init_team.c
*/

#include <time.h>
#include <string.h>
#include "server.h"

static bool eggs_init(server_t *server)
{
    debug_print("Init eggs\n");
    srand(time(NULL));
    server->world->eggs = create_egg_list();
    if (server->world->eggs == NULL)
        return false;
    for (int i = 0; i < server->world->nbr_teams; i++) {
        for (int j = 0; j < server->option->clients_nb; j++) {
            create_add_egg_to_list(server->world->eggs,
                (position_t){rand() % server->option->width,
                    rand() % server->option->height, rand() % 4},
                server->option->names[i]);
        }
    }
    return true;
}

void enw_all_egg(server_t *server, client_t *client)
{
    char *buffer = NULL;
    egg_t *tmp = server->world->eggs->head;

    debug_print("ENW ALL EGGS\n");
    for (; tmp != NULL; tmp = tmp->next) {
        buffer = malloc(sizeof(char) * 2048);
        sprintf(buffer, "enw %i %i %i %i\n", tmp->id, -1, tmp->pos.x,
            tmp->pos.y);
        add_to_buffer(&client->buffer_out, buffer, true);
    }
}

static bool incantation_init(server_t *server)
{
    debug_print("Init incantation\n");
    server->world->incantations = create_incantation_list();
    if (server->world->incantations == NULL)
        return false;
    return true;
}

bool team_init(server_t *server)
{
    debug_print("Init teams\n");
    if (server->option->names == NULL)
        return false;
    for (server->world->nbr_teams = 0;
        server->option->names[server->world->nbr_teams] != NULL;
        server->world->nbr_teams++);
    server->world->teams = malloc(sizeof(team_t) * server->world->nbr_teams);
    if (server->world->teams == NULL)
        return false;
    for (int i = 0; i < server->world->nbr_teams; i++) {
        server->world->teams[i].name = strdup(server->option->names[i]);
        server->world->teams[i].max_clients = server->option->clients_nb;
        server->world->teams[i].current_clients = 0;
    }
    if (incantation_init(server) == false)
        return false;
    if (eggs_init(server) == false)
        return false;
    return true;
}
