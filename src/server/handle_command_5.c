/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

void send_data_to_online_user(server_t *srv, char *uuid, char *content)
{
    linked_client_t *c = srv->first_client;
    char buffer[37];

    if (is_online(uuid, srv) == 0) return;
    while (c != NULL) {
        if (c->actual_user == NULL) {
            c = c->next;
            continue;
        }
        uuid_unparse_lower(c->actual_user->_uuid, buffer);
        if (strcmp(buffer, uuid) == 0) {
            send_spe_json(c->client_fd, content, c);
        }
        c = c->next;
    }
}

void broadcast_sub(char *team_uuid, char *content, server_t *server)
{
    user_t *user = server->first_user;
    char buffer[37];

    if (server->first_user == NULL) return;
    while (user != NULL) {
        uuid_unparse_lower(user->_uuid, buffer);
        if (is_sub_team(team_uuid, user)) {
            send_data_to_online_user(server, buffer, content);
        }
        user = user->_next;
    }
    free(content);
}

void broadcast_content(char *content, server_t *server)
{
    linked_client_t *client = server->first_client;

    while (client != NULL) {
        if (client->actual_user != NULL)
            send_spe_json(client->client_fd, content, client);
        client = client->next;
    }
    free(content);
}

static char *get_json_complete(char *code, va_list *list, int size)
{
    char **cmd_array = malloc (sizeof (char *) * (size + 1));
    char *tmp = (char *) va_arg(*list, char *);
    char *new;
    char *json;

    for (int i = 0; i < size; i++, tmp = (char *) va_arg(*list, char *)) {
        new = malloc(strlen(tmp) + 1);
        sprintf(new, "%s", tmp);
        cmd_array[i] = new;
        cmd_array[i + 1] = NULL;
    }
    va_end(*list);
    json = json_message_to_server(code, cmd_array);
    for (int i = 0; i < size; i++)
        free(cmd_array[i]);
    free(cmd_array);
    return (json);
}

char *get_json(int size, char *code, ...)
{
    va_list cmd_list;

    va_start(cmd_list, code);
    return (get_json_complete(code, &cmd_list, size));
}
