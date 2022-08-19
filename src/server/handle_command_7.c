/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

static void log_thread(thread_t *thread, server_t *server
, channel_t *channel, linked_client_t *client)
{
    user_t *user = client->actual_user;
    team_t *team = client->actual_team;
    char buffer[37];
    char buffer_user[37];
    char buffer_channel[37];
    char convert[10];
    char buffer_team[37];
    uuid_unparse_lower(team->_uuid, buffer_team);
    uuid_unparse_lower(channel->_uuid, buffer_channel);
    uuid_unparse_lower(thread->_uuid, buffer);
    uuid_unparse_lower(user->_uuid, buffer_user);
    sprintf(convert, "%ld", thread->_date);
    write(client->client_fd, get_json(4, "232", buffer, convert
    , thread->_title , thread->_content)
    , strlen(get_json(4, "232", buffer, convert
    , thread->_title , thread->_content)));
    broadcast_sub(buffer_team, get_json(5, "102", buffer, buffer_user,convert
    , thread->_title, thread->_content), server);
    server_event_thread_created(buffer_channel, buffer, buffer_user
    , thread->_title, thread->_content);
}

thread_t *create_thread(linked_client_t *client, server_t *server
, receive_json_t *content)
{
    channel_t *client_channel = client->actual_channel;
    thread_t *loop_tmp = client_channel->_thread_list;
    thread_t *tmp = malloc(sizeof(thread_t));

    if (client_channel == NULL) return NULL;
    uuid_generate_random(tmp->_uuid);
    uuid_copy(tmp->_user_uuid, client->actual_user->_uuid);
    tmp->_date = time(NULL);
    tmp->_content = content->params[1];
    tmp->_msg_list = NULL;
    tmp->_title = content->params[0];
    tmp->_next = NULL;
    if (client_channel->_thread_list == NULL) {
        client_channel->_thread_list = tmp;
    } else {
        while (loop_tmp->_next != NULL) loop_tmp = loop_tmp->_next;
        loop_tmp->_next = tmp;
    }
    log_thread(tmp, server, client_channel, client);
    return tmp;
}

static void log_resp(thread_t *thread, linked_client_t *client, message_t *tmp,
server_t *server)
{
    team_t *team = client->actual_team;
    char buffer_team[37];
    char buffer[37];
    char buffer_user[37];
    char convert[10];

    uuid_unparse_lower(thread->_uuid, buffer);
    uuid_unparse_lower(team->_uuid, buffer_team);
    uuid_unparse_lower(client->actual_user->_uuid, buffer_user);
    sprintf(convert, "%ld", thread->_date);
    write(client->client_fd, get_json(5, "233", buffer, buffer_user,
    convert, tmp->_content, buffer_team)
    , strlen(get_json(5, "233", buffer, buffer_user,
    convert, tmp->_content, buffer_team)));
    broadcast_sub(buffer_team, get_json(4, "103", buffer_team, buffer
    , buffer_user, tmp->_content), server);
    server_event_reply_created(buffer, buffer_user, tmp->_content);
}

message_t *create_resp(linked_client_t *client, server_t *server
, receive_json_t *content)
{
    char *msg = content->params[0];
    thread_t *client_thread = client->actual_thread;
    message_t *loop_tmp = client_thread->_msg_list;
    message_t *tmp = malloc(sizeof(message_t));

    uuid_generate_random(tmp->_uuid);
    uuid_copy(tmp->_user_uuid, client->actual_user->_uuid);
    tmp->_date = time(NULL);
    tmp->_content = msg;
    tmp->_next = NULL;
    if (client_thread->_msg_list == NULL) {
        client_thread->_msg_list = tmp;
    } else {
        while (loop_tmp->_next != NULL) loop_tmp = loop_tmp->_next;
        loop_tmp->_next = tmp;
    }
    log_resp(client_thread, client, tmp, server);
    return tmp;
}

void login (linked_client_t *client, server_t *server
, receive_json_t *content)
{
    char *user = content->params[0];
    user_t *tmp = server->first_user;
    char buffer[37];

    while (tmp != NULL) {
        if (strcmp(user, tmp->_name) == 0) {
            break;
        }
        tmp = tmp->_next;
    }
    if (tmp == NULL)
        tmp = create_user(client, server, content);
    uuid_unparse_lower(tmp->_uuid, buffer);
    client->auth = 2;
    client->actual_user = tmp;
    server_event_user_logged_in(buffer);
    broadcast_content(get_json(2, "202", buffer, tmp->_name), server);
}
