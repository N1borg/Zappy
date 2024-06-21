/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** destroy
*/

#include "server.h"

// Free eggs memory
void destroy_eggs(server_t *serv)
{
    for (int i = 0; serv->map[i]; i++) {
        for (int j = 0; serv->map[i][j].eggs; j++) {
            destroy_eggs_pointer(serv->map[i][j].eggs);
        }
    }
}

// Free clients memory
void destroy_clients(server_t *serv)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i]->fd > 0)
            close(serv->clients[i]->fd);
        free_command_queue(serv->clients[i]->command_queue);
        free(serv->clients[i]);
    }
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
    destroy_clients(serv);
    destroy_teams(serv->teams);
    destroy_eggs(serv);
    destroy_map(serv->map);
    printf("Server closed\n");
    return ret;
}
