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

std::string Zappy_GUI::Server::FirstWord(std::string buffer) {
    std::string firstWord;
    size_t pos = buffer.find(' ');

    if (pos != std::string::npos) {
        firstWord = buffer.substr(0, pos);
    } else {
        firstWord = buffer;
    }
    return firstWord;
}

void Zappy_GUI::Server::mszFonction(const std::string& command) {
    std::string temp;
    std::string x;
    std::string y;

    std::stringstream(command) >> temp >> x >> y;

    try {
        _xMap = std::stoi(x);
        _yMap = std::stoi(y);
    } catch (std::invalid_argument &e) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
}

std::string Zappy_GUI::Server::ReadClient() {
    std::string buffer;
    char c;
    int result;

    while ((result = recv(_socket, &c, 1, 0)) > 0) {
        buffer += c;
        if (c == '\n')
            break;
    }
    if (result == 0) {
        CloseSocket();
        throw Zappy_GUI::Server::ReceiveFailed("Connection closed by server.");
    } else if (result < 0) {
        CloseSocket();
        throw Zappy_GUI::Server::ReceiveFailed("Receive failed.");
    }
    return buffer;
}

void Zappy_GUI::Server::SendData(std::string message) {
    FD_ZERO(&_writefds);
    FD_SET(_socket, &_writefds);
    
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int activity = select(_socket + 1, NULL, &_writefds, NULL, &timeout);

    if (activity < 0) {
        CloseSocket();
        throw Zappy_GUI::Server::ReceiveFailed("Select failed.");
    }

    if (FD_ISSET(_socket, &_writefds)) {
            int bytesSent = send(_socket, message.c_str(), strlen(message.c_str()), 0);
            if (bytesSent < 0) {
                CloseSocket();
                throw Zappy_GUI::Server::SendFailed("Send failed.");
            }
        }
}

void Zappy_GUI::Server::Run() {
    char buffer[1024];
    srand(static_cast<unsigned>(time(0)));
    // TODO: Give the map size as parameters got from the server
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