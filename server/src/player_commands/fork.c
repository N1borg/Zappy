/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "server.h"

// Create an egg
int command_fork(server_t *serv, client_t *player, char *arg)
{
    if (arg != NULL)
        return 1;
    serv->map[player->y][player->x].egg++;
    serv->teams[get_team_id(serv, player->team)]->free_slots++;
    return success_response(player);
}
