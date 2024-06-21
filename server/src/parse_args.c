/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** Parse arguments & init stucture
*/

#include "server.h"

void init_team(team_t *teams, char *name)
{
    teams->free_slots = 0;
    teams->name = name;
    for (int i = 0; i < MAX_CLIENTS; i++)
        teams->players[i] = NULL;
    teams->eggs = NULL;
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
}

// Get the parameters from the arguments
void get_param(server_t *serv, int argc, char *argv[])
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            serv->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            serv->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            serv->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL) {
            serv->freq = atoi(argv[i + 1]);
            serv->interval = 1000000000 / serv->freq;
        }
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            serv->max_client_team = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL) {
            serv->teams = malloc(sizeof(team_t *) * (argc - i));
            get_team_names(&argv[i], serv->teams);
        }
    }
}

// Parse arguments and fill the server struct
server_t parse_args(int argc, char *argv[])
{
    server_t serv = {0};

    serv.port = 0;
    serv.width = 0;
    serv.height = 0;
    serv.freq = 100;
    serv.elapsed_time = 0;
    serv.max_client_team = 0;
    serv.teams = NULL;
    get_param(&serv, argc, argv);
    for (int i = 0; serv.teams[i + 1]; i++)
        serv.teams[i]->free_slots = serv.max_client_team;
    serv.teams[get_team_id(&serv, "GRAPHIC")]->free_slots = MAX_CLIENTS;
    serv.team_nb = tablen(serv.teams);
    return serv;
}
