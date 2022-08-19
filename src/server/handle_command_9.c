/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

void list_thread(channel_t *channel, server_t *server, linked_client_t *client)
{
    thread_t *tmp = channel->_thread_list;
    char buffer[37];
    char *final;
    char tmps[37];

    uuid_unparse_lower(channel->_uuid, tmps);
    if (channel->_thread_list == NULL) {
        send_json(client->client_fd, get_json(1, "412", tmps), client);
        return;
    }
    final = default_json("225", thread_size(channel),5);
    for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, buffer);
        final = json_dynamic_thread(final, tmp, i, server);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}

void list_reply(thread_t *thread, server_t *server, linked_client_t *client)
{
    message_t *tmp = thread->_msg_list;
    char buffer[37];
    char *final;
    char tmps[37];
    server = server;
    uuid_unparse_lower(thread->_uuid, tmps);
    if (thread->_msg_list == NULL) {
        send_json(client->client_fd, get_json(1, "413", tmps), client);
        return;
    }
    if (thread->_msg_list == NULL) return;
    final = default_json("226", message_size_thread(thread),4);
    for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_user_uuid, buffer);
        final = json_dynamic_message_re(final, tmp, i, thread);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}

void add_msg(char *content, char *user_id, pvconv_t *conv)
{
    message_t *msg = malloc(sizeof(message_t));
    message_t *tmp = conv->_msg_list;

    uuid_generate_random(msg->_uuid);
    uuid_parse(user_id, msg->_user_uuid);
    msg->_date = time(NULL);
    msg->_content = content;
    msg->_next = NULL;
    if (conv->_msg_list == NULL) {
        conv->_msg_list = msg;
    } else {
        while (tmp->_next != NULL) tmp = tmp->_next;
        tmp->_next = msg;
    }
}

pvconv_t *add_conv(char *sender, char *receiver, server_t *server)
{
    pvconv_t *loop = server->first_conv;
    pvconv_t *tmp = malloc(sizeof(pvconv_t));

    uuid_parse(sender, tmp->_user_uuid1);
    uuid_parse(receiver, tmp->_user_uuid2);
    uuid_generate_random(tmp->_uuid);
    tmp->_msg_list = NULL;
    tmp->_next = NULL;
    if (server->first_conv == NULL) {
        server->first_conv = tmp;
    } else {
        while (loop->_next != NULL) loop = loop->_next;
        loop->_next = tmp;
    }
    return tmp;
}

void send_private(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    char *uuid_receive = json->params[0];
    char *content = json->params[1];
    char uuid_sender[37];
    pvconv_t *origin;

    uuid_unparse_lower(client->actual_user->_uuid, uuid_sender);
    if (get_user(server, uuid_receive) == NULL) {
        send_json(client->client_fd, get_json(1, "410", uuid_sender), client);
        return;
    }
    origin = get_conv(uuid_receive, server, uuid_sender);
    if (origin == NULL)
        origin = add_conv(uuid_sender, uuid_receive, server);
    add_msg(content, uuid_sender, origin);
    server_event_private_message_sended(uuid_sender, uuid_receive, content);
    send_json(client->client_fd, get_json(1, "200", "MESSAGE SEND"), client);
    send_data_to_online_user(server, uuid_receive, get_json(2, "201"
    , uuid_sender, content));
}
