/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** send
*/

#include "client.h"

void send_msg_to_server(client_t *client)
{
    ssize_t lenght = 0;

    lenght = write(client->server_fd, client->buffer_write
            , BUFFER);
    if (lenght == -1) {
        fprintf(stdout, "Error: write failed | %s\n", strerror(errno));
        return;
    }
    client->buffer_lock_write = 0;
    client->is_write = false;
}
