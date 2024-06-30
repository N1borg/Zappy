/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include "server.h"

static int apply_dir(int sound, client_t *player)
{
    int adjust = (WEST - player->orientation) * (2);

    if (sound - adjust < 0)
        sound += 8;
    return sound - adjust;
}

/// @brief the numbers 2-3-4 and 6-7-8 are mirrored because
/// the trigonometric circle is in the wrong direction clockwise.
static int get_index(float angle, client_t *player)
{
    if (angle < 22.5 || angle >= 337.5)
        return apply_dir(1, player);
    if (angle < 67.5 && angle >= 22.5)
        return apply_dir(8, player);
    if (angle < 112.5 && angle >= 67.5)
        return apply_dir(7, player);
    if (angle < 157.5 && angle >= 112.5)
        return apply_dir(6, player);
    if (angle < 202.5 && angle >= 157.5)
        return apply_dir(5, player);
    if (angle < 247.5 && angle >= 202.5)
        return apply_dir(4, player);
    if (angle < 292.5 && angle >= 247.5)
        return apply_dir(3, player);
    if (angle < 337.5 && angle >= 292.5)
        return apply_dir(2, player);
    return 0;
}

static void get_shortest_vector(server_t *serv, int *x, int *y)
{
    if (*x < 0)
        *x = *x * (-1) <= serv->width / 2 ? *x : *x + (serv->width + 1);
    else
        *x = *x <= serv->width / 2 ? *x : *x - (serv->width + 1);
    if (*y < 0)
        *y = *y * (-1) <= serv->height / 2 ? *y : *y + (serv->height + 1);
    else
        *y = *y <= serv->height / 2 ? *y : *y - (serv->height + 1);
}

/// @brief use a trigonometric circle to calculate the incidence angle
/// using the coordinates of a vector
/// @param serv used to check for the map size
/// @param sender used to set the origin point of the vector
/// @param receiver used to set the end point of the vector and get the
/// orientation
/// @return a number between 1 and 8,
/// representing the direction from which the sound is heard
int get_broadcast_dir(server_t *serv, client_t *src, client_t *dest)
{
    int x_dir = dest->x - src->x;
    int y_dir = dest->y - src->y;
    double angle;

    if (src->x == dest->x && src->y == dest->y)
        return 0;
    get_shortest_vector(serv, &x_dir, &y_dir);
    angle = atan2((double)y_dir, (double)x_dir) * (180 / M_PI);
    if (angle < 0)
        angle += 360;
    return get_index(angle, dest);
}

// Sends a message to all players
int command_broadcast(server_t *serv, client_t *player, char *arg)
{
    if (arg == NULL)
        return 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (serv->clients[i] && serv->clients[i]->team != NULL &&
            serv->clients[i]->id != player->id && serv->clients[i]->id != 0)
            dprintf(serv->clients[i]->fd, "message %d, %s\n",
                    get_broadcast_dir(serv, player, serv->clients[i]), arg);
    }
    event_pbc(serv, player, arg);
    return success_response(player);
}
