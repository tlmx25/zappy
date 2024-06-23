/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "server.hpp"
#include "Game.hpp"

static int verif_args(int ac, char **av)
{
    if (ac != 5) {
        return 84;
    }
    if (strcmp(av[1], "-p") != 0 && strcmp(av[1], "-h") != 0)
        return 84;
    if (strcmp(av[3], "-h") != 0 && strcmp(av[3], "-p") != 0)
        return 84;
    return 0;
}

static void print_usage()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
}

int main(int ac, char **av)
{
    Game game(30, 30);
    game.run();
    // if (std::string(av[1]) == "-h" && ac == 2) {
    //     print_usage();
    //     return 0;
    // }
    // if (verif_args(ac, av) == 84)
    //     return 84;

    // try
    //   {
    //     if (std::string(av[1]).compare("-p") == 0) {
    //         Zappy_GUI::Server server(av[2], av[4]);
    //         server.OpenSocket();
    //         server.ConnectSocket();
    //         server.Run();
    //     }
    //     if (std::string(av[1]).compare("-h") == 0) {
    //         Zappy_GUI::Server server(av[4], av[2]);
    //         server.OpenSocket();
    //         server.ConnectSocket();
    //         server.Run();
    //     }
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    return 0;
}
