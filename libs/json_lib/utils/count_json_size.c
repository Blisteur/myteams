/*
** EPITECH PROJECT, 2022
** count_json_size.c
** File description:
** utils
*/

#include "../json_lib.h"

int count_json_size(char *cmd, char **params, int *i)
{
    int counter = strlen(cmd) + strlen("{\"cmd\":\"\",");

    for (; params[*i]; *i = *i + 1)
        counter += strlen(params[*i]) + strlen("\"param\":\"\",")
        + size_int(*i);
    counter += strlen("\"nb_params\":\"\",}") + size_int(*i) + 1;
    return (counter);
}
