/*
** EPITECH PROJECT, 2023
** B-YEP-400-LIL-4-1-zappy-romaric.loevenbruck
** File description:
** command_queue.c
*/

#include "../include/main.h"

// Initialize the command queue of the client
void init_command_queue(client_t *client)
{
    client->command_queue = malloc(sizeof(command_queue_t));

    if (client->command_queue == NULL)
        return;
    client->command_queue->front = NULL;
    client->command_queue->back = NULL;
    client->command_queue->size = 0;
}

// Enqueue a command in the command queue of the client
int enqueue_command(client_t *client, char *command_str)
{
    command_t *new_command = NULL;

    if (client->size >= 10)
        return 1;
    new_command = malloc(sizeof(command_t));
    if (new_command == NULL)
        return 84;
    new_command->command = strdup(command_str);
    if (new_command->command == NULL) {
        free(new_command);
        return 84;
    }
    new_command->next = NULL;
    if (client->command_queue->back == NULL) {
        client->command_queue->front = new_command;
        client->command_queue->back = new_command;
    } else {
        client->command_queue->back->next = new_command;
        client->command_queue->back = new_command;
    }
    client->command_queue->size++;
    return 0;
}

// Dequeue a command from the command queue of the client
char *dequeue_command(command_queue_t *queue)
{
    command_t *command_node = NULL;
    char *command_str = NULL;

    if (queue->front == NULL)
        return NULL;
    command_node = queue->front;
    command_str = strdup(command_node->command);
    if (command_str == NULL)
        return NULL;
    queue->front = command_node->next;
    if (queue->front == NULL)
        queue->back = NULL;
    free(command_node->command);
    free(command_node);
    queue->size--;
    return command_str;
}
