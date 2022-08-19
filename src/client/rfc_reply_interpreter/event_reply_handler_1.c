/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** event_reply_handler_1
*/

#include "client.h"

void event_code_100(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_team_created(json->params[0], json->params[1]
    , json->params[2]);
}

void event_code_101(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_channel_created(json->params[0], json->params[1]
    , json->params[2]);
}

void event_code_102(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 5) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_thread_created(json->params[0], json->params[1]
    , (time_t)(atoi(json->params[2])), json->params[3]
    , json->params[4]);
}

void event_code_103(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 4) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_thread_reply_received(json->params[0], json->params[1]
    , json->params[2], json->params[3]);
}
