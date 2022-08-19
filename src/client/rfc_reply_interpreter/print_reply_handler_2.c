/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** print_reply_handler_1
*/

#include "client.h"

void print_code_221(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 3 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 3)
        client_print_teams(json->params[i], json->params[i + 1]
        , json->params[i + 2]);
}

void print_code_222(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 3 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 3)
        client_print_users(json->params[i], json->params[i + 1]
        , atoi(json->params[i + 2]));
}

void print_code_223(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 3 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 3)
        client_print_teams(json->params[i], json->params[i + 1]
        , json->params[i + 2]);
}

void print_code_224(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 3 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 3)
        client_team_print_channels(json->params[i], json->params[i + 1]
        , json->params[i + 2]);
}

void print_code_225(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 5 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 5)
        client_channel_print_threads(json->params[i], json->params[i + 1]
        , (time_t)(atoi(json->params[i + 2])), json->params[i + 3]
        , json->params[i + 4]);
}
