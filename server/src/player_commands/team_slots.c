/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** team_slots
*/

#include "server.h"

// Send the number of free slots in the team
int command_team_slots(server_t *serv, client_t *player, char *arg)
{
    if (arg != NULL)
        return 1;
    dprintf(player->fd, "%d\n",
    serv->teams[get_team_id(serv, player->team)]->free_slots);
    return 0;
}
