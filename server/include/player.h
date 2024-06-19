/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** player
*/

#pragma once

#include "egg.h"

#define MAX_CLIENTS 2048

#ifndef FD_SETSIZE
    #define FD_SETSIZE MAX_CLIENTS
#else
    #undef FD_SETSIZE
    #define FD_SETSIZE MAX_CLIENTS
#endif

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct command_s {
    char *command;
    struct command_s *next;
} command_t;

typedef struct command_queue_s {
    command_t *front;
    command_t *back;
    int size;
} command_queue_t;

typedef struct client_s {
    int fd;
    int id;
    int x;
    int y;
    int level;
    bool is_incanting;
    orientation_t orientation;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    char *team;
    command_queue_t *command_queue;
} client_t;

typedef struct team_s {
    char *name;
    int free_slots;
    client_t *players[MAX_CLIENTS];
    egg_t *eggs;
} team_t;
