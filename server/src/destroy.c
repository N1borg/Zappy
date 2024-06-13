/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** destroy
*/

#include "../include/main.h"

// Free clients memory
void destroy_clients(server_t *s)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        free(s->clients[i]);
}

// Free teams memory
void destroy_teams(team_t **teams)
{
    for (int i = 0; teams[i]; i++)
        free(teams[i]);
    free(teams);
}

// Free map memory
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
    for (int i = 0; i < s->max_client_team * s->team_nb; i++)
        close(s->clients[i]->fd);
    for (int i = 0; s->teams[i]; i++)
        free(s->teams[i]);
    free(s->teams);
    destroy_clients(s);
    destroy_map(s->map);
    printf("Server closed\n");
    return ret;
}
