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
#include <errno.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

typedef struct server_s {
    int port;
    int width;
    int height;
    int freq;
    int max_client;
    int team_nb;
    char **team_names;
}   server_t;

int help(char *binary_name, int ret);
server_t init_server(server_t server, int argc, char *argv[]);
