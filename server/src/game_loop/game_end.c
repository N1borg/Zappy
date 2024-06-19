/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** game_loop.c
*/

#include "server.h"

int check_team_levels(team_t *team)
{
    int max_level_p = 0;

    for (int i = 0; team->players[i]; i++) {
        if (team->players[i]->level == 8)
            max_level_p += 1;
        if (max_level_p == 6)
            return 1;
    }
    return 0;
}

int check_game_end(server_t *server)
{
    for (int i = 0; server->teams[i]; i++) {
        if (check_team_levels(server->teams[i]) == 1) {
            printf("team %s has won\n", server->teams[i]->name);
            return 1;
        }
    }
    return 0;
}
