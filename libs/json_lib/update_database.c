/*
** EPITECH PROJECT, 2022
** update_database.c
** File description:
** update the json database filling the information of the linked lists
*/

#include "json_lib.h"

static void generate_subscribed_list(subscribe_t *sub_list, FILE *fptr)
{
    subscribe_t *tmp = sub_list;
    char unparsed_id[37];

    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, unparsed_id);
        if (!i)
            fprintf(fptr, "[");
        fprintf(fptr, "{\"_uuid\":\"%s\"}", unparsed_id);
        if (!tmp->_next) {
            fprintf(fptr, "]");
        } else
            fprintf(fptr, ",");
    }
}

static void generate_user_list(user_t *user_list, FILE *fptr)
{
    user_t *tmp = user_list;
    char unparsed_id[37];

    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++) {
        uuid_unparse_lower(tmp->_uuid, unparsed_id);
        if (!i)
            fprintf(fptr, "[");
        fprintf(fptr, "{\"_uuid\":\"%s\",\"_name\":\"%s\",\"_password\":",
        unparsed_id, tmp->_name);
        fprintf(fptr, "\"%s\",\"_teamSubscribed\":", "none");
        generate_subscribed_list(tmp->_sub_list, fptr);
        if (!tmp->_next) {
            fprintf(fptr, "}]");
        } else
            fprintf(fptr, "},");
    }
}

static void loop_print_pvconv(pvconv_t *tmp, FILE *fptr, int i)
{
    char unparsed_id[37];
    char unparsed_user1_id[37];
    char unparsed_user2_id[37];

    uuid_unparse_lower(tmp->_uuid, unparsed_id);
    uuid_unparse_lower(tmp->_user_uuid1, unparsed_user1_id);
    uuid_unparse_lower(tmp->_user_uuid2, unparsed_user2_id);
    if (!i)
        fprintf(fptr, "[");
    fprintf(fptr,
    "{\"_uuid\":\"%s\",\"_user1_uuid\":\"%s\",\"_user2_uuid\":\"%s\",",
    unparsed_id, unparsed_user1_id, unparsed_user2_id);
    fprintf(fptr, "\"_messageList\":");
    generate_message_list(tmp->_msg_list, fptr);
    if (!tmp->_next) {
        fprintf(fptr, "}]");
    } else
        fprintf(fptr, "},");
}

static void generate_pvconv_list(pvconv_t *pvconv_list, FILE *fptr)
{
    pvconv_t *tmp = pvconv_list;

    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++)
        loop_print_pvconv(tmp, fptr, i);
}

void generate_db_json(team_t *team_list, user_t *user_list,
pvconv_t *pvconv_list, char *db_path)
{
    FILE *fptr = fopen(db_path, "w");

    fprintf(fptr, "{\"_teamList\":");
    generate_team_list(team_list, fptr);
    fprintf(fptr, ",\"_userList\":");
    generate_user_list(user_list, fptr);
    fprintf(fptr, ",\"_privateConversationList\":");
    generate_pvconv_list(pvconv_list, fptr);
    fprintf(fptr, "}");
    fclose(fptr);
}
