/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include "server.h"

// Send broadcast signal to GRAPHIC clients
void event_pbc(server_t *serv, client_t *player, char *message)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pbc %d %s\n",
                player->id, message);
        }
    }
}
