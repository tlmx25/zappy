/*
** EPITECH PROJECT, 2024
** server
** File description:
** sending
*/

#include <stdio.h>
#include <stdarg.h>
#include "server.h"

void send_to_all_graphic(client_list_t *list, char *msg)
{
    client_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        add_to_buffer(&tmp->buffer_out, msg, false);
    }
}

void send_to_all_graphic_arg(client_list_t *list, char *format, ...)
{
    client_t *tmp = list->head;
    va_list args;
    char tmp_buffer[2048];

    va_start(args, format);
    vsnprintf(tmp_buffer, 2048, format, args);
    for (; tmp != NULL; tmp = tmp->next) {
        add_to_buffer(&tmp->buffer_out, tmp_buffer, false);
    }
    va_end(args);
}

void send_to_all_ai(client_ai_list_t *list, char *msg)
{
    client_ai_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        add_to_buffer(&tmp->buff_out, msg, false);
    }
}

void send_to_other_ai(client_ai_list_t *list, char *msg, client_ai_t *client)
{
    client_ai_t *tmp = list->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp == client)
            continue;
        add_to_buffer(&tmp->buff_out, msg, false);
    }
}

void send_to_all_graphic_func(server_t *server, char const **cmd,
    void (*fct)(server_t *server, client_t *client, char const **command) )
{
    client_t *tmp = server->graphic_clients->head;

    for (;tmp; tmp = tmp->next)
    {
        fct(server, tmp, cmd);
    }
}
