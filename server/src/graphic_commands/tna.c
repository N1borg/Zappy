/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** name of all the teams
*/

#include "server.h"

// Send the name of all the teams
int command_tna(server_t *serv, client_t *client, char *arg)
{
    if (arg != NULL)
        return 1;
    for (int i = 0; serv->teams[i] != NULL
        && strcmp(serv->teams[i]->name, "GRAPHIC") != 0; i++) {
        dprintf(client->fd, "tna %s\n", serv->teams[i]->name);
    }
    return 0;
}