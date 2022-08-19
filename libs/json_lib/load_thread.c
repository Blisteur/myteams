/*
** EPITECH PROJECT, 2022
** load_thread.c
** File description:
** load_thread
*/

#include "json_lib.h"

static void free_ptr(char *uuid, char *user_uuid)
{
    if (uuid)
        free(uuid);
    if (user_uuid)
        free(user_uuid);
}

static thread_t *set_thread_var(thread_t *data, char *uuid, char *user_uuid,
char **buff)
{
    char *date = string_finder_json(*buff, "_date");
    data->_date = strtol(date, NULL, 10);
    free(date);
    data->_next = NULL;
    uuid_parse(uuid, data->_uuid);
    uuid_parse(user_uuid, data->_user_uuid);
    data->_title = string_finder_json(*buff, "_title");
    data->_content = string_finder_json(*buff, "_content");
    if (!strstr(*buff, MESSAGE_LIST)
    || ((void*)strstr(*buff, MESSAGE_LIST)
    > (void*)strstr(*buff, USER_LIST) && strstr(*buff, USER_LIST))
    || ((void*)strstr(*buff, MESSAGE_LIST)
    > (void*)strstr(*buff, THREAD_LIST) && strstr(*buff, THREAD_LIST))
    || ((void*)strstr(*buff, MESSAGE_LIST)
    > (void*)strstr(*buff, CHANNEL_LIST) && strstr(*buff, CHANNEL_LIST))
    || (strstr(*buff, MESSAGE_LIST) + strlen(MESSAGE_LIST))[0] == ']') {
        free(data);
        return (NULL);
    }
    return (data);
}

thread_t *load_thread(char **buff, thread_t *thread_list)
{
    thread_t *new = malloc(sizeof(thread_t));
    thread_t *tmp = thread_list;
    char *uuid = string_finder_json(*buff, "_uuid");
    char *user_uuid = string_finder_json(*buff, "_user_uuid");

    if (!new || *buff[0] == ']' || !uuid || !user_uuid) {
        if (new)
            free(new);
        free_ptr(uuid, user_uuid);
        return (thread_list);
    }
    new = set_thread_var(new, uuid, user_uuid, buff);
    if (new)
        new->_msg_list = load_message_loop(buff);
    free_ptr(uuid, user_uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (thread_list);
}
