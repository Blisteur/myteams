/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** server
*/

#include "server.h"
#include "sig_handler_server.h"

static void client_handler(server_t *server)
{
    linked_client_t *tmp = server->first_client;
    int lenght = 0;

    for (; tmp != NULL; tmp = tmp->next) {
        if (client_handler_extended(server, lenght, tmp) == 1)
            return;
    }
}

static void new_client(server_t *server)
{
    char ip[INET_ADDRSTRLEN];

    if (FD_ISSET(server->server_fd, &server->readfds)) {
        server->first_client
        = add_client(server->first_client, server->server_fd);
        if (server->first_client == NULL) {
            fprintf(stdout, "Error: new client connection failed\n");
            return;
        }
        fprintf(stdout, "New client connected on %d fd | ip:%s | port:%d\n"
        , server->first_client->client_fd
        , inet_ntop(AF_INET, &server->first_client->client_addr.sin_addr, ip
        , INET_ADDRSTRLEN), ntohs(server->first_client->client_addr.sin_port));
        FD_SET(server->first_client->client_fd, &server->readfds);
        if (server->first_client->client_fd > server->max_fd)
            server->max_fd = server->first_client->client_fd;
        write(server->first_client->client_fd, CODE_220, strlen(CODE_220));
    }
}

static void reset_fd(server_t *server)
{
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(0, &server->readfds);
    FD_SET(server->server_fd, &server->readfds);
    for (linked_client_t *tmp = server->first_client; tmp != NULL
    ; tmp = tmp->next)
        FD_SET(tmp->client_fd, &server->readfds);
    for (linked_client_t *tmp = server->first_client; tmp != NULL
        ; tmp = tmp->next)
        if (tmp->writeable == true)
            FD_SET(tmp->client_fd, &server->writefds);
}

static void get_client_fd_is_set(server_t *server)
{
    for (linked_client_t *tmp = server->first_client; tmp != NULL
    ; tmp = tmp->next)
        if (FD_ISSET(tmp->client_fd, &server->writefds))
            send_json_final(tmp);
}

int teams_server_loop(server_t *server, int port)
{
    int handler = 0;
    fprintf(stdout, "Waiting for a connection on port: %d\n", port);
    while (server->is_running && !sig_handler_called) {
        reset_fd(server);
        handler = select(server->max_fd + 1, &server->readfds
        , &server->writefds, NULL, NULL);
        if (handler == -1) {
            fprintf(stdout, "Error: select failed | %s\n", strerror(errno));
            return (84);
        }
        if (handler == -1 && errno == EINTR)
            return (0);
        get_client_fd_is_set(server);
        if (FD_ISSET(0, &server->readfds)) {
            cli(server);
        }
        client_handler(server);
        new_client(server);
    }
    return (0);
}
