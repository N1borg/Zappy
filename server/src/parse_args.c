/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parse arguments & init stucture
*/

#include "../include/main.h"

// Get the number of elements in a table
int tablen(char **tab)
{
    int i = 0;

    for (; tab && tab[i]; i++);
    return i;
}

// Get the team names from the arguments
void get_team_names(char **argv, int argc, int i, char **team_names)
{
    int j = 0;

    for (j = 1; argv[i + j]; j++) {
        if (argv[i + j][0] == '-')
            break;
        team_names[j - 1] = argv[i + j];
    }
    team_names[j - 1] = NULL;
}

// Get the parameters from the arguments
void get_param(server_t *server, int argc, char *argv[])
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            server->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            server->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            server->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            server->freq = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            server->max_client_team = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL) {
            server->team_names = malloc(sizeof(char *) * (argc - (i + 1)));
            get_team_names(argv, argc, i, server->team_names);
        }
    }
}

// Parse arguments and fill the server struct
server_t parse_args(server_t server, int argc, char *argv[])
{
    server.port = 0;
    server.width = 0;
    server.height = 0;
    server.freq = 100;
    server.max_client_team = 0;
    server.team_names = NULL;
    get_param(&server, argc, argv);
    server.team_nb = tablen(server.team_names);
    return server;
}
