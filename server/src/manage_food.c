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

void manage_food(server_t *serv)
{
    for (int i = 0; serv->clients[i] != NULL; i++) {
        if (serv->clients[i]->food > 0) {
            serv->clients[i]->food--;
            check_if_dead(serv->clients[i]);
        }
    }
}
