/*
** EPITECH PROJECT, 2022
** receive_message.c
** File description:
** fill receive_json_t struct thanks to the client message
*/

#include "json_lib.h"

static receive_json_t *loop_set_struct(char *tmp, char *buffer, char *message,
receive_json_t *new)
{
    for (int i = 0; i < new->nb_params; i++) {
        tmp = malloc(sizeof(char) * strlen("param") + size_int(i) + 1);
        strcpy(tmp, "param");
        sprintf(buffer, "%d", i + 1);
        strcat(tmp, buffer);
        new->params[i] = string_finder_json(message, tmp);
        if (!new->params[i])
            return NULL;
        free(tmp);
    }
    return (new);
}

receive_json_t *receive_json_to_struct(char *message)
{
    receive_json_t *new = malloc(sizeof(receive_json_t));
    char *tmp = NULL;
    char *buffer = malloc(sizeof(char) * 5);
    if (!new)
        return NULL;
    tmp = string_finder_json(message, "nb_params");
    new->cmd = string_finder_json(message, "cmd");
    if (!new->cmd || !tmp)
        return NULL;
    new->nb_params = atoi(tmp);
    free(tmp);
    new->params = malloc(sizeof(char*) * (new->nb_params + 1));
    if (!new->params)
        return NULL;
    new = loop_set_struct(tmp, buffer, message, new);
    if (!new)
        return NULL;
    new->params[new->nb_params] = NULL;
    free(buffer);
    return (new);
}
