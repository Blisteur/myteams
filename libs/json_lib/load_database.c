/*
** EPITECH PROJECT, 2022
** load_database.c
** File description:
** load_database
*/

#include "json_lib.h"

static team_t *load_team_loop(char *buff)
{
    team_t *new = NULL;

    buff = strstr(buff, TEAM_LIST) + strlen(TEAM_LIST);
    while (buff && buff[0] != '\0' && buff[0] != ']') {
        new = load_team(&buff, new);
        if (!new || !strncmp(buff + 1, USER_LIST, strlen(USER_LIST)))
            break;
    }
    return (new);
}

static user_t *load_user_loop(char *buff)
{
    user_t *new = NULL;

    buff = strstr(buff, USER_LIST) + strlen(USER_LIST);
    while (buff && buff[0] != '\0' && buff[0] != ']') {
        new = load_user(&buff, new);
        if (!new)
            break;
    }
    return (new);
}

static pvconv_t *load_pvconv_loop(char *buff)
{
    pvconv_t *new = NULL;

    buff = strstr(buff, PV_LIST) + strlen(PV_LIST);
    while (buff && buff[0] != '\0' && buff[0] != ']') {
        new = load_pvconv(&buff, new);
        if (!new)
            break;
    }
    return (new);
}

database_t *load_database(char *db_path)
{
    char *buff = file_buffer(db_path);
    database_t *new = malloc(sizeof(database_t));

    if (!buff || !new) {
        free(buff);
        return NULL;
    }
    new->_team_list = load_team_loop(buff);
    new->_user_list = load_user_loop(buff);
    new->_pvconv_list = load_pvconv_loop(buff);
    free(buff);
    return (new);
}
