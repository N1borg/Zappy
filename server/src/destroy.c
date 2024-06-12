/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** destroy
*/

#include "../include/main.h"

// free clients memory
void destroy_clients(client_t *clients[MAX_CLIENTS])
{
    for (int i = 0; clients[i]; i++)
        free(clients[i]);
}

// free teams memory
void destroy_teams(team_t **teams)
{
    for (int i = 0; teams[i]; i++)
        free(teams[i]);
    free(teams);
}

// free map memory
void destroy_map(tile_t **map)
{
    for (int i = 0; map[i]; i++)
        free(map[i]);
    free(map);
}

// Close sockets and free memory
int destroy_server(server_t *s, int ret)
{
    close(s->master_socket);
    for (int i = 0; i < s->max_client_team; i++)
        close(s->clients[i]->fd);
    free(s->teams);
    destroy_clients(s->clients);
    destroy_map(s->map);
    printf("Server closed\n");
    return ret;
}
