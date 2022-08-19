/*
** EPITECH PROJECT, 2022
** string_finder_json.c
** File description:
** string_finder_json
*/

#include "../json_lib.h"

char *string_finder_json(char *message, char *search)
{
    char *start = strstr(message, search);
    char *find = NULL;
    char *tmp = alloca(255);
    int i = 0;

    if (!start)
        return NULL;
    start = start + strlen(search) + 3;
    for (; start[i] && strncmp(start + i, "\",", 2)
    && strncmp(start + i, "\"}", 2); i++)
        tmp[i] = start[i];
    tmp[i] = '\0';
    find = malloc(sizeof(char) * strlen(tmp) + 1);
    strcpy(find, tmp);
    return (find);
}
