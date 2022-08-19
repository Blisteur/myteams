/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** receive
*/

#include "client.h"
#include "client_reply_code_cmd.h"

static void get_msg_from_server(client_t *client)
{
    receive_json_t *json = receive_json_to_struct(client->buffer_read);
    if (json == NULL)
        return;
    for (int i = 0; cmd_reply_code_array[i].ptr != NULL; i ++) {
        if (strcmp(cmd_reply_code_array[i].reply, json->cmd) == 0) {
            cmd_reply_code_array[i].ptr(client, json);
            break;
        }
    }
    free(json);
}

void receive_msg_from_server(client_t *client)
{
    int len = 0;

    len = read(client->server_fd
        , client->buffer_read + client->buffer_lock_read, BUFFER);
    client->buffer_read[client->buffer_lock_read + len] = '\0';
    if (len == 0) {
        client->is_running = false;
        return;
    }
    if (strstr(client->buffer_read, "\r\n") == NULL) {
        client->buffer_lock_read = client->buffer_lock_read + len;
        return;
    }
    client->buffer_lock_read = 0;
    get_msg_from_server(client);
}
