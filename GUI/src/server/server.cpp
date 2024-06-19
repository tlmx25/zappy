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

    _map = {
            {"bct", bctFonction},
            {"tna", [](const std::string&, Game&) {}},
            {"pnw", pnwFonction},
            {"ppo", ppoFonction},
            {"plv", plvFonction},
            {"pin", pinFonction},
            {"pex", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"pbc", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"pic", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"pie", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"pfk", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"pdr", pdrFonction},
            {"pgt", pgtFonction},
            {"pdi", pdiFonction},
            {"enw", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"ebo", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"edi", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"sgt", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"sst", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"seg", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"smg", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"suc", [](const std::string&, Game&) { std::cout << "Lambda 2" << std::endl; }},
            {"sbp", [](const std::string&, Game&) { std::cout << "Lambda 3" << std::endl; }}
        };
}

Zappy_GUI::Server::~Server() {};

void Zappy_GUI::Server::LambdaExecute(std::string key, std::string command, Game& game) {
    auto it = _map.find(key);

    if (it != _map.end()) {
        it->second(command, game);
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

void Zappy_GUI::Server::Run() {
    GUIStart();
    GUISize();
    srand(static_cast<unsigned>(time(0)));
    Game game(_xMap, _yMap);

    while (game.getWindow().isOpen()) {
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
            std::cout << buffer << std::endl;
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

void Zappy_GUI::Server::GUISize() {
    FD_ZERO(&_readfds);
    FD_SET(_socket, &_readfds);
    
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int activity = select(_socket + 1, &_readfds, NULL, NULL, &timeout);

    if (activity < 0) {
        CloseSocket();
        throw Zappy_GUI::Server::ReceiveFailed("Select failed.");
    }

    std::string buffer = ReadClient();
    mszFonction(buffer);
}

void Zappy_GUI::Server::CloseSocket() {
    close(_socket);
}

void bctFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string x;
    std::string y;
    std::string q0;
    std::string q1;
    std::string q2;
    std::string q3;
    std::string q4;
    std::string q5;
    std::string q6;

    std::stringstream(command) >> temp >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;

    try {
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(0, std::stoi(q0));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(1, std::stoi(q1));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(2, std::stoi(q2));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(3, std::stoi(q3));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(4, std::stoi(q4));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(5, std::stoi(q5));
        game.getMap().getTile(std::stoi(x), std::stoi(y)).setItemQuantity(6, std::stoi(q6));
    } catch (std::invalid_argument &e) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
}

void pnwFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string x;
    std::string y;
    std::string O;
    std::string L;
    std::string N;

    std::stringstream(command) >> temp >> nbr >> x >> y >> O >> L >> N;

    try {
        game.getTrantorians().insert({nbr, std::make_shared<Trantorian>(std::stoi(nbr), N, sf::Vector2i(std::stoi(x), std::stoi(y)), std::stoi(O), std::stoi(L), game.getTeamNumber(N))});
    } catch (std::invalid_argument &e) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
}

void ppoFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string x;
    std::string y;
    std::string O;

    std::stringstream(command) >> temp >> nbr >> x >> y >> O;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
    auto player = it->second;
    player->setPos(sf::Vector2i(std::stoi(x), std::stoi(y)));
}

void plvFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string L;

    std::stringstream(command) >> temp >> nbr >> L;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
    auto player = it->second;
    player->setLevel(std::stoi(L));
}

void pinFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string x;
    std::string y;
    std::string q0;
    std::string q1;
    std::string q2;
    std::string q3;
    std::string q4;
    std::string q5;
    std::string q6;

    std::stringstream(command) >> temp >> nbr >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
    auto player = it->second;
    player->setInventory(std::stoi(q0),std::stoi(q1),std::stoi(q2),std::stoi(q3),std::stoi(q4),std::stoi(q5),std::stoi(q6));
}

void pdrFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string i;

    std::stringstream(command) >> temp >> nbr >> i;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
    int item;
    try {
        item = std::stoi(i);
    } catch (const std::invalid_argument& e) {
        throw Zappy_GUI::Server::BadParameter("L'argument de l'objet n'est pas un entier valide.");
    }

    auto& player = it->second;
    auto& tile = game.getMap().getTile(player->getPos().x, player->getPos().y);
    player->dropItem(tile, item);
}

void pgtFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;
    std::string i;

    std::stringstream(command) >> temp >> nbr >> i;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }
    int item;
    try {
        item = std::stoi(i);
    } catch (const std::invalid_argument& e) {
        throw Zappy_GUI::Server::BadParameter("L'argument de l'objet n'est pas un entier valide.");
    }

    auto& player = it->second;
    auto& tile = game.getMap().getTile(player->getPos().x, player->getPos().y);
    player->collectItem(tile, item);
}

void pdiFonction(const std::string& command, Game& game)
{
    std::string temp;
    std::string nbr;

    std::stringstream(command) >> temp >> nbr;

    auto& trantorians = game.getTrantorians();
    auto it = trantorians.find(nbr);
    if (it == trantorians.end()) {
        throw Zappy_GUI::Server::BadParameter("Mauvais arguments.");
    }

    trantorians.erase(nbr);
}