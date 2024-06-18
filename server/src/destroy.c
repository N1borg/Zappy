/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** destroy
*/

#include "server.h"

// Free clients memory
void destroy_clients(server_t *serv)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
        free(serv->clients[i]);
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
int destroy_server(server_t *serv, int ret)
{
    close(serv->master_socket);
    for (int i = 0; i < serv->max_client_team * serv->team_nb; i++)
        close(serv->clients[i]->fd);
    for (int i = 0; serv->teams[i]; i++)
        free(serv->teams[i]);
    free(serv->teams);
    destroy_clients(serv);
    destroy_map(serv->map);
    printf("Server closed\n");
    return ret;
}
