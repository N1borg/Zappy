/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** time unit modification
*/

#include "server.h"

// Send the time unit modification
int command_sst(server_t *serv, client_t *client, char *arg)
{
    int temp_freq = 0;

    if (arg == NULL)
        return event_sbp(client);
    temp_freq = atoi(arg);
    if (temp_freq <= 0)
        return event_sbp(client);
    serv->freq = temp_freq;
    dprintf(client->fd, "sst %d\n", serv->freq);
    return 0;
}
