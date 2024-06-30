/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init socket & listener
*/

#include "server.h"

// Initialize the listener
int init_listener(server_t *serv)
{
    serv->addr.sin_family = AF_INET;
    serv->addr.sin_addr.s_addr = INADDR_ANY;
    serv->addr.sin_port = htons(serv->port);
    if (bind(serv->master_socket, (struct sockaddr *)&serv->addr,
        sizeof(serv->addr)) < 0) {
        perror("Bind failed");
        return 84;
    }
    if (listen(serv->master_socket, 10) < 0) {
        perror("Listen");
        return 84;
    }
    return 0;
}

// Initialize the socket
int init_socket(server_t *serv)
{
    int opt = true;

    serv->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv->master_socket == -1) {
        perror("Socket failed");
        return 84;
    }
    if (setsockopt(serv->master_socket, SOL_SOCKET, SO_REUSEADDR,
        (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return 84;
    }
    return 0;
}
