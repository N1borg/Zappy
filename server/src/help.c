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
    printf("\tport\t\tis the port number (1 - 65535)\n");
    printf("\twidth\t\tis the width of the world (1 - 50)\n");
    printf("\theight\t\tis the height of the world (1 - 50)\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients ");
    printf("per team (1 - 50)\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution ");
    printf("of actions (>=0)\n");
    if (serv->teams)
        destroy_teams(serv->teams);
    return ret;
}
