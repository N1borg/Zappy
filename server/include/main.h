/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** main
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#define MAX_CLIENTS 100

typedef struct client_s {
    int fd;
    int level;
    int orientation;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int egg;
    int team;
} client_t;

typedef struct tile_s {
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int egg;
    int players;
} tile_t;

typedef struct server_s {
    int port;
    int width;
    int height;
    int freq;
    int max_client_team;
    int team_nb;
    char **team_names;
    int master_socket;
    int client_socket[MAX_CLIENTS];
    struct sockaddr_in addr;
    fd_set readfds;
    tile_t **map;
} server_t;

int help(char *binary_name, int ret, server_t *server);
server_t parse_args(server_t server, int argc, char *argv[]);
int start_litener(server_t *server);
int init_socket(server_t *server);
int init_listener(server_t *server);
void accept_client(server_t *s);
void disconnect_client(server_t *s, int sd);
void destroy_map(tile_t **map);
void init_server(server_t *server);
