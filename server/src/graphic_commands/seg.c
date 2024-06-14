/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** end of game
*/

#include "../../include/main.h"

void event_seg(server_t *server, char *team)
{
    for (int i = 0; server->clients[i] != NULL; i++) {
        if (strcmp(server->clients[i]->team, "GRAPHIC") == 0) {
            dprintf(server->clients[i]->fd, "seg %s\n", team);
        }
    }
}
