/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** forking
*/

#include "../../include/main.h"

// create an egg
int command_fork(server_t *server, client_t *client, char *arg)
{
    tile_t *tile = &server->map[client->y][client->x];
    team_t *team = server->teams[which_team(server, client->team)];

    if (add_egg(team, tile) == 84)
        return 84;
    team->free_slots++;
    return 0;
}
