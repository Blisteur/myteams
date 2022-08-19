/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** client
*/

#include "client.h"

static void renitialize_client(client_t *client)
{
    FD_ZERO(&client->readfds);
    FD_ZERO(&client->writefds);
    FD_SET(0, &client->readfds);
    FD_SET(client->server_fd, &client->readfds);
    if (client->is_write)
        FD_SET(client->server_fd, &client->writefds);
}

static int client_loop(client_t *client)
{
    int handler = 0;
    while (client->is_running) {
        renitialize_client(client);
        handler = select(client->server_fd + 1, &client->readfds
        , &client->writefds, NULL, NULL);
        if (handler == -1 && errno != EINTR) {
            fprintf(stdout, "Error: select failed | %s\n", strerror(errno));
            return (84);
        }
        if (handler == -1 && errno == EINTR)
            return (0);
        if (FD_ISSET(0, &client->readfds))
            cli(client);
        if (FD_ISSET(client->server_fd, &client->readfds))
            receive_msg_from_server(client);
        if (FD_ISSET(client->server_fd, &client->writefds))
            send_msg_to_server(client);
    }
    destroy_client(client);
    return (0);
}

int client(int port, char *ip)
{
    client_t *client = creat_client(ip, port);

    if (client == NULL)
        return (84);
    return (client_loop(client));
}
