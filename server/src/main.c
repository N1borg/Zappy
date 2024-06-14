/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "../include/main.h"

// free map memory
void destroy_map(tile_t **map)
{
    for (int i = 0; map[i]; i++)
        free(map[i]);
    free(map);
}

// Close sockets and free memory
int destroy_server(server_t *server, int ret)
{
    close(server->master_socket);
    for (int i = 0; i < server->max_client_team; i++)
        close(server->client_socket[i]);
    free(server->team_names);
    destroy_map(server->map);
    printf("Server closed\n");
    return ret;
}

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
