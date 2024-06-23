/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <stdio.h>
#include "server.h"
#include "my.h"

static int print_help(void)
{
    printf("USAGE : ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
    return 0;
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (ac == 2 && (!my_strcmp(av[1], "-help") || !my_strcmp(av[1], "-h")))
        return print_help();
    server = create_server(av);
    if (server == NULL)
        return 84;
    init_game(server);
    run_server(server);
    delete_server(server);
    return 0;
}
