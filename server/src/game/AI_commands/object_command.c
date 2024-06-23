/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** object_command.c
*/

#include <string.h>
#include "server.h"

static tile_t *get_tile_by_pos(server_t *server, position_t position)
{
    int x = position.x;
    int y = position.y;

    if (x < 0)
        x = server->option->width + x;
    if (y < 0)
        y = server->option->height + y;
    if (x >= server->option->width)
        x = x % server->option->width;
    if (y >= server->option->height)
        y = y % server->option->height;
    return &server->world->tiles[y * server->option->width + x];
}

static size_t getobject(char *option)
{
    if (option == NULL)
        return -1;
    if (strcmp(option, "food") == 0)
        return 0;
    if (strcmp(option, "linemate") == 0)
        return 1;
    if (strcmp(option, "deraumere") == 0)
        return 2;
    if (strcmp(option, "sibur") == 0)
        return 3;
    if (strcmp(option, "mendiane") == 0)
        return 4;
    if (strcmp(option, "phiras") == 0)
        return 5;
    if (strcmp(option, "thystame") == 0)
        return 6;
    return -1;
}

static bool modifie_inventory3(inventory_t *to_add, inventory_t *to_remove,
    size_t obj)
{
    if (obj == 3 && to_remove->sibur > 0) {
        to_add->sibur++;
        to_remove->sibur--;
        return true;
    }
    return false;
}

static bool modifie_inventory2(inventory_t *to_add, inventory_t *to_remove,
    size_t obj)
{
    if (obj == 4 && to_remove->mendiane > 0) {
        to_add->mendiane++;
        to_remove->mendiane--;
        return true;
    }
    if (obj == 5 && to_remove->phiras > 0) {
        to_add->phiras++;
        to_remove->phiras--;
        return true;
    }
    if (obj == 6 && to_remove->thystame > 0) {
        to_add->thystame++;
        to_remove->thystame--;
        return true;
    }
    return modifie_inventory3(to_add, to_remove, obj);
}

bool modifie_inventory(inventory_t *to_add, inventory_t *to_remove, size_t obj)
{
    if (obj == 0 && to_remove->food > 0) {
        printf("food = %i\n", to_remove->food);
        to_add->food++;
        to_remove->food--;
        return true;
    }
    if (obj == 1 && to_remove->linemate > 0) {
        to_add->linemate++;
        to_remove->linemate--;
        return true;
    }
    if (obj == 2 && to_remove->deraumere > 0) {
        to_add->deraumere++;
        to_remove->deraumere--;
        return true;
    }
    return modifie_inventory2(to_add, to_remove, obj);
}

void take_command(server_t *server, client_ai_t *client)
{
    tile_t *tile = get_tile_by_pos(server, client->position);
    size_t obj = getobject(client->option);

    debug_print("Client AI %i is executing action Take on object \"%s\""
                " in pos : %i %i\n", client->num_player, client->option,
                client->position.x, client->position.y);
    if (obj == (size_t)-1)
        return add_to_buffer(&client->buff_out, "ko\n", false);
    if (modifie_inventory(&client->inventory, &tile->object, obj) == false)
        return add_to_buffer(&client->buff_out, "ko\n", false);
    add_to_buffer(&client->buff_out, "ok\n", false);
    send_to_all_graphic_arg(server->graphic_clients, "pgt %i %li\n",
    client->num_player, obj);
    send_to_all_graphic_arg(server->graphic_clients,
    "bct %i %i %d %d %d %d %d %d %d\n",
    client->position.x, client->position.y, tile->object.food,
    tile->object.linemate, tile->object.deraumere, tile->object.sibur,
    tile->object.mendiane, tile->object.phiras, tile->object.thystame);
}

void set_command(server_t *server, client_ai_t *client)
{
    tile_t *tile = get_tile_by_pos(server, client->position);
    size_t obj = getobject(client->option);

    debug_print("Client AI %i is executing action set on object \"%s\""
                " in pos : %i %i\n", client->num_player, client->option,
                client->position.x, client->position.y);
    if (obj == (size_t)-1)
        return add_to_buffer(&client->buff_out, "ko\n", false);
    if (modifie_inventory(&tile->object, &client->inventory, obj) == false)
        return add_to_buffer(&client->buff_out, "ko\n", false);
    add_to_buffer(&client->buff_out, "ok\n", false);
    send_to_all_graphic_arg(server->graphic_clients, "pdr %i %li\n",
    client->num_player, obj);
    send_to_all_graphic_arg(server->graphic_clients,
    "bct %i %i %d %d %d %d %d %d %d\n",
    client->position.x, client->position.y, tile->object.food,
    tile->object.linemate, tile->object.deraumere, tile->object.sibur,
    tile->object.mendiane, tile->object.phiras, tile->object.thystame);
}
