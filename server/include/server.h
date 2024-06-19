/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** server
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#include "player.h"
#include "tile.h"

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

typedef struct command_map {
    const char *command;
    int (*command_function)(server_t *serv, client_t *client, char *arg);
    int time_limit;
} command_map_t;

int help(char *binary_name, int ret, server_t *serv);
server_t parse_args(int argc, char *argv[]);
int start_listener(server_t *serv);
int init_socket(server_t *serv);
int init_listener(server_t *serv);
void accept_client(server_t *serv);
void disconnect_client(server_t *serv, client_t *client);
void destroy_map(tile_t **map);
void init_server(server_t *serv);
void compute_response(server_t *serv, client_t *client, char *buffer);
int is_team(server_t *serv, char *team_name);
int is_player(server_t *serv, int socket);
int tablen(team_t **tab);
int create_player(server_t *serv, client_t *client, char *team_name);
void set_client(client_t *clients);
int get_player_id_on_map(tile_t *tile, client_t *client);
int move_player(server_t *serv, client_t *client, int x, int y);
int get_team_id(server_t *serv, char *team_name);
int x_to_map_x(server_t *serv, int x);
int y_to_map_y(server_t *serv, int y);
void destroy_clients(server_t *serv);
void destroy_teams(team_t **teams);
void destroy_map(tile_t **map);
int destroy_server(server_t *serv, int ret);
int add_player_to_team(server_t *serv, client_t *player, char *team_name);
client_t *get_client_by_id(server_t *serv, int id);
int get_nbr_eggs_on_tile(tile_t *tile);
int add_egg(team_t *team, tile_t *tile);
int remove_egg(egg_t *egg);
int destroy_eggs_from_tiles(tile_t *tile);
void destroy_eggs(server_t *serv);
void init_command_queue(client_t *client);
int enqueue_command(client_t *client, char *command_str);
char *dequeue_command(command_queue_t *queue);
void free_command_queue(command_queue_t *queue);
void manage_queue(client_t *client, char *buffer);

// player commands
int success_response(client_t *client);
int command_forward(server_t *serv, client_t *client, char *arg);
int command_turn_right(server_t *serv __attribute__((unused)),
    client_t *client, char *arg);
int command_turn_left(server_t *serv __attribute__((unused)),
    client_t *client, char *arg);
int init_look(client_t *client, char *buffer);
int command_look(server_t *serv, client_t *client, char *arg);
int buffer_len(server_t *serv, client_t *client);
int command_inventory(server_t *serv, client_t *client, char *arg);
int command_fork(server_t *serv, client_t *client, char *arg);
int command_take_object(server_t *serv, client_t *client, char *arg);
int command_set_object(server_t *serv, client_t *client, char *arg);
int command_eject(server_t *serv, client_t *client, char *arg);
int command_broadcast(server_t *serv, client_t *client, char *arg);
int command_incantation(server_t *serv, client_t *client, char *arg);
int command_team_slots(server_t *serv, client_t *client, char *arg);

// graphic commands
void send_tile_content(server_t *serv, client_t *client, int x, int y);
int command_bct(server_t *serv, client_t *client, char *arg);
int command_mct(server_t *serv, client_t *client, char *arg);
int command_msz(server_t *serv, client_t *client, char *arg);
int command_pin(server_t *serv, client_t *client, char *arg);
int command_plv(server_t *serv, client_t *client, char *arg);
int command_ppo(server_t *serv, client_t *client, char *arg);
int command_sgt(server_t *serv, client_t *client, char *arg);
int command_sst(server_t *serv, client_t *client, char *arg);
int command_tna(server_t *serv, client_t *client, char *arg);

// graphic events
void event_pbc(server_t *serv, client_t *player, char *message);
void event_pdi(server_t *serv, client_t *player);
void event_pdr(server_t *serv, client_t *player, int ressource);
void event_pex(server_t *serv, client_t *player);
void event_pfk(server_t *serv, client_t *player);
void event_pgt(server_t *serv, client_t *player, int ressource);
void event_pnw(server_t *serv, client_t *player);
void event_pie(server_t *serv, client_t *player, char *result);
void event_sbp(client_t *client);
void event_seg(server_t *serv, char *team);
void event_smg(server_t *serv, char *msg);
void event_suc(client_t *client);

// Resource management functions
void generate_resources(server_t *serv);
