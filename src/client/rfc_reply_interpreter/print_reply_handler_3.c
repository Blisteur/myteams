/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** print_reply_handler_1
*/

#include "client.h"

void print_code_226(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 4 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 4)
        client_thread_print_replies(json->params[i], json->params[i + 1]
        , (time_t)(atoi(json->params[i + 2])), json->params[i + 3]);
}

void print_code_227(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_team(json->params[0], json->params[1], json->params[2]);
}

void print_code_228(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_channel(json->params[0], json->params[1], json->params[2]);
}

void print_code_229(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 5) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_thread(json->params[0], json->params[1]
    , (time_t)(atoi(json->params[2])), json->params[3], json->params[4]);
}
