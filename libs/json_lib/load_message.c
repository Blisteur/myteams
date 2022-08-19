/*
** EPITECH PROJECT, 2022
** load_message.c
** File description:
** load_message
*/

#include "json_lib.h"

static void free_ptr(char *uuid, char *user_uuid)
{
    if (uuid)
        free(uuid);
    if (user_uuid)
        free(user_uuid);
}

static message_t *set_message_var(message_t *data, char *uuid,
char *user_uuid, char **buff)
{
    char *date = string_finder_json(*buff, "_date");

    data->_date = strtol(date, NULL, 10);
    free(date);
    uuid_parse(uuid, data->_uuid);
    uuid_parse(user_uuid, data->_user_uuid);
    data->_content = string_finder_json(*buff, "_content");
    data->_next = NULL;
    return (data);
}

message_t *load_message(char **buff, message_t *message_list)
{
    message_t *new = malloc(sizeof(message_t));
    message_t *tmp = message_list;
    char *uuid = string_finder_json(*buff, "_uuid");
    char *user_uuid = string_finder_json(*buff, "_user_uuid");

    if (!new || *buff[0] == ']' || !uuid || !user_uuid) {
        if (new)
            free(new);
        free_ptr(uuid, user_uuid);
        return (message_list);
    }
    new = set_message_var(new, uuid, user_uuid, buff);
    *buff = strstr(*buff, new->_content) + strlen(new->_content) + 2;
    free_ptr(uuid, user_uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (message_list);
}
