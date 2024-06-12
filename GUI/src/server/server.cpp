/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** server
*/

#include "server.hpp"
#include "Game.hpp"

Zappy_GUI::Server::Server(char *Port, char * adresse_ip) {
    _port = Port;
    _ip = adresse_ip;
}

Zappy_GUI::Server::~Server() {};

void Zappy_GUI::Server::OpenSocket() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_socket < 0)
        throw Zappy_GUI::Server::BadParameter("Erreur de création du socket.");

    std::memset(&_server, 0, sizeof(_server));
    _server.sin_family = AF_INET;
    _server.sin_port = htons(std::atoi(_port.c_str()));
    _server.sin_addr.s_addr = inet_addr(_ip.c_str());
}

void Zappy_GUI::Server::ConnectSocket() {
    if (connect(_socket, (struct sockaddr*)&_server, sizeof(_server)) < 0) {
        close(_socket);
        throw Zappy_GUI::Server::ConnectFailed("Connection failed.");
    }
}

void Zappy_GUI::Server::Run() {
    char buffer[1024];
    srand(static_cast<unsigned>(time(0)));
    Game game(30, 30);

    while (true) {
        // Recevoir des données
        int bytesReceived = recv(_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived < 0) {
            CloseSocket();
            throw Zappy_GUI::Server::ReceiveFailed("Receive failed.");
        } else if (bytesReceived == 0) {
            CloseSocket();
            throw Zappy_GUI::Server::ReceiveFailed("Receive failed.");
        }

        buffer[bytesReceived] = '\0';
        std::cout << "Données reçues : " << buffer << std::endl;
        game.run();
    }
}

void Zappy_GUI::Server::CloseSocket() {
    close(_socket);
}