/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "server.h"

void handle_sigpipe(int sig __attribute__((unused)))
{
}

int main(int argc, char *argv[])
{
    server_t serv = parse_args(argc, argv);

    signal(SIGPIPE, handle_sigpipe);
    srand(time(NULL));
    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        return help(argv[0], 0, &serv);
    if (serv.port <= 0 || serv.port > 65535 || serv.width <= 0 ||
        serv.height <= 0 || serv.freq <= 0 || serv.max_client_team <= 0
        || serv.team_nb <= 0)
        return help(argv[0], 84, &serv);
    init_server(&serv);
    if (init_socket(&serv) != 0 || init_listener(&serv) != 0)
        return destroy_server(&serv, 84);
    if (start_listener(&serv) != 0)
        return destroy_server(&serv, 84);
    return destroy_server(&serv, 0);
}
