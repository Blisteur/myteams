/*
** EPITECH PROJECT, 2022
** load_team.c
** File description:
** load_team
*/

#include "json_lib.h"

static void free_ptr(char *uuid)
{
    if (uuid)
        free(uuid);
}

static channel_t *load_channel_loop(char **buff)
{
    channel_t *new = NULL;

    *buff = strstr(*buff, CHANNEL_LIST) + strlen(CHANNEL_LIST);
    while (*buff && *buff[0] != ']' && *buff[0] != '\0') {
        if (strstr(*buff, THREAD_LIST)
        && ((void*)strstr(*buff, THREAD_LIST) <
        (void*)strstr(*buff, CHANNEL_LIST) || !strstr(*buff, CHANNEL_LIST))) {
            new = load_channel(buff, new);
        } else
            break;
        if (new == NULL)
            break;
    }
    if (*buff[0] == ']')
        *buff += 2;
    return (new);
}

static team_t *set_team_var(team_t *data, char *uuid, char **buff)
{
    data->_next = NULL;
    uuid_parse(uuid, data->_uuid);
    data->_name = string_finder_json(*buff, "_name");
    data->_description = string_finder_json(*buff, "_description");
    data->_channel_list = load_channel_loop(buff);
    return (data);
}

team_t *load_team(char **buff, team_t *team_list)
{
    team_t *new = malloc(sizeof(team_t));
    team_t *tmp = team_list;
    char *uuid = string_finder_json(*buff, "_uuid");

    if (!new || *buff[0] == ']' || !uuid) {
        if (new)
            free(new);
        free_ptr(uuid);
        return (team_list);
    }
    new = set_team_var(new, uuid, buff);
    free_ptr(uuid);
    if (!tmp)
        return (new);
    for (; tmp->_next; tmp = tmp->_next);
    tmp->_next = new;
    return (team_list);
}
