/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

char *json_dynamic_sub_user(char *origin, user_t *sub, int n, server_t *srv)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];

    uuid_unparse_lower(sub->_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), sub->_name,
    (mul + 3), (is_online(buffer, srv) ? "1" : "0"));
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

char *json_dynamic_sub_teams(char *origin, subscribe_t *sub, int n,
server_t *srv)
{
    int mul = 3 * n;
    team_t *team;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];

    uuid_unparse_lower(sub->_uuid, buffer);
    team = get_team(srv, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), team->_name,
    (mul + 3), team->_description);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

char *json_dynamic_teams(char *origin, team_t *team, int n)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\","
                    "\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];

    uuid_unparse_lower(team->_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), team->_name,
    (mul + 3), team->_description);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

char *json_dynamic_message_re(char *origin, message_t *u, int n, thread_t *t)
{
    int mul = 4 * n;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\","
                    "\"param%d\":\"%ld\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char u_buffer[37];
    char buffer[37];

    uuid_unparse_lower(t->_uuid, buffer);
    uuid_unparse_lower(u->_user_uuid, u_buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), u_buffer,
    (mul + 3), u->_date, (mul + 4), u->_content);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

char *json_dynamic_message(char *origin, message_t *u, int n, server_t *srv)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\","
                    "\"param%d\":\"%ld\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];
    srv = srv;
    uuid_unparse_lower(u->_user_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), u->_date,
    (mul + 3), u->_content);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}
