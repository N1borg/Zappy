/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** player’s inventory
*/

#include "server.h"

// Send the inventory of a player
int command_pin(server_t *serv, client_t *client, char *arg)
{
    int id = 0;
    client_t *player = NULL;

    if (arg == NULL)
        return 1;
    id = atoi(arg);
    if (id <= 0)
        return 1;
    player = get_client_by_id(serv, id);
    if (player == NULL)
        return 1;
    dprintf(client->fd, "pin %d %d %d %d %d %d %d %d %d %d\n", player->id,
    player->x, player->y, player->inv.food, player->inv.linemate,
    player->inv.deraumere, player->inv.sibur, player->inv.mendiane,
    player->inv.phiras, player->inv.thystame);
    return 0;
}
