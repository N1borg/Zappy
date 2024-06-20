/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** time unit request
*/

#include "server.h"

// Send the time unit request
int command_sgt(server_t *serv, client_t *client, char *arg)
{
    if (arg != NULL)
        return event_sbp(client);
    dprintf(client->fd, "sgt %d\n", serv->freq);
    return 0;
}
