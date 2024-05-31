/*
** EPITECH PROJECT, 2024
** server
** File description:
** option
*/

#ifndef SERVER_OPTION_H
    #define SERVER_OPTION_H
    #include <unistd.h>

typedef struct option_s {
    int port;
    int width;
    int height;
    int clients_nb;
    int freq;
    char **names;
} option_t;

typedef struct option_tab_s {
    char *flag;
    int (*func)(option_t *option, const char **av, int i);
} option_tab_t;



#endif //SERVER_OPTION_H
