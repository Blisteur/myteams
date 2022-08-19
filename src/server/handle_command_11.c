/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

void log_sub(user_t *user, char *team)
{
    char buffer[37];

    uuid_unparse_lower(user->_uuid, buffer);
    server_event_user_subscribed(team, buffer);
}

void add_sub(linked_client_t *client, server_t *server, receive_json_t *json)
{
    char *team_uuid = json->params[0];
    user_t *actual = client->actual_user;
    subscribe_t *tmp = actual->_sub_list;
    subscribe_t *sub = malloc(sizeof (subscribe_t));
    if (get_team(server, team_uuid) == NULL) {
        send_json(client->client_fd, get_json(1, "411", team_uuid), client);
        free(sub);
        return;
    }
    uuid_parse(team_uuid, sub->_uuid);
    sub->_next = NULL;
    if (actual->_sub_list == NULL) {
        actual->_sub_list = sub;
    } else {
        while (tmp->_next != NULL)
            tmp = tmp->_next;
        tmp->_next = sub;
    }
    log_sub(client->actual_user, team_uuid);
    send_json(client->client_fd, get_json(1, "220", team_uuid), client);
}

int sub_size_user(char *t_uuid, server_t *srv)
{
    user_t *tmp = srv->first_user;
    subscribe_t *_tmp;
    int i;
    char buff[37];
    int stop = 0;

    if (srv->first_user == NULL) return 0;
    for (i = 0; tmp != NULL; tmp = tmp->_next, stop = 0) {
        _tmp = tmp->_sub_list;
        if (tmp->_sub_list == NULL) continue;
        while (_tmp != NULL && stop == 0) {
            uuid_unparse_lower(_tmp->_uuid, buff);
            add_size(buff, t_uuid, &i, &stop);
            _tmp = _tmp->_next;
        }
    }
    return i;
}

char *add_list_user(user_t *u, char **args, server_t *server, int i)
{
    subscribe_t *tmp = u->_sub_list;
    char buff[37];
    char *final = args[0];
    char *team_uuid = args[1];

    uuid_unparse_lower(tmp->_uuid, buff);
    while (tmp != NULL) {
        uuid_unparse_lower(tmp->_uuid, buff);
        if (strcmp(buff, team_uuid) == 0) {
            final = json_dynamic_sub_user(final, u, i, server);
            break;
        }
        tmp = tmp ->_next;
    }
    return final;
}

void list_all_user(char *team_uuid, server_t *server, linked_client_t *client)
{
    user_t *u = server->first_user;
    char *final = default_json("222", sub_size_user(team_uuid, server), 3);
    char **args = malloc(sizeof (char **) * 2);

    for (int i = 0; u != NULL; u = u->_next, i++) {
        if (u->_sub_list == NULL) continue;
        args[0] = final;
        args[1] = team_uuid;
        final = add_list_user(u, args, server, i);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}
