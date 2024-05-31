/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "../include/main.h"

int destroy_server(server_t *server, int ret)
{
    close(server->master_socket);
    for (int i = 0; i < server->max_client_team; i++)
        close(server->client_socket[i]);
    free(server->team_names);
    return ret;
}

int main(int argc, char *argv[])
{
    server_t server = init_server(server, argc, argv);

    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        return help(argv[0], 0);
    if (server.port <= 0 || server.port > 65535 || server.width <= 0 ||
        server.height <= 0 || server.freq <= 0 || server.max_client_team <= 0
        || server.team_nb <= 0)
        return help(argv[0], 84);
    printf("port: %d\n", server.port);
    printf("width: %d\n", server.width);
    printf("height: %d\n", server.height);
    printf("freq: %d\n", server.freq);
    printf("max_client: %d\n", server.max_client_team);
    printf("team_nb: %d\n", server.team_nb);
    for (int i = 0; server.team_names && server.team_names[i]; i++)
        printf("team_names[%d]: %s\n", i, server.team_names[i]);
    if (start_litener(&server) != 0)
        return destroy_server(&server, 84);
    return destroy_server(&server, 0);
}
