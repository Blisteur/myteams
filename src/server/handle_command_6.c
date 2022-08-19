/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

user_t *create_user(linked_client_t *client, server_t *server
, receive_json_t *content)
{
    char *user = content->params[0];
    user_t *loop_tmp = server->first_user;
    user_t *tmp = malloc(sizeof(user_t));
    char buffer[37];

    client = client;
    uuid_generate_random(tmp->_uuid);
    tmp->_name = user;
    tmp->_next = NULL;
    tmp->_sub_list = NULL;
    if (server->first_user == NULL) {
        server->first_user = tmp;
    } else {
        while (loop_tmp->_next != NULL) loop_tmp = loop_tmp->_next;
        loop_tmp->_next = tmp;
    }
    uuid_unparse_lower(tmp->_uuid, buffer);
    server_event_user_created(buffer, tmp->_name);
    return tmp;
}

static void log_team(user_t *user, team_t *team, linked_client_t *client
,server_t *server)
{
    char buffer[37];
    char buffer_user[37];

    uuid_unparse_lower(team->_uuid, buffer);
    uuid_unparse_lower(user->_uuid, buffer_user);
    write(client->client_fd, get_json(3, "230", buffer
    , team->_name, team->_description), strlen(get_json(3, "230", buffer
    , team->_name, team->_description)));
    broadcast_content(get_json(3, "100", buffer, team->_name
    , team->_description), server);
    server_event_team_created(buffer, team->_name, buffer_user);
}

team_t *create_team(linked_client_t *client, server_t *server
, receive_json_t *content)
{
    char *team_name = content->params[0];
    char *team_description = content->params[1];
    team_t *loop_tmp = server->first_team;
    team_t *tmp = malloc(sizeof(team_t));

    uuid_generate_random(tmp->_uuid);
    tmp->_name = team_name;
    tmp->_description = team_description;
    tmp->_channel_list = NULL;
    tmp->_next = NULL;
    if (server->first_team == NULL) {
        server->first_team = tmp;
    } else {
        while (loop_tmp->_next != NULL) loop_tmp = loop_tmp->_next;
        loop_tmp->_next = tmp;
    }
    log_team(client->actual_user, tmp, client, server);
    return tmp;
}

static void log_channel(channel_t *channel, team_t *team
, linked_client_t *client, server_t *server)
{
    char buffer[37];
    char buffer_channel[37];

    uuid_unparse_lower(channel->_uuid, buffer_channel);
    uuid_unparse_lower(team->_uuid, buffer);
    write(client->client_fd, get_json(3, "231", buffer_channel
    , channel->_name, channel->_description)
    , strlen(get_json(3, "231", buffer_channel
    , channel->_name, channel->_description)));
    broadcast_sub(buffer, get_json(3, "101", buffer_channel
    , channel->_name, channel->_description), server);
    server_event_channel_created(buffer, buffer_channel, channel->_name);
}

channel_t *create_channel(linked_client_t *client, server_t *server
, receive_json_t *content)
{
    team_t *client_team = client->actual_team;
    channel_t *loop_tmp = client_team->_channel_list;
    channel_t *tmp = malloc(sizeof(channel_t));

    if (client_team == NULL)
        return NULL;
    uuid_generate_random(tmp->_uuid);
    tmp->_name = content->params[0];
    tmp->_description = content->params[1];
    tmp->_thread_list = NULL;
    tmp->_next = NULL;
    if (client_team->_channel_list == NULL) {
        client_team->_channel_list = tmp;
    } else {
        while (loop_tmp->_next != NULL) loop_tmp = loop_tmp->_next;
        loop_tmp->_next = tmp;
    }
    log_channel(tmp, client_team, client, server);
    return (tmp);
}
