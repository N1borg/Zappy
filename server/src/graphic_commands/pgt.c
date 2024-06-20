/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** resource collecting
*/

#include "server.h"

// Send ressource collect signal to GRAPHIC clients
void event_pgt(server_t *serv, client_t *player, int ressource)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pgt %d %d\n",
                player->id, ressource);
        }
    }
}
