/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy
*/

#include "server.h"

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
    egg_t *next_egg = NULL;
    egg_t *current_egg = NULL;

    for (int i = 0; teams[i]; i++) {
        current_egg = teams[i]->eggs;
        while (current_egg != NULL) {
            next_egg = current_egg->next_team;
            free(current_egg);
            current_egg = next_egg;
        }
        free(teams[i]);
    }
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
    destroy_map(serv->map);
    printf("Server closed\n");
    return ret;
}
