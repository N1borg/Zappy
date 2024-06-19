/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** looking
*/

#include "server.h"

// Initialize the look command
int init_look(client_t *player, char *buffer)
{
    if (buffer != NULL) {
        buffer[0] = '\0';
        buffer = strcpy(buffer, "[");
    }
    if (player->orientation == NORTH)
        return -1;
    if (player->orientation == WEST)
        return -1;
    return 1;
}

// Format and send the buffer to the client
int send_buffer(char *buffer, client_t *player)
{
    if (strlen(buffer) > 2)
        buffer[strlen(buffer) - 2] = '\0';
    strcat(buffer, "]");
    dprintf(player->fd, "%s\n", buffer);
    free(buffer);
    return 0;
}

// Send the content of the tiles in front of the player
int command_look(server_t *serv, client_t *player, char *arg)
{
    int loop = (player->orientation % 2);
    char *buffer = malloc(sizeof(char) * buffer_len(serv, player));
    int vec = init_look(player, buffer);

    if (arg != NULL)
        return 1;
    for (int i = 0; loop && i <= player->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++)
            display_tile(&serv->map[y_to_map_y(serv, player->y + i * vec)]
            [x_to_map_x(serv, player->x + ((j * -vec) + i * vec))], buffer);
    }
    for (int i = 0; !loop && i <= player->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++)
            display_tile(
            &serv->map[y_to_map_y(serv, player->y - ((j * -vec) + i * vec))]
            [x_to_map_x(serv, player->x + i * vec)], buffer);
    }
    return send_buffer(buffer, player);
}
