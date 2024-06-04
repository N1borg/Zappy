/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** rotating
*/

#include "../../include/main.h"

// Increase the orientation of the client by 1
int command_turn_right(server_t *s, client_t *client)
{
    int temp = client->orientation;

    printf("ACTUAL ORIENTATION: %d\n", client->orientation);
    client->orientation = (temp == 4) ? 1 : temp + 1;
    printf("NEW ORIENTATION: %d\n", client->orientation);
    return 0;
}

// Decrease the orientation of the client by 1
int command_turn_left(server_t *s, client_t *client)
{
    int temp = client->orientation;

    printf("ACTUAL ORIENTATION: %d\n", client->orientation);
    client->orientation = (temp == 1) ? 4 : temp - 1;
    printf("NEW ORIENTATION: %d\n", client->orientation);
    return 0;
}
