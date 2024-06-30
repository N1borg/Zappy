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
void get_team_names(server_t *serv, int argc, char **argv, int start_index)
{
    int num_teams = argc - start_index + 1;
    char *graphic_team = "GRAPHIC";
    int i = 0;

    serv->teams = malloc(sizeof(team_t *) * (num_teams + 1));
    if (!serv->teams) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < num_teams - 1; i++) {
        serv->teams[i] = malloc(sizeof(team_t));
        if (!serv->teams[i]) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        init_team(serv->teams[i], argv[start_index + i]);
    }
    serv->teams[i] = malloc(sizeof(team_t));
    if (!serv->teams[i]) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    init_team(serv->teams[i], graphic_team);
    serv->teams[i + 1] = NULL;
}

// Get the parameters from the arguments
static void get_param(server_t *serv, int argc, char *argv[])
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            serv->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            serv->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            serv->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            serv->freq = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            serv->max_client_team = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL)
            get_team_names(serv, argc, argv, i + 1);
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
    serv.timeout.tv_sec = 0;
    serv.timeout.tv_usec = 0;
    serv.max_client_team = 0;
    serv.teams = NULL;
    get_param(&serv, argc, argv);
    if (!serv.teams)
        return serv;
    for (int i = 0; serv.teams[i + 1]; i++)
        serv.teams[i]->free_slots = serv.max_client_team;
    serv.teams[get_team_id(&serv, "GRAPHIC")]->free_slots = MAX_CLIENTS;
    serv.team_nb = tablen(serv.teams);
    return serv;
}
