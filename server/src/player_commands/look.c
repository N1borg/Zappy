/*
** EPITECH PROJECT, 2024
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** looking
*/

#include "../../include/main.h"

// Initialize the look command
int init_look(client_t *client, char *buffer)
{
    if (buffer != NULL) {
        buffer[0] = '\0';
        buffer = strcpy(buffer, "[");
    }
    if (client->orientation == NORTH)
        return -1;
    if (client->orientation == WEST)
        return -1;
    return 1;
}

// Format and send the buffer to the client
int send_buffer(char *buffer, client_t *client)
{
    if (strlen(buffer) > 2)
        buffer[strlen(buffer) - 2] = '\0';
    strcat(buffer, "]");
    dprintf(client->fd, "%s\n", buffer);
    free(buffer);
    return 0;
}

// Send the content of the tiles in front of the player
int command_look(server_t *s, client_t *client, char *arg)
{
    int loop = (client->orientation % 2);
    char *buffer = malloc(sizeof(char) * buffer_len(s, client));
    int vec = init_look(client, buffer);

    if (arg != NULL)
        return 1;
    for (int i = 0; loop && i <= client->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++)
            display_tile(&s->map[y_to_map_y(s, client->y + i * vec)]
                [x_to_map_x(s, client->x + ((j * -vec) + i * vec))], buffer);
    }
    for (int i = 0; !loop && i <= client->level; i++) {
        for (int j = 0; j < (i * 2 + 1); j++)
            display_tile(
                &s->map[y_to_map_y(s, client->y - ((j * -vec) + i * vec))]
                [x_to_map_x(s, client->x + i * vec)], buffer);
    }
    return send_buffer(buffer, client);
}
