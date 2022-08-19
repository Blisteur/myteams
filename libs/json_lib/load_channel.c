/*
** EPITECH PROJECT, 2022
** load_channel.c
** File description:
** load_channel
*/

#include "json_lib.h"

static void free_ptr(char *uuid)
{
    if (uuid)
        free(uuid);
}

static channel_t *set_channel_var(channel_t *data, char *uuid, char **buff)
{
    uuid_parse(uuid, data->_uuid);
    data->_next = NULL;
    data->_name = string_finder_json(*buff, "_name");
    data->_description = string_finder_json(*buff, "_description");
    return (data);
}

static thread_t *load_thread_loop(char **buff)
{
    thread_t *new = NULL;
    *buff = strstr(*buff, THREAD_LIST) + strlen(THREAD_LIST);
    while (*buff && *buff[0] != '\0' && *buff[0] != ']') {
        if (strstr(*buff, MESSAGE_LIST)
        && ((void*)strstr(*buff, MESSAGE_LIST)
        < (void*)strstr(*buff, CHANNEL_LIST) || !strstr(*buff, CHANNEL_LIST))
        && ((void*)strstr(*buff, MESSAGE_LIST)
        < (void*)strstr(*buff, PV_LIST) || !strstr(*buff, PV_LIST))
        && ((void*)strstr(*buff, MESSAGE_LIST)
        < (void*)strstr(*buff, THREAD_LIST) || !strstr(*buff, THREAD_LIST))
        && ((void*)strstr(*buff, MESSAGE_LIST)
        < (void*)strstr(*buff, USER_LIST) || !strstr(*buff, USER_LIST))) {
            new = load_thread(buff, new);
        } else
            break;
        if (new == NULL) break;
    }
    if (*buff[0] == ']')
        *buff += 2;
    return (new);
}

channel_t *load_channel(char **buff, channel_t *channel_list)
{
    channel_t *new = malloc(sizeof(channel_t));
    channel_t *tmp = channel_list;
    char *uuid = string_finder_json(*buff, "_uuid");

    if (!new || *buff[0] == ']' || !uuid) {
        if (new)
            free(new);
        free_ptr(uuid);
        return (channel_list);
    }
    new = set_channel_var(new, uuid, buff);
    new->_thread_list = load_thread_loop(buff);
    free_ptr(uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (channel_list);
}
