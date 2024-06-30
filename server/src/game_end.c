/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game_end.c
*/

#include "server.h"

// Get the number of eggs on a team
int get_nbr_eggs_on_team(team_t *team)
{
    egg_t *egg = team->eggs;
    int count = 0;

    while (egg) {
        count++;
        egg = egg->next_team;
    }
    return count;
}

// Check if a team has 6 players at level 8
int check_team_levels(server_t *server, team_t *team)
{
    client_t *client = NULL;
    int max_level_count = 0;

    for (int j = 0; j < MAX_CLIENTS; j++) {
        client = team->players[j];
        if (client != NULL && client->level == 8)
            max_level_count++;
        if (max_level_count >= 6) {
            printf("Team %s has won\n", team->name);
            event_seg(server, team->name);
            return 1;
        }
    }
    return 0;
}

// Check if a team is still alive
int is_team_alive(team_t *team)
{
    if (get_nbr_eggs_on_team(team) > 0)
        return 1;
    for (int j = 0; j < MAX_CLIENTS; j++) {
        if (team->players[j] != NULL)
            return 1;
    }
    return 0;
}

// Verify for each team and call check_team_levels
int check_game_end(server_t *server)
{
    int alive_teams = 0;
    int winning_team_index = -1;

    for (int i = 0; i < server->team_nb; i++) {
        if (is_team_alive(server->teams[i])) {
            alive_teams++;
            winning_team_index = i;
        }
    }
    if (alive_teams == 1) {
        printf("Team %s has won\n", server->teams[winning_team_index]->name);
        event_seg(server, server->teams[winning_team_index]->name);
        return 1;
    }
    for (int i = 0; i < server->team_nb; i++)
        if (check_team_levels(server, server->teams[i]) == 1)
            return 1;
    return 0;
}
