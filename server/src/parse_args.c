/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** parse_args
*/

#include "../include/main.h"

int tablen(char **tab)
{
    int i = 0;

    for (; tab && tab[i]; i++);
    return i;
}

char **get_team_names(char **argv, int argc, int i)
{
    char **team_names = malloc(sizeof(char *) * (argc - (i + 1)));
    int j = 0;

    for (j = 1; argv[i + j]; j++) {
        if (argv[i + j][0] == '-')
            break;
        team_names[j - 1] = argv[i + j];
    }
    team_names[j - 1] = NULL;
    return team_names;
}

server_t get_param(server_t server, int argc, char *argv[])
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            server.port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            server.width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            server.height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            server.freq = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            server.max_client = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL)
            server.team_names = get_team_names(argv, argc, i);
    }
    return server;
}

server_t init_server(server_t server, int argc, char *argv[])
{
    server.port = 0;
    server.width = 0;
    server.height = 0;
    server.freq = 0;
    server.max_client = 0;
    server.team_names = NULL;
    for (int i = 0; argv[i]; i++)
        server = get_param(server, argc, argv);
    server.team_nb = tablen(server.team_names);
    return server;
}
