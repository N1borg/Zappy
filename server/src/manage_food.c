/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** food.c
*/

#include "server.h"

void check_if_dead(server_t *serv, client_t *client)
{
    if (client->inv.food == 0) {
        dprintf(client->fd, "dead\n");
        disconnect_client(serv, client);
    }
}

void manage_food(server_t *serv)
{
    for (int i = 0; serv->clients[i] != NULL; i++) {
        if (serv->clients[i]->inv.food > 0) {
            serv->clients[i]->inv.food--;
            check_if_dead(serv, serv->clients[i]);
        }
    }
}
