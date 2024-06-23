/*
** EPITECH PROJECT, 2024
** server
** File description:
** broadcast
*/

#include "commands_ai.h"

int get_dir(client_ai_t *em, client_ai_t *rc)
{
    int x = rc->position.x - em->position.x;
    int y = rc->position.y - em->position.y;

    if (x > 0 && y > 0)
        return DIR(2, 4, 6, 8);
    if (x > 0 && y < 0)
        return DIR(4, 6, 8, 2);
    if (x < 0 && y > 0)
        return DIR(8, 2, 4, 6);
    if (x < 0 && y < 0)
        return DIR(6, 8, 2, 4);
    if (x > 0 && y == 0)
        return DIR(3, 5, 7, 1);
    if (x < 0 && y == 0)
        return DIR(7, 1, 3, 5);
    if (x == 0 && y > 0)
        return DIR(1, 3, 5, 7);
    if (x == 0 && y < 0)
        return DIR(5, 7, 1, 3);
    return 0;
}

void send_broadcast(client_ai_t *em, client_ai_t *rc)
{
    char buffer[8192] = {0};
    int dir = get_dir(em, rc);

    if (em->option == NULL)
        return;
    snprintf(buffer, 8192, "message %i, %s\n", dir, em->option);
    add_to_buffer(&rc->buff_out, buffer, false);
}

void broadcast_command(server_t *server, client_ai_t *client)
{
    for (client_ai_t *tmp = server->ai_clients->head; tmp != NULL;
    tmp = tmp->next) {
        if (tmp == client)
            continue;
        send_broadcast(client, tmp);
    }
    debug_print("Client AI %i broadcasted message [%s]\n",
    client->num_player, client->option);
    add_to_buffer(&client->buff_out, "ok\n", false);
    send_to_all_graphic_arg(server->graphic_clients, "pbc %i %s\n",
    client->num_player, client->option);
}
