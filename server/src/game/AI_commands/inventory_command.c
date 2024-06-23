/*
** EPITECH PROJECT, 2024
** server
** File description:
** inventory_command
*/

#include "commands_ai.h"

void inventory_command(UNUSED server_t *server, client_ai_t *client)
{
    char buff[2048];

    snprintf(buff, 2048, "[food %d, linemate %d, deraumere %d, sibur %d,"
    " mendiane %d, phiras %d, thystame %d]\n", client->inventory.food,
    client->inventory.linemate, client->inventory.deraumere,
    client->inventory.sibur, client->inventory.mendiane,
    client->inventory.phiras, client->inventory.thystame);
    debug_print("Client AI %i inventory : %s", client->num_player, buff);
    add_to_buffer(&client->buff_out, buff, false);
}
