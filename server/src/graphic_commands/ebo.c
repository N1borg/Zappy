/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player connection for an egg
*/

#include "server.h"

void event_ebo(server_t *serv, egg_t *egg)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "ebo %i\n", egg->id);
        }
    }
}
