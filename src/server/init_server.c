/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** init_server
*/

#include "server.h"

int init_socket(server_t *server)
{
    int sock = true;
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == -1) {
        fprintf(stdout, "Error: server socket failed | %s\n", strerror(errno));
        return (84);
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR
        , (char *)&sock, sizeof(int)) == -1) {
        fprintf(stdout, "Error: setsockopt failed | %s\n", strerror(errno));
        close(server->server_fd);
        return (84);
    }
    server->max_fd = server->server_fd;
    return (0);
}

int init_bind_and_listen(server_t *server, int port)
{
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server->server_fd, (struct sockaddr *)&server->server_addr,
        sizeof(server->server_addr)) == -1) {
        fprintf(stdout, "Error: bind failed | %s\n", strerror(errno));
        return (84);
    }
    if (listen(server->server_fd, 500) == -1) {
        fprintf(stdout, "Error: listen failed | %s\n", strerror(errno));
        return (84);
    }
    return (0);
}

int init_listen_fd(server_t *server)
{
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(0, &server->readfds);
    FD_SET(server->server_fd, &server->readfds);
    return (0);
}

void init_cli(server_t *server)
{
    server->cli.buffer_cli[0] = '\0';
    server->cli.call_cmd[HELP_CLI] = &cli_cmd_help;
    server->cli.call_cmd[EXIT_CLI] = &cli_cmd_exit;
    server->cli.call_cmd[CLIENTS_CLI] = &cli_cmd_clients;
    server->cli.call_cmd[STATUS_CLI] = &cli_cmd_status;
}
