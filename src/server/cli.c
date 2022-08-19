/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli
*/

#include "server.h"

static cmd_cli get_command_cli(char *cmd)
{
    cmd_cli index = -1;
    index = (strcmp(cmd, "exit\n") == 0) ? EXIT_CLI : index;
    index = (strcmp(cmd, "help\n") == 0) ? HELP_CLI : index;
    index = (strcmp(cmd, "clients\n") == 0) ? CLIENTS_CLI : index;
    index = (strcmp(cmd, "status\n") == 0) ? STATUS_CLI : index;
    return (index);
}

void cli(server_t *server)
{
    cmd_cli tmp = -1;
    int lenght = read(0, server->cli.buffer_cli, BUFFER);

    if (lenght == 0) {
        return;
    }
    server->cli.buffer_cli[lenght] = '\0';
    tmp = get_command_cli(server->cli.buffer_cli);
    if ((int)tmp == -1) {
        printf("Unknown command.\n");
        return;
    }
    server->cli.call_cmd[tmp](server);
}
