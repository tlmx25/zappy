/*
** EPITECH PROJECT, 2024
** server
** File description:
** create_server
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"


static int bind_listen(int sockfd, struct sockaddr_in *server_addr)
{
    int opt = 1;

    if (setsockopt(sockfd, SOL_SOCKET,
        SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        return -1;
    }
    if (bind(sockfd, (struct sockaddr *)server_addr,
        sizeof(struct sockaddr_in)) == -1) {
        free(server_addr);
        return -1;
    }
    if (listen(sockfd, 10) == -1) {
        perror("Erreur lors de l'association du port");
        free(server_addr);
        return -1;
    }
    return sockfd;
}

static int create_socket(int port)
{
    int sockfd;
    struct sockaddr_in *server_addr = calloc(sizeof(struct sockaddr_in), 1);

    if (server_addr == NULL)
        return -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        return -1;
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    server_addr->sin_addr.s_addr = INADDR_ANY;
    if (bind_listen(sockfd, server_addr) == -1)
        return -1;
    free(server_addr);
    return sockfd;
}

server_t *create_server(int port)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    server->port = port;
    server->socket = create_socket(port);
    if (server->socket == -1) {
        free(server);
        return NULL;
    }
    server->pending_clients = create_client_list();
    server->graphic_clients = create_client_list();
    server->ai_clients = create_client_list();
    if (!server->pending_clients || !server->graphic_clients
        || !server->ai_clients) {
        delete_server(server);
        return NULL;
    }
    return server;
}
