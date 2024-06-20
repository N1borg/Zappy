/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** map size
*/

#include "server.h"

// Function to send the map size to the client
int command_msz(server_t *serv, client_t *client, char *arg)
{
    if (arg != NULL)
        return event_sbp(client);
    dprintf(client->fd, "msz %d %d\n", serv->width, serv->height);
    return 0;
}
