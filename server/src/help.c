/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** help function
*/

#include "../include/main.h"

// Print the help message, free the team names and return the given value
int help(char *binary_name, int ret, server_t *server)
{
    printf("USAGE: %s -p port -x width -y height -n name1 name2", binary_name);
    printf(" ... -c clientsNb -f freq\n");
    free(server->team_names);
    return ret;
}
