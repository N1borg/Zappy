/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** egg laying by the player
*/

#include "server.h"

// Send the egg laying signal to GRAPHIC clients
void event_pfk(server_t *serv, client_t *player)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pfk %d\n", player->id);
        }
    }
}
