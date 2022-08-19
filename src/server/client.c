/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** client
*/

#include "cmd_pointer.h"

int client_handler_extended(server_t *server, int len, linked_client_t *tmp)
{
    if (FD_ISSET(tmp->client_fd, &server->readfds)) {
        len = read(tmp->client_fd, tmp->buffer_lock + tmp->buffer, BUFFER);
        tmp->buffer[tmp->buffer_lock + len] = '\0';
        if (len == 0) {
            fprintf(stdout, "Client %d disconnected\n", tmp->client_fd);
            FD_CLR(tmp->client_fd, &server->readfds);
            server->first_client = delete_client(server->first_client, tmp);
            return (1);
        }
        if (strstr(tmp->buffer, "\r\n") == NULL) {
            tmp->buffer_lock = tmp->buffer_lock + len;
            return (0);
        }
        fprintf(stdout, "Client: %d send: %s\n", tmp->client_fd, tmp->buffer);
        client_cmd(tmp, server);
        return (1);
    }
    return (0);
}

static void client_cmd_exec_auth(linked_client_t *client
, server_t *server, int i, receive_json_t *content)
{
    if (cmd_array[i].needLogin == 1 && client->actual_user == NULL) {
        write(client->client_fd, CODE_403, strlen(CODE_403));
    }
    cmd_array[i].execute(client, server, content);
}

void client_cmd(linked_client_t *client, server_t *server)
{
    client->buffer_lock = 0;
    receive_json_t *content = receive_json_to_struct(client->buffer);

    for (int i = 0; cmd_array[i].execute != NULL; i ++) {
        if (strcmp(content->cmd, cmd_array[i].cmd) == 0) {
            client_cmd_exec_auth(client, server, i, content);
        }
    }
}
