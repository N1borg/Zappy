/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** resource dropping
*/

#include "server.h"

// Send ressource drop signal to GRAPHIC clients
void event_pdr(server_t *serv, client_t *player, const char *ressource)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pdr %d %s\n",
                player->id, ressource);
        }
    }
}
