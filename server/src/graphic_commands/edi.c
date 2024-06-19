/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** death of an egg
*/

#include "server.h"

void event_edi(server_t *serv, egg_t *egg)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team &&
            strcmp(serv->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(serv->clients[i]->fd, "edi %i\n", egg->id);
        }
    }
}
