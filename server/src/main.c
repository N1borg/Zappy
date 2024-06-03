/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
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

// Have I really to explain this ?
int main(int argc, char *argv[])
{
    server_t server = parse_args(server, argc, argv);

    srand(time(NULL));
    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        return help(argv[0], 0, &server);
    if (server.port <= 0 || server.port > 65535 || server.width <= 0 ||
        server.height <= 0 || server.freq <= 0 || server.max_client_team <= 0
        || server.team_nb <= 0)
        return help(argv[0], 84, &server);
    init_server(&server);
    if (start_litener(&server) != 0)
        return destroy_server(&server, 84);
    return destroy_server(&server, 0);
}
