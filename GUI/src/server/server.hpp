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
            /**
             * @brief Build the Server object with the parameter Port and adresse_ip
             * 
             */
            Server(char *Port, char * adresse_ip);
            /**
             * @brief Destroy the Server object
             * 
             */
            ~Server();
        
        public :
            /**
             * @brief Open the socket for connection
             * 
             * 
             */
            void OpenSocket();
            /**
             * @brief Connect the socket and the server
             * 
             * 
             */
            void ConnectSocket();
            /**
             * @brief Close the socket
             * 
             * 
             */
            void CloseSocket();
            /**
             * @brief Run the server og GUI
             * 
             * 
             */
            void Run();
      
            /**
             * @brief Send the first command to Server and send GRAPHIC
             * 
             * 
             */
            void GUIStart();
            /**
             * @brief Receive the size of Map
             * 
             * 
             */
            void GUISize();
            /**
             * @brief Send Data for the server
             * 
             * @param message The message to send
             */
            void SendData(std::string message);
            /**
             * @brief Read the message receive
             * 
             * 
             */
            std::string ReadClient();

            /**
             * @brief Lambda for differents fonctions
             * 
             * @param key First word of the buffer
             * @param command The complete command
             * @param game The object game
             */
            void LambdaExecute(std::string key, std::string command, Game& game);
            /**
             * @brief Take the first word of the buffer
             * 
             * @param buffer The complete command
             */
            std::string FirstWord(std::string buffer);
            /**
             * @brief Take the size of the map in 
             * 
             * @param buffer The complete command
             */
            void mszFonction(const std::string& command);

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