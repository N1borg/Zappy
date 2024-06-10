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

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct client_s {
    int fd;
    int x;
    int y;
    int level;
    orientation_t orientation;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    char *team;
} client_t;

typedef struct team_s {
    char *name;
    int size;
    client_t *players[MAX_CLIENTS];
} team_t;

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
    client_t *players[MAX_CLIENTS];
} tile_t;

typedef struct server_s {
    int port;
    int width;
    int height;
    int freq;
    int max_client_team;
    int team_nb;
    team_t **teams;
    int master_socket;
    struct sockaddr_in addr;
    fd_set readfds;
    client_t *clients[MAX_CLIENTS];
    tile_t **map;
} server_t;

typedef struct {
    char *name;
    double density;
    int *resource_ptr;
} resource_density_t;

resource_density_t resources[] = {
    {"food", 0.5, NULL},
    {"linemate", 0.3, NULL},
    {"deraumere", 0.15, NULL},
    {"sibur", 0.1, NULL},
    {"mendiane", 0.1, NULL},
    {"phiras", 0.08, NULL},
    {"thystame", 0.05, NULL}
};

struct CommandMap {
    const char *command;
    int (*CommandFunction)(server_t *s, client_t *client);
};

int help(char *binary_name, int ret, server_t *server);
server_t parse_args(server_t server, int argc, char *argv[]);
int start_litener(server_t *server);
int init_socket(server_t *server);
int init_listener(server_t *server);
void accept_client(server_t *s);
void disconnect_client(server_t *s, client_t *client);
void destroy_map(tile_t **map);
void init_server(server_t *server);
void compute_response(server_t *s, client_t *client, char *buffer);
int is_team(server_t *s, char *team_name);
int is_player(server_t *s, int socket);
int tablen(team_t **tab);
int create_player(server_t *s, client_t *client, char *team_name);
void set_client(client_t *clients);
int wich_player_on_map(server_t *s, client_t *client, int x, int y);
int move_player(server_t *s, client_t *client, int x, int y);

// client commands
int command_move_up(server_t *s, client_t *client);
int command_turn_right(server_t *s, client_t *client);
int command_turn_left(server_t *s, client_t *client);
int command_look_around(server_t *s, client_t *client);
int command_inventory(server_t *s, client_t *client);
int command_fork(server_t *s, client_t *client);
int command_take_object(server_t *s, client_t *client);
int command_set_object(server_t *s, client_t *client);

// Resource management functions
void init_resource_pointers(tile_t *tile);
void spread_resources(server_t *server, double density, int *resource_ptr);
void init_resources(server_t *server);
void generate_resources(server_t *server);
