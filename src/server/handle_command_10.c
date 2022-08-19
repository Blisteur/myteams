/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

static int get_user_info (linked_client_t *client, server_t *srv)
{
    char buffer[37];

    if (client->actual_team == NULL) {
        uuid_unparse_lower(client->actual_user->_uuid, buffer);
        send_json(client->client_fd, get_json(3, "210", buffer,
        client->actual_user->_name,
        is_online(buffer, srv) ? "1" : "0"),
        client);
        return 1;
    }
    return 0;
}

void get_info_thread(thread_t *thread, linked_client_t *cl, server_t *s)
{
    char buffer[37];
    char user_buffer[37];
    char date_char[10];

    s = s;
    sprintf(date_char, "%ld", thread->_date);
    uuid_unparse_lower(thread->_uuid, buffer);
    uuid_unparse_lower(thread->_user_uuid, user_buffer);
    send_json(cl->client_fd, get_json(5, "229", buffer, user_buffer,
    date_char, thread->_title, thread->_content), cl);
}

void get_info(linked_client_t *client, server_t *server, receive_json_t *json)
{
    char buffer[37];
    json = json;
    if (get_user_info(client, server) == 1) return;
    if (client->actual_thread != NULL) {
        get_info_thread(client->actual_thread, client, server);
        return;
    } else if (client->actual_channel != NULL) {
        uuid_unparse_lower(client->actual_channel->_uuid, buffer);
        send_json(client->client_fd, get_json(3, "228", buffer,
        client->actual_channel->_name,
        client->actual_channel->_description),
        client);
        return;
    } if (client->actual_team != NULL) {
        uuid_unparse_lower(client->actual_team->_uuid, buffer);
        send_json(client->client_fd, get_json(3, "227", buffer,
        client->actual_team->_name,
        client->actual_team->_description),
        client);
    }
}

void get_user_information(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    char *uuid_search = json->params[0];
    user_t *search = get_user(server, uuid_search);
    char buffer[37];

    if (strlen(uuid_search) < 36 || search == NULL) {
        send_json(client->client_fd, get_json(1, "410", uuid_search), client);
        return;
    }
    uuid_unparse_lower(search->_uuid, buffer);
    send_json(client->client_fd
    , get_json(3, "210", buffer, search->_name
    , (is_online(buffer, server) ? "1" : "0")), client);
}

void get_messages(linked_client_t *client, server_t *server
, receive_json_t *json)
{
    char *uuid_receive = json->params[0];
    char uuid_client[37];
    pvconv_t *conv;
    message_t *tmp;
    char *final;

    uuid_unparse_lower(client->actual_user->_uuid, uuid_client);
    conv = get_conv(uuid_receive, server, uuid_client);
    if (conv == NULL || conv->_msg_list == NULL) {
        send_json(client->client_fd, get_json(1, "410", uuid_receive), client);
        return;
    }
    final = default_json("212", message_size(conv),3);
    tmp = conv->_msg_list;
    for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
        final = json_dynamic_message(final, tmp, i, server);
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}
