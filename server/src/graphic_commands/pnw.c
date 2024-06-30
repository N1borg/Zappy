/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connection of a new player
*/

#include "server.h"

// Send new player signal
void event_pnw(server_t *serv, client_t *player)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pnw %d %d %d %d %d %s\n",
                player->id, player->x, player->y, player->orientation,
                player->level, player->team);
        }
    }
}
