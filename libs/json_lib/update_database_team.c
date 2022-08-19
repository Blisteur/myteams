/*
** EPITECH PROJECT, 2022
** update_database_team.c
** File description:
** update_database_team
*/

#include "json_lib.h"

static void loop_print_thread(thread_t *tmp, FILE *fptr, int i)
{
    char unparsed_id[37];
    char unparsed_user_id[37];

    uuid_unparse_lower(tmp->_uuid, unparsed_id);
    uuid_unparse_lower(tmp->_user_uuid, unparsed_user_id);
    if (!i)
        fprintf(fptr, "[");
    fprintf(fptr,
    "{\"_uuid\":\"%s\",\"_user_uuid\":\"%s\",\"_title\":\"%s\",",
    unparsed_id, unparsed_user_id, tmp->_title);
    fprintf(fptr, "\"_date\":\"%ld\",\"_content\":\"%s\",\"_messageList\":",
    tmp->_date, tmp->_content);
    generate_message_list(tmp->_msg_list, fptr);
    if (!tmp->_next) {
        fprintf(fptr, "}]");
    } else
        fprintf(fptr, "},");
}

void generate_thread_list(thread_t *thread_list, FILE *fptr)
{
    thread_t *tmp = thread_list;

    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++)
        loop_print_thread(tmp, fptr, i);
}

void generate_channel_list(channel_t *channel_list, FILE *fptr)
{
    channel_t *tmp = channel_list;
    char unparsed_id[37];
    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, unparsed_id);
        if (!i)
            fprintf(fptr, "[");
        fprintf(fptr,
        "{\"_uuid\":\"%s\",\"_name\":\"%s\",\"_description\":\"%s\",",
        unparsed_id, tmp->_name, tmp->_description);
        fprintf(fptr, "\"_threadList\":");
        generate_thread_list(tmp->_thread_list, fptr);
        if (!tmp->_next) {
            fprintf(fptr, "}]");
        } else
            fprintf(fptr, "},");
    }
}

void generate_team_list(team_t *team_list, FILE *fptr)
{
    team_t *tmp = team_list;
    char unparsed_id[37];
    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, unparsed_id);
        if (!i)
            fprintf(fptr, "[");
        fprintf(fptr,
        "{\"_uuid\":\"%s\",\"_name\":\"%s\",\"_description\":\"%s\",",
        unparsed_id, tmp->_name, tmp->_description);
        fprintf(fptr, "\"_channelList\":");
        generate_channel_list(tmp->_channel_list, fptr);
        if (!tmp->_next) {
            fprintf(fptr, "}]");
        } else
            fprintf(fptr, "},");
    }
}
