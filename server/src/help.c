/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** help function
*/

#include "server.h"

// Print the help message, free the team names and return the given value
int help(char *binary_name, int ret, server_t *serv)
{
    printf("USAGE: %s -p port -x width -y height -n name1 name2", binary_name);
    printf(" ... -c clientsNb -f freq\n");
    free(serv->teams);
    return ret;
}
