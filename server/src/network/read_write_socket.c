/*
** EPITECH PROJECT, 2024
** server
** File description:
** read_write_socket
*/

#include <unistd.h>
#include "server.h"
#include "my.h"

char *read_socket(int fd)
{
    char tmp_buffer[1025] = {0};
    char *buffer = NULL;
    long readed;

    while (1) {
        readed = read(fd, tmp_buffer, 1024);
        tmp_buffer[readed] = 0;
        if (readed == -1)
            return NULL;
        if (readed == 0)
            break;
        buffer = my_strcat_free(buffer, tmp_buffer, 1, 0);
        if (buffer == NULL)
            return NULL;
        if (buffer[my_strlen(buffer) - 1] == '\n')
            break;
    }
    return buffer;
}

int write_socket(int fd, char *str)
{
    if (write(fd, str, my_strlen(str)) == -1)
        return ERROR;
    return 0;
}

void add_to_buffer(char **buffer, char *str, bool free_str)
{
    char *tmp = NULL;

    if (str == NULL)
        return;
    if (str[my_strlen(str) - 1] != '\n') {
        tmp = str;
        str = my_strcat_free(str, "\n", 0, 0);
    }
    if (*buffer == NULL)
        *buffer = my_strdup(str);
    else
        *buffer = my_strcat_free(*buffer, str, 1, 0);
    if (free_str)
        free(str);
    if (tmp != NULL && free_str)
        free(tmp);
}
