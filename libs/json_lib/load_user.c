/*
** EPITECH PROJECT, 2022
** load_user.c
** File description:
** load_user
*/

#include "json_lib.h"

static void free_ptr(char *uuid)
{
    if (uuid)
        free(uuid);
}

subscribe_t *load_subscription(char **buff, subscribe_t *sub_list)
{
    subscribe_t *new = malloc(sizeof(subscribe_t));
    subscribe_t *tmp = sub_list;
    char *uuid = string_finder_json(*buff, "_uuid");

    if (!new || *buff[0] == ']' || !uuid) {
        if (new)
            free(new);
        free_ptr(uuid);
        return NULL;
    }
    uuid_parse(uuid, new->_uuid);
    *buff = strstr(*buff, uuid) + strlen(uuid) + 2;
    new->_next = NULL;
    free_ptr(uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (sub_list);
}

subscribe_t *load_sub_loop(char **buff)
{
    subscribe_t *new = NULL;

    *buff = strstr(*buff, SUB_LIST) + strlen(SUB_LIST);
    while (*buff && *buff[0] != ']' && *buff[0] != '\0') {
        new = load_subscription(buff, new);
        if (new == NULL)
            break;
    }
    return (new);
}

static void free_malloced(user_t *new, char *uuid)
{
    if (new)
        free(new);
    free_ptr(uuid);
}

user_t *load_user(char **buff, user_t *user_list)
{
    user_t *new = malloc(sizeof(user_t));
    user_t *tmp = user_list;
    char *uuid = string_finder_json(*buff, "_uuid");

    if (!new || *buff[0] == ']' || !uuid) {
        free_malloced(new, uuid);
        return NULL;
    }
    uuid_parse(uuid, new->_uuid);
    new->_name = string_finder_json(*buff, "_name");
    new->_password = string_finder_json(*buff, "_password");
    new->_sub_list = load_sub_loop(buff);
    new->_next = NULL;
    free_ptr(uuid);
    if (*buff[0] == ']')
        *buff += 2;
    if (!tmp) return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (user_list);
}
