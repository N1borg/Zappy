/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "../include/main.h"

int main(int argc, char *argv[])
{
    server_t server = parse_args(argc, argv);

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
