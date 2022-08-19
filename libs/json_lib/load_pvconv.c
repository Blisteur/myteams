/*
** EPITECH PROJECT, 2022
** load_pvconv.c
** File description:
** load_pvconv
*/

#include "json_lib.h"

static void free_ptr(char *uuid, char *user1_uuid, char *user2_uuid)
{
    if (uuid)
        free(uuid);
    if (user1_uuid)
        free(user1_uuid);
    if (user2_uuid)
        free(user2_uuid);
}

message_t *load_message_loop(char **buff)
{
    message_t *new = NULL;

    *buff = strstr(*buff, MESSAGE_LIST) + strlen(MESSAGE_LIST);
    while (*buff && *buff[0] != ']' && *buff[0] != '\0') {
        new = load_message(buff, new);
        if (new == NULL)
            break;
    }
    if (*buff[0] == ']')
        *buff += 2;
    return (new);
}

static pvconv_t *set_pvconv_var(pvconv_t *data, char *uuid, char *user1_uuid,
char *user2_uuid)
{
    data->_next = NULL;
    uuid_parse(uuid, data->_uuid);
    uuid_parse(user1_uuid, data->_user_uuid1);
    uuid_parse(user2_uuid, data->_user_uuid2);
    return (data);
}

pvconv_t *load_pvconv(char **buff, pvconv_t *pvconv_list)
{
    pvconv_t *new = malloc(sizeof(pvconv_t));
    pvconv_t *tmp = pvconv_list;
    char *uuid = string_finder_json(*buff, "_uuid");
    char *user1_uuid = string_finder_json(*buff, "_user1_uuid");
    char *user2_uuid = string_finder_json(*buff, "_user2_uuid");

    if (!new || *buff[0] == ']' || !uuid || !user1_uuid || !user2_uuid) {
        if (new)
            free(new);
        free_ptr(uuid, user1_uuid, user2_uuid);
        return (pvconv_list);
    }
    new = set_pvconv_var(new, uuid, user1_uuid, user2_uuid);
    new->_msg_list = load_message_loop(buff);
    free_ptr(uuid, user1_uuid, user2_uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (pvconv_list);
}
