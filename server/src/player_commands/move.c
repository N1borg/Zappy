/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** moving
*/

#include "server.h"

// Move the client in the direction he is facing
int command_forward(server_t *serv, client_t *player, char *arg)
{
    if (arg != NULL)
        return 1;
    if (player->orientation == NORTH)
        move_player(serv, player, player->x, player->y - 1);
    if (player->orientation == EAST)
        move_player(serv, player, player->x + 1, player->y);
    if (player->orientation == SOUTH)
        move_player(serv, player, player->x, player->y + 1);
    if (player->orientation == WEST)
        move_player(serv, player, player->x - 1, player->y);
    if (player->orientation < 1 || player->orientation > 4)
        return 1;
    return success_response(player);
}
