/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli_cmd
*/

#include "server.h"

void cli_cmd_help(server_t *server)
{
    fprintf(stdout, "Available cmd is:\n\
    Exit: for exit server\n\
    Help: for this help message\n\
    Clients: for list of connected clients\n\
    Status: for server status\n");
    server->is_running = true;
}

void cli_cmd_exit(server_t *server)
{
    server->is_running = false;
    fprintf(stdout, "Bye\n");
}

void cli_cmd_clients(server_t *server)
{
    linked_client_t *tmp = server->first_client;
    char ip[INET_ADDRSTRLEN];

    fprintf(stdout, "Connected clients:\n");
    for (; tmp; tmp = tmp->next)
        fprintf(stdout, "Client connected on %d fd with ip:%s and port:%d\n"
        , tmp->client_fd, inet_ntop(AF_INET, &tmp->client_addr.sin_addr, ip
        , INET_ADDRSTRLEN), ntohs(tmp->client_addr.sin_port));
}

void cli_cmd_status(server_t *server)
{
    char ip[INET_ADDRSTRLEN];

    fprintf(stdout, "Server ip is: %s port: %d\n"
    , inet_ntop(AF_INET, &server->server_addr.sin_addr, ip, INET_ADDRSTRLEN)
    , ntohs(server->server_addr.sin_port));
}
