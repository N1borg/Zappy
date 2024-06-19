/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** food.c
*/

#include "server.h"

void check_if_dead(client_t *client)
{
    if (client->food == 0) {
        dprintf(client->fd, "dead\n");
        close(client->fd);
        set_client(client);
        client->fd = -1;
    }
}

void manage_food(server_t *server)
{
    for (int i = 0; server->clients[i] != NULL; i++) {
        if (server->clients[i]->food > 0) {
            server->clients[i]->food--;
            check_if_dead(server->clients[i]);
        }
    }
}
