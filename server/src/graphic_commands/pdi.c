/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** death of a player
*/

#include "server.h"

// Send the death of a player signal to the GRAPHIC client
void event_pdi(server_t *serv, client_t *player)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "pdi %d\n",
                player->id);
        }
    }
}
