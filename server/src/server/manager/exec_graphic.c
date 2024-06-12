/*
** EPITECH PROJECT, 2024
** server
** File description:
** exec_graphic
*/

#include "server.h"

static const command_t GRAPHIC_COMMANDS[] = {
    {NULL, NULL, 0},
};

static void exec_command(server_t *server, client_t *client,
    char const **tab, int i)
{
    int len = my_arrsize(tab);

    if ((len - 1) != GRAPHIC_COMMANDS[i].nb_args &&
    GRAPHIC_COMMANDS[i].nb_args != -1)
        return add_to_buffer(&client->buffer_out, "sbp\n", false);
    GRAPHIC_COMMANDS[i].func(server, client, tab);
}

static void check_command(server_t *server, client_t *client,
    char const *command)
{
    char **tab = my_str_to_word_array(command, " ");

    for (int i = 0; GRAPHIC_COMMANDS[i].command != NULL; i++) {
        if (my_strcmp(GRAPHIC_COMMANDS[i].command, tab[0]) == 0) {
            exec_command(server, client, (char const **)tab, i);
            free_tab(tab);
            return;
        }
    }
    debug_print(" [GRAPHIC] command: [%s] for client: [%i] not exist\n", command,
        client->fd);
    free_tab(tab);
    add_to_buffer(&client->buffer_out, "suc\n", false);
}

void exec_graphic(server_t *server, client_t *client, char **command)
{
    int i = 0;
    char *other_cmd = NULL;

    for (; command[i] != NULL && i != 10; i++)
        check_command(server, client, command[i]);
    free(client->buffer_in);
    client->buffer_in = NULL;
    if (i < 10)
        return;
    other_cmd = my_array_to_str_separator((char const **)&command[i], " \n");
    if (other_cmd == NULL)
        return;
    client->buffer_in = other_cmd;
}

void exec_graphic_list(server_t *server)
{
    client_t *tmp = server->graphic_clients->head;
    client_t *next = NULL;
    char **command = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        command = my_str_to_word_array(tmp->buffer_in, "\n");
        if (command == NULL)
            return;
        exec_graphic(server, tmp, command);
        tmp = next;
        free_tab(command);
    }
}
