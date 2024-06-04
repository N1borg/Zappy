/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** inventory
*/

#include "../../include/main.h"

// sends the content of the client's inventory
int command_inventory(server_t *s, client_t *client)
{
    char buf1[256] = {0};
    char buf2[256] = {0};

    snprintf(buf1, sizeof(buf1), "[linemate %d, deraumere %d, sibur %d,",
            client->linemate, client->deraumere, client->sibur);
    snprintf(buf2, sizeof(buf2), " mendiane %d, phiras %d, thystame %d]\n",
            client->mendiane, client->phiras, client->thystame);
    dprintf(client->fd, "%s%s", buf1, buf2);
    return 0;
}
