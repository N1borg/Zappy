/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** broadcast
*/

#include "server.h"

/// @brief use a trigonometric circle to calculate the incidence angle
/// using the coordinates of a vector
/// @param serv used to check for the map size
/// @param sender used to set the origin point of the vector
/// @param receiver used to set the end point of the vector and get the
/// orientation
/// @return a number between 1 and 8,
/// representing the direction from which the sound is heard
int get_broadcast_dir(server_t *serv, client_t *sender, client_t *receiver)
{
    int x_dir = receiver->x - sender->x;
    int y_dir = receiver->y - sender->y;
    float angle;
    int dir;

    x_dir = x_dir <= serv->width / 2 ? x_dir : x_dir * (-1);
    y_dir = y_dir <= serv->height / 2 ? y_dir : y_dir * (-1);
    angle = arctan(y_dir, x_dir) * 180 / pi();
    dir = round(fmod((((angle - fmod(angle, 22.5)) / 22.5) / 2), 8)) + 1;
    return angle;
}

// Sends a message to all players
int command_broadcast(server_t *serv, client_t *player, char *arg)
{
    if (arg == NULL)
        return 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team != NULL &&
            serv->clients[i]->id != player->id && serv->clients[i]->id != 0)
            dprintf(serv->clients[i]->fd, "message %d, %s\n", arg,
                    get_broadcast_dir(serv, player, serv->clients[i]));
    }
    event_pbc(serv, player, arg);
    return success_response(player);
}
