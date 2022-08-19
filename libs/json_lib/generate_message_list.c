/*
** EPITECH PROJECT, 2022
** generate_message_list.c
** File description:
** generate_message_list
*/

#include "json_lib.h"

static void loop_print_message(message_t *tmp, FILE *fptr, int i)
{
    char unparsed_id[37];
    char unparsed_user_id[37];

    uuid_unparse_lower(tmp->_uuid, unparsed_id);
    uuid_unparse_lower(tmp->_user_uuid, unparsed_user_id);
    if (!i)
        fprintf(fptr, "[");
    fprintf(fptr,
    "{\"_uuid\":\"%s\",\"_user_uuid\":\"%s\",",
    unparsed_id, unparsed_user_id);
    fprintf(fptr,
    "\"_date\":\"%ld\",\"_content\":\"%s\"}", tmp->_date, tmp->_content);
    if (!tmp->_next) {
        fprintf(fptr, "]");
    } else
        fprintf(fptr, ",");
}

void generate_message_list(message_t *message_list, FILE *fptr)
{
    message_t *tmp = message_list;

    if (!tmp) {
        fprintf(fptr, "[]");
        return;
    }
    for (int i = 0; tmp; tmp = tmp->_next, i++)
        loop_print_message(tmp, fptr, i);
}
