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
            void SendData();

        private :
            std::string _port;
            std::string _ip;
            int _socket;
            struct sockaddr_in _server;

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
}