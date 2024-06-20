/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** an egg was laid by a player
*/

#include "server.h"

void event_enw(server_t *serv, client_t *player, egg_t *egg)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "enw %i %i %i %i\n",
                egg->id, player->id, player->x, player->y);
        }
    }
}
