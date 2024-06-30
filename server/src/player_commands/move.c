/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** moving
*/

#include "server.h"

// Move the client in the direction he is facing
int command_forward(server_t *serv, client_t *player, char *arg)
{
    if (arg != NULL)
        return 1;
    switch (player->orientation) {
        case NORTH:
            move_player(serv, player, player->x, player->y - 1);
            break;
        case EAST:
            move_player(serv, player, player->x + 1, player->y);
            break;
        case SOUTH:
            move_player(serv, player, player->x, player->y + 1);
            break;
        case WEST:
            move_player(serv, player, player->x - 1, player->y);
            break;
        default:
            return 1;
    }
    return success_response(player);
}
