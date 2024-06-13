/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parse arguments & init stucture
*/

#include "../include/main.h"

void init_team(team_t *teams, char *name)
{
    teams->free_slots = 0;
    teams->name = name;
    for (int i = 0; i < MAX_CLIENTS; i++)
        teams->players[i] = NULL;
}

// Get the team names from the arguments
void get_team_names(char **argv, team_t **teams)
{
    int i = 0;
    char *graphic_team = "GRAPHIC";

    for (i = 1; argv[i] && argv[i][0] != '-'; i++) {
        teams[i - 1] = malloc(sizeof(team_t));
        init_team(teams[i - 1], argv[i]);
    }
    teams[i - 1] = malloc(sizeof(team_t));
    init_team(teams[i - 1], graphic_team);
    teams[i] = NULL;
    printf("TEAM NAMES:\n");
    for (int k = 0; teams[k]; k++)
        printf("Team %d: %s\n", k, teams[k]->name);
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
            server->teams = malloc(sizeof(team_t *) * (argc - i));
            get_team_names(&argv[i], server->teams);
        }
    }
}

// Parse arguments and fill the server struct
server_t parse_args(int argc, char *argv[])
{
    server_t server = {0};

    server.port = 0;
    server.width = 0;
    server.height = 0;
    server.freq = 100;
    server.max_client_team = 0;
    server.teams = NULL;
    get_param(&server, argc, argv);
    for (int i = 0; server.teams[i + 1]; i++)
        server.teams[i]->free_slots = server.max_client_team;
    server.teams[get_team_id(&server, "GRAPHIC")]->free_slots = MAX_CLIENTS;
    server.team_nb = tablen(server.teams);
    return server;
}
