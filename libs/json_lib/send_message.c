/*
** EPITECH PROJECT, 2022
** send_message.c
** File description:
** convert the input command to json format to send it to the server
*/

#include "json_lib.h"

static void loop_params_format(char *json_msg, char **params,
int nb_params)
{
    char* buffer = alloca(5000);

    for (int i = 0; i < nb_params; i++) {
        strcat(json_msg, "\"param");
        sprintf(buffer, "%d", i + 1);
        strcat(json_msg, buffer);
        strcat(json_msg, "\":\"");
        strcat(json_msg, params[i]);
        strcat(json_msg, "\"");
        if (i < nb_params - 1)
            strcat(json_msg, ",");
    }
}

char *json_message_to_server(char *cmd, char **params)
{
    int nb_params = 0;
    char *json_msg = malloc(sizeof(char) *
    count_json_size(cmd, params, &nb_params) + 1);
    char* buffer = malloc(sizeof(char) * 5);

    sprintf(buffer, "%d", nb_params);
    strcpy(json_msg, "{\"cmd\":\"");
    strcat(json_msg, cmd);
    strcat(json_msg, "\",\"nb_params\":\"");
    strcat(json_msg, buffer);
    strcat(json_msg, "\",");
    loop_params_format(json_msg, params, nb_params);
    strcat(json_msg, "}");
    free(buffer);
    return (json_msg);
}
