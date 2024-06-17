/*
** EPITECH PROJECT, 2024
** server
** File description:
** exec_ai
*/

#include "commands_ai.h"
#include "server.h"
#include "graphique_cmd.h"

static const command_ai_t commands[] = {
    {"Forward", 7, forward_command, NULL},
    {"Right", 7, right_command, NULL},
    {"Left", 7, left_command, NULL},
    {"Connect_nbr", 0, NULL, connect_nbr_command},
    {"Inventory", 1, inventory_command, NULL},
    {"Fork", 42, fork_command, prefork_command},
    {"Look", 7, look_command, NULL},
    {NULL, 0, NULL, NULL}
};

//    {"Broadcast", 7, broadcast_command},
//    {"Eject", 7, eject_command},
//    {"Take", 7, take_command},
//    {"Set", 7, set_command},

static int check_death(server_t *server, client_ai_t *tmp)
{
    tmp->TTL -= 1 * server->option->freq;
    tmp->TTL = (tmp->TTL <= 0) ? 0 : tmp->TTL;
    if (tmp->TTL == 0) {
        if (tmp->inventory.food != 0) {
            tmp->inventory.food--;
            debug_print("Client AI %i TTL has %i food left\n",
            tmp->num_player, tmp->inventory.food);
            tmp->TTL = 126;
        } else {
            add_to_buffer(&tmp->buff_out, "dead\n", false);
            send_to_all_graphic_arg(server->graphic_clients, "pdi %i\n",
            tmp->num_player);
            debug_print("Client AI %i is dead\n", tmp->num_player);
            return 1;
        }
    }
    return 0;
}

void exec_command_ai(server_t *server, client_ai_t *client)
{
    if (client->action == -1)
        return;
    if (client->TTEA > 0)
        client->TTEA--;
    if (client->TTEA != 0)
        return;
    if (commands[client->action].func != NULL) {
        debug_print("Client AI %i is executing action %s\n",
        client->num_player,
        commands[client->action].command);
        commands[client->action].func(server, client);
    }
    client->action = -1;
}

static void reconstruct_buff(client_ai_t *client, char **tab, server_t *server)
{
    free(client->buff_in);
    client->buff_in = NULL;
    if (tab[1] == NULL) {
        client->buff_in = NULL;
        if (commands[client->action].prefunc) {
            debug_print("Client AI %i is executing prefunc %s\n",
            client->num_player, commands[client->action].command);
            commands[client->action].prefunc(server, client);
        }
        return;
    }
    client->buff_in = my_array_to_str_separator((char const **)&tab[1], "\n");
}

static void invalid_command(client_ai_t *client, char *command)
{
    add_to_buffer(&client->buff_out, "ko\n", false);
    debug_print("Client AI %i has invalid command [%s]\n",
    client->num_player, command);
}

static void check_command(server_t *server, client_ai_t *client)
{
    char **tab = NULL;

    if (client->action != -1 || client->buff_in == NULL)
        return;
    tab = my_str_to_word_array(client->buff_in, "\n");
    if (tab == NULL || tab[0] == NULL)
        return;
    for (int i = 0; commands[i].command != NULL; i++) {
        if (my_strcmp(commands[i].command, tab[0]) == 0) {
            client->action = i;
            client->TTEA = FREQ(commands[i].TTEA);
            break;
        }
    }
    if (client->action == -1)
        invalid_command(client, tab[0]);
    reconstruct_buff(client, tab, server);
    free_tab(tab);
}

static void meteor_shower(server_t *server)
{
    static int meteor = 0;
    static struct timeval last_exec;
    static bool first = true;

    meteor++;
    if (meteor == FREQ(20)) {
        meteor = 0;
        debug_print("Meteor shower\n");
        distribute_ressources(server);
        send_to_all_graphic_func(server, NULL, cmd_mct);
    }
}

void exec_ai_list(server_t *server)
{
    client_ai_t *tmp = server->ai_clients->head;
    static int meteor = 0;
    static struct timeval last_exec;
    static bool first = true;

    if (first) {
        last_exec = get_current_time();
        first = false;
    }
    for (; tmp; tmp = tmp->next) {
        check_command(server, tmp);
        if (get_seconds_elapsed(last_exec) >= 1.0f) {
            check_death(server, tmp);
            exec_command_ai(server, tmp);
            meteor_shower(server);
            last_exec = get_current_time();
        }
    }
}
