/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** server
*/

#include "server.hpp"

Zappy_GUI::Server::Server(char *Port, char * adresse_ip) {
    _port = Port;
    _ip = adresse_ip;

    _map = {
            {"msz", []() { std::cout << "Map" << std::endl; }},
            {"bct", []() { std::cout << "Lambda 2" << std::endl; }},
            {"tna", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pnw", []() { std::cout << "Lambda 2" << std::endl; }},
            {"ppo", []() { std::cout << "Lambda 2" << std::endl; }},
            {"plv", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pin", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pex", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pbc", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pic", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pie", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pfk", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pdr", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pgt", []() { std::cout << "Lambda 2" << std::endl; }},
            {"pdi", []() { std::cout << "Lambda 2" << std::endl; }},
            {"enw", []() { std::cout << "Lambda 2" << std::endl; }},
            {"ebo", []() { std::cout << "Lambda 2" << std::endl; }},
            {"edi", []() { std::cout << "Lambda 2" << std::endl; }},
            {"sgt", []() { std::cout << "Lambda 2" << std::endl; }},
            {"sst", []() { std::cout << "Lambda 2" << std::endl; }},
            {"seg", []() { std::cout << "Lambda 2" << std::endl; }},
            {"smg", []() { std::cout << "Lambda 2" << std::endl; }},
            {"suc", []() { std::cout << "Lambda 2" << std::endl; }},
            {"sbp", []() { std::cout << "Lambda 3" << std::endl; }}
        };
}

Zappy_GUI::Server::~Server() {};

void Zappy_GUI::Server::LambdaExecute(std::string key, std::string command, Game& game) {
    auto it = _map.find(key);

    if (it != _map.end()) {
        it->second();
    }
}

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

std::string Zappy_GUI::Server::ReadClient() {
    std::string buffer;
    char c;
    int result;

    while (result = recv(_socket, &c, 1, 0) > 0) {
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

void Zappy_GUI::Server::Run() {
    
    GUIStart();
    srand(static_cast<unsigned>(time(0)));
    Game game(0, 0);

    while (game.GetWindow().isOpen()) {
        FD_ZERO(&_readfds);
        FD_ZERO(&_writefds);
        FD_SET(_socket, &_readfds);
        FD_SET(_socket, &_writefds);

        struct timeval timeout;
        timeout.tv_sec = 0.5;
        timeout.tv_usec = 0;

        int activity = select(_socket + 1, &_readfds, NULL, NULL, &timeout);

        game.run();
        
        if (activity < 0) {
            CloseSocket();
            throw Zappy_GUI::Server::ReceiveFailed("Select failed.");
        } else if (activity == 0) {
            continue;
        }

        if (FD_ISSET(_socket, &_readfds)) {
            std::string buffer = ReadClient();
            std::string key = FirstWord(buffer);
            if (buffer.empty() == true)
                continue;
            LambdaExecute(key, buffer, game);
        }
    }
}

void Zappy_GUI::Server::GUIStart() {
    FD_ZERO(&_writefds);
    FD_ZERO(&_readfds);
    FD_SET(_socket, &_writefds);
    FD_SET(_socket, &_readfds);
    
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int activity = select(_socket + 1, &_readfds, NULL, NULL, &timeout);

    if (activity < 0) {
        CloseSocket();
        throw Zappy_GUI::Server::ReceiveFailed("Select failed.");
    }

    char buffer[1024];

    if (FD_ISSET(_socket, &_readfds)) {
        int bytesReceived = recv(_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived < 0) {
            CloseSocket();
            throw Zappy_GUI::Server::ReceiveFailed("Receive failed.");
        } else if (bytesReceived == 0) {
            CloseSocket();
            throw Zappy_GUI::Server::ReceiveFailed("Connection closed by peer.");
        }
        buffer[bytesReceived] = '\0';
    }
    std::string buffer2 = buffer;
    if (buffer2.compare("WELCOME\0") == true) {
        if (FD_ISSET(_socket, &_writefds)) {
            const char *message = "GRAPHIC\n";
            int bytesSent = send(_socket, message, strlen(message), 0);
            if (bytesSent < 0) {
                CloseSocket();
                throw Zappy_GUI::Server::SendFailed("Send failed.");
            }
        }
    }
}

void Zappy_GUI::Server::CloseSocket() {
    close(_socket);
}