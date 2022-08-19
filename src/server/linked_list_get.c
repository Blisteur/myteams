/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** linked_list_get.c
*/

#include "server.h"

user_t *get_user(server_t *server, char const *uuid)
{
    user_t *tmp = server->first_user;
    char uuid_buffer[37];

    if (server->first_user == NULL) return NULL;
    while (tmp != NULL) {
        uuid_unparse_lower(tmp->_uuid, uuid_buffer);
        if (strcmp(uuid_buffer, uuid) == 0) return tmp;
        tmp = tmp->_next;
    }
    return NULL;
}

pvconv_t *get_conv(char *uuid_participant, server_t *server
, char *other_participant)
{
    pvconv_t *tmp = server->first_conv;
    pvconv_t *render = NULL;

    if (server->first_conv == NULL) return NULL;
    while (tmp != NULL && render == NULL) {
        char buffer[37];
        uuid_unparse_lower(tmp->_user_uuid1, buffer);
        if (strcmp(uuid_participant, buffer) == 0
        || strcmp(other_participant, buffer) == 0) {
            uuid_unparse_lower(tmp->_user_uuid2, buffer);
            render = getter_conv(uuid_participant, other_participant, tmp,
            buffer);
        }
        tmp = tmp->_next;
    }
    return render;
}

team_t *get_team(server_t *server, char const *uuid)
{
    team_t *tmp = server->first_team;
    char uuid_buffer[37];

    if (server->first_team == NULL) return NULL;
    while (tmp != NULL) {
        uuid_unparse_lower(tmp->_uuid, uuid_buffer);
        if (strcmp(uuid_buffer, uuid) == 0) return tmp;
        tmp = tmp->_next;
    }
    return NULL;
}

channel_t *get_channel( team_t *team, char const *uuid)
{
    channel_t *tmp = team->_channel_list;
    char uuid_buffer[37];

    if (team->_channel_list == NULL) return NULL;
    while (tmp != NULL) {
        uuid_unparse_lower(tmp->_uuid, uuid_buffer);
        if (strcmp(uuid_buffer, uuid) == 0) return tmp;
        tmp = tmp->_next;
    }
    return NULL;
}

thread_t *get_thread(channel_t *channel, char const *uuid)
{
    thread_t *tmp = channel->_thread_list;
    char uuid_buffer[37];

    if (channel->_thread_list == NULL) return NULL;
    while (tmp != NULL) {
        uuid_unparse_lower(tmp->_uuid, uuid_buffer);
        if (strcmp(uuid_buffer, uuid) == 0) return tmp;
        tmp = tmp->_next;
    }
    return NULL;
}
