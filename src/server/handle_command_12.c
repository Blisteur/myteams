/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

int sub_size(user_t *user)
{
    subscribe_t *tmp = user->_sub_list;
    int i;

    if (user->_sub_list == NULL) return 0;
    for (i = 0; tmp != NULL; tmp = tmp->_next, i++);
    return i;
}

static void reload_unsub(char *team_uuid, subscribe_t *tmp
, linked_client_t *client)
{
    subscribe_t *tmp_old = client->actual_user->_sub_list;
    char s_buffer[37];

    if (tmp_old->_next == NULL) {
        client->actual_user->_sub_list = NULL;
        return;
    }
    while (tmp_old != NULL) {
        uuid_unparse_lower(tmp_old->_next->_uuid, s_buffer);
        if (strcmp(s_buffer, team_uuid) == 0) {
            tmp_old->_next = tmp->_next;
            free(tmp);
            break;
        }
        tmp_old = tmp_old->_next;
    }
}

void unsub_list(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    char *team_uuid = json->params[0];
    subscribe_t *tmp = client->actual_user->_sub_list;
    char buffer[37];
    int find = 0;
    if (client->actual_user->_sub_list == NULL
    || get_team(server, team_uuid) == NULL) {
        send_json(client->client_fd, get_json(1, "411", team_uuid), client);
        return;
    }
    for (; tmp != NULL; tmp = tmp->_next) {
        uuid_unparse_lower(tmp->_uuid, buffer);
        if (strcmp(team_uuid, buffer) == 0) {
            find = 1;
            break;
        }
    }
    if (find == 0) return;
    server_event_user_unsubscribed(team_uuid, buffer);
    send_json(client->client_fd, get_json(1, "219", team_uuid), client);
    reload_unsub(team_uuid, tmp, client);
}

void create(linked_client_t *client, server_t *server, receive_json_t *content)
{
    if (client->actual_thread != NULL) {
        create_resp(client, server, content);
        return;
    } else if (client->actual_channel != NULL) {
        create_thread(client, server, content);
        return;
    }
    if (client->actual_team != NULL) {
        create_channel(client, server, content);
        return;
    }
    create_team(client, server, content);
    return;
}

void list_cmd(linked_client_t *client, server_t *server, receive_json_t *json)
{
    json = json;
    if (client->actual_thread != NULL) {
        list_reply(client->actual_thread, server, client);
        return;
    }
    if (client->actual_channel != NULL) {
        list_thread(client->actual_channel, server, client);
        return;
    }
    if (client->actual_team != NULL) {
        list_channels(server, client->actual_team, client);
        return;
    }
    list_teams(server, client);
}
