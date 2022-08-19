/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

int channel_size(team_t *team)
{
    channel_t *channel = team->_channel_list;
    int i;

    if (team->_channel_list == NULL) return 0;
    for (i = 0; channel != NULL; i++, channel = channel->_next);
    return (i);
}

int team_size(server_t *server)
{
    team_t *team = server->first_team;
    int i;

    if (server->first_team == NULL) return 0;
    for (i = 0; team != NULL; i++, team = team->_next);
    return (i);
}

int user_size(server_t *srv)
{
    user_t *user = srv->first_user;
    int i;

    if (srv->first_user == NULL) return 0;
    for (i = 0; user != NULL; i++, user = user->_next);
    return (i);
}

char *json_dynamic_thread(char *origin, thread_t  *thread, int n, server_t *srv)
{
    int mul = 5 * n;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\","
                    "\"param%d\":\"%ld\",\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];
    char u_buffer[37];
    srv = srv;
    uuid_unparse_lower(thread->_uuid, buffer);
    uuid_unparse_lower(thread->_user_uuid, u_buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), u_buffer,
    (mul + 3), thread->_date, (mul + 4),
    thread->_title, (mul + 5), thread->_content);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

char *json_dynamic_channel(char *origin, channel_t *channel, int n,
server_t *srv)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];
    srv = srv;
    uuid_unparse_lower(channel->_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), channel->_name,
    (mul + 3), channel->_description);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}
