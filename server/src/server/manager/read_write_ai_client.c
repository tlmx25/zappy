/*
** EPITECH PROJECT, 2024
** server
** File description:
** read_write_ai_client
*/

#include "server.h"

static void cut_buffer(client_ai_t *tmp)
{
    char **tmp_tab = my_str_to_word_array(tmp->buff_in, "\n");
    int size = my_arrsize((char const **)tmp_tab);

    if (tmp_tab == NULL)
        return;
    if (size <= 10)
        return free_tab(tmp_tab);
    for (int i = 10; i < size; i++) {
        free(tmp_tab[i]);
        tmp_tab[i] = NULL;
    }
    free(tmp->buff_in);
    tmp->buff_in = my_array_to_str_separator((char const **)tmp_tab, "\n");
    free_tab(tmp_tab);
}

static void error_read(client_ai_t *tmp)
{
    char *tmp_buff = read_socket(tmp->fd);

    if (tmp_buff == NULL) {
        tmp->to_disconnect = true;
        return;
    }
    if (my_count_char(tmp->buff_in, '\n') > 10) {
        free(tmp_buff);
        cut_buffer(tmp);
        return;
    }
    add_to_buffer(&tmp->buff_in, tmp_buff, true);
}

void read_ai_list(server_t *server, client_ai_list_t *list)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (FD_ISSET(tmp->fd, &server->select_config->readfds)) {
            error_read(tmp);
        }
        if (tmp->to_disconnect == true) {
            debug_print("Client AI disconnected num : %i, fd: %i\n",
            tmp->num_player, tmp->fd);
            delete_client_ai_from_list(list, tmp, true);
        }
        tmp = next;
    }
}

void write_ai_list(server_t *server, client_ai_list_t *list)
{
    client_ai_t *tmp = list->head;
    client_ai_t *next = NULL;

    for (; tmp != NULL; tmp = next) {
        next = tmp->next;
        if (!FD_ISSET(tmp->fd, &server->select_config->writefds))
            continue;
        if (tmp->buff_out != NULL) {
            write_socket(tmp->fd, tmp->buff_out);
            free(tmp->buff_out);
            tmp->buff_out = NULL;
        }
        if (tmp->TTL <= 0) {
            debug_print("Client AI death fd: %i\n", tmp->fd);
            delete_client_ai_from_list(list, tmp, true);
        }
    }
}
