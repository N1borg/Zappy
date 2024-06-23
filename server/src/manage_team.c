/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** manage_team
*/

#include "server.h"

// Return the index of the team in the server based on it's name
int get_team_id(server_t *serv, char *team_name)
{
    for (int i = 0; serv->teams[i] && serv->teams[i]->name; i++) {
        if (strcmp(team_name, serv->teams[i]->name) == 0)
            return i;
    }
    return -1;
}

// Add a player to a team based on it's name
int add_player_to_team(server_t *serv, client_t *player, char *team_name)
{
    int i = 0;
    int j = 0;

    if (player == NULL || team_name == NULL)
        return 1;
    for (; serv->teams[i] && strcmp(team_name, serv->teams[i]->name); i++);
    if (serv->teams[i] && serv->teams[i]->free_slots >= 1
        && strcmp(team_name, serv->teams[i]->name) == 0) {
        for (; j < MAX_CLIENTS && serv->teams[i]->players[j]; j++);
        if (j < MAX_CLIENTS) {
            serv->teams[i]->players[j] = player;
            player->team = serv->teams[i]->name;
            player->level = 1;
        } else
            return 1;
    } else
        return 1;
    return 0;
}

// Add a graphic to a team based on it's name
int add_graphic_to_team(server_t *serv, client_t *graphic)
{
    int i = 0;
    int j = 0;

    if (graphic == NULL)
        return 1;
    for (; serv->teams[i] && strcmp("GRAPHIC", serv->teams[i]->name); i++);
    if (serv->teams[i] && serv->teams[i]->free_slots >= 1
        && strcmp("GRAPHIC", serv->teams[i]->name) == 0) {
        for (; j < MAX_CLIENTS && serv->teams[i]->players[j]; j++);
        if (j < MAX_CLIENTS) {
            serv->teams[i]->players[j] = graphic;
            graphic->team = serv->teams[i]->name;
        } else
            return 1;
    } else
        return 1;
    return 0;
}
