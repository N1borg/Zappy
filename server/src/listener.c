/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** init socket & listener
*/

#include "../include/main.h"

int init_listener(server_t *s)
{
    s->addr.sin_family = AF_INET;
    s->addr.sin_addr.s_addr = INADDR_ANY;
    s->addr.sin_port = htons(s->port);
    if (bind(s->master_socket, (struct sockaddr *)&s->addr,
        sizeof(s->addr)) < 0) {
        perror("Bind failed");
        return 84;
    }
    if (listen(s->master_socket, 10) < 0) {
        perror("Listen");
        return 84;
    }
    return 0;
}

int init_socket(server_t *s)
{
    int opt = true;

    for (int i = 0; i < s->max_client_team; i++)
        s->client_socket[i] = 0;
    s->master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s->master_socket == 0) {
        perror("Socket failed");
        return 84;
    }
    if (setsockopt(s->master_socket, SOL_SOCKET, SO_REUSEADDR,
        (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return 84;
    }
    if (s->master_socket == 0) {
        perror("Socket failed");
        return 84;
    }
    return 0;
}
