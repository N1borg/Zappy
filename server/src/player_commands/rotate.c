/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** rotating
*/

#include "server.h"

// Increase the orientation of the player by 1
int command_turn_right(server_t *serv __attribute__((unused)),
    client_t *player, char *arg __attribute__((unused)))
{
    int temp = player->orientation;

    if (arg != NULL)
        return 1;
    player->orientation = (temp == 4) ? 1 : temp + 1;
    return success_response(player);
}

// Decrease the orientation of the player by 1
int command_turn_left(server_t *serv __attribute__((unused)),
    client_t *player, char *arg __attribute__((unused)))
{
    int temp = player->orientation;

    if (arg != NULL)
        return 1;
    player->orientation = (temp == 1) ? 4 : temp - 1;
    return success_response(player);
}
