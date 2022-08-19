/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

void logout(linked_client_t *client, server_t *server, receive_json_t *json)
{
    linked_client_t *old = server->first_client;
    user_t *user = client->actual_user;
    char buffer[37];
    json = json;
    if (old->client_fd == client->client_fd) {
        server->first_client = client->next;
    } else {
        logout_tkt(old, client);
        old->next = client->next;
    }
    if (client->actual_user != NULL) {
        uuid_unparse_lower(user->_uuid, buffer);
        server_event_user_logged_out(buffer);
        broadcast_content(get_json(2, "203", buffer, user->_name), server);
    }
    shutdown(client->client_fd, SHUT_RDWR);
    free(client);
}

void list_users(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    user_t *display = server->first_user;
    char buff[37];
    int u_size = user_size(server);
    char calc[1024];
    char *pattern = "{\"cmd\":\"%s\",\"nb_params\":\"%d\"";
    char *final;
    json = json;
    sprintf(calc, pattern, "211", u_size * 3);
    final = malloc(strlen(calc) + 1);
    final[0] = '\0';
    strcat(final, calc);
    if (server->first_user == NULL)
        return;
    for (int i = 0; display != NULL; i++, display = display->_next) {
        uuid_unparse_lower(display->_uuid, buff);
        final = json_dynamic_user(final, display, i, server);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}

void use_command(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    client->actual_channel = NULL;
    client->actual_thread = NULL;
    if (json->nb_params >= 1) {
        if ((team = get_team(server, json->params[0])) == NULL)
            return;
        client->actual_team = team;
    }
    if (json->nb_params >= 2) {
        if ((channel = get_channel(team, json->params[1])) == NULL)
            return;
        client->actual_channel = channel;
    }
    if (json->nb_params >= 3) {
        if ((thread = get_thread(channel, json->params[2])) == NULL)
            return;
        client->actual_thread = thread;
    }
}

void list_teams(server_t *server, linked_client_t *client)
{
    team_t *tmp = server->first_team;
    char buffer[37];
    char *final;

    if (server->first_team == NULL) return;
    final = default_json("223", team_size(server), 3);
    for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, buffer);
        final = json_dynamic_teams(final, tmp, i);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}

void list_channels(server_t *server, team_t *team, linked_client_t *client)
{
    channel_t *tmp = team->_channel_list;
    char buffer[37];
    char *final;
    char tmps[37];

    uuid_unparse_lower(team->_uuid, tmps);
    if (team->_channel_list == NULL) {
        send_json(client->client_fd, get_json(1, "411", tmps), client);
        return;
    }
    final = default_json("224", channel_size(team),3);
    for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, buffer);
        final = json_dynamic_channel(final, tmp, i, server);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}
