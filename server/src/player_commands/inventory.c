/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** inventory
*/

#include "server.h"

// Sends the content of the client's inventory
int command_inventory(server_t *serv __attribute__((unused)),
    client_t *player, char *arg)
{
    char buf1[256] = {0};
    char buf2[256] = {0};

    if (arg != NULL)
        return 1;
    snprintf(buf1, sizeof(buf1),
        "[food %d, linemate %d, deraumere %d, ",
        player->food, player->linemate, player->deraumere);
    snprintf(buf2, sizeof(buf2),
        "sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        player->sibur, player->mendiane, player->phiras, player->thystame);
    dprintf(player->fd, "%s%s", buf1, buf2);
    return 0;
}
