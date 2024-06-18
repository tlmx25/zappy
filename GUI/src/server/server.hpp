/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** server
*/


#pragma once

    #include <iostream>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <cstring>
    #include <string>
    #include <sstream>
    #include <unordered_map>
    #include <map>
    #include <functional>
    #include "Game.hpp"
        
namespace Zappy_GUI {

    class Server {
        public :
            Server(char *Port, char * adresse_ip);
            ~Server();
        
        public :
            void OpenSocket();
            void ConnectSocket();
            void CloseSocket();
            void Run();
            void GUIStart();
            void GUISize();
            void SendData();
            std::string ReadClient();

            void LambdaExecute(std::string key, std::string command, Game& game);
            std::string FirstWord(std::string buffer);
            void mszFonction(const std::string& command);

        private :
            std::string _port;
            std::string _ip;
            int _socket;
            struct sockaddr_in _server;
            std::map<std::string, std::function<void(const std::string&, Game&)>> _map;
            fd_set _readfds;
            fd_set _writefds;
            int _xMap;
            int _yMap;

        public: // Error socket and IP

            class BadParameter : public std::exception {
                public:
                    BadParameter(std::string msg) : _msg(msg) {};
                    ~BadParameter() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };

            class ConnectFailed : public std::exception {
                public:
                    ConnectFailed(std::string msg) : _msg(msg) {};
                    ~ConnectFailed() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };

            class ReceiveFailed : public std::exception {
                public:
                    ReceiveFailed(std::string msg) : _msg(msg) {};
                    ~ReceiveFailed() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };

            class SendFailed : public std::exception {
                public:
                    SendFailed(std::string msg) : _msg(msg) {};
                    ~SendFailed() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };

    };
};

void bctFonction(const std::string& command, Game&);
void pnwFonction(const std::string& command, Game&);
void ppoFonction(const std::string& command, Game&);
