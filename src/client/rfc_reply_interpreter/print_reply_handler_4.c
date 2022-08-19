/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** print_reply_handler_1
*/

#include "client.h"

void print_code_230(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_team_created(json->params[0], json->params[1]
    , json->params[2]);
    client_event_team_created(json->params[0], json->params[1]
    , json->params[2]);
}

void print_code_231(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_channel_created(json->params[0], json->params[1]
    , json->params[2]);
    client_event_channel_created(json->params[0], json->params[1]
    , json->params[2]);
}

void print_code_232(client_t *client, receive_json_t *json)
{
    char uuid[37];

    if (json->nb_params != 4) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    uuid_unparse(client->user_uuid, uuid);
    client_print_thread_created(json->params[0], uuid
    , (time_t)(atoi(json->params[1])), json->params[2], json->params[3]);
    client_event_thread_created(json->params[0], uuid
    , (time_t)(atoi(json->params[1])), json->params[2], json->params[3]);
}

void print_code_233(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 5) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_reply_created(json->params[0], json->params[1]
    , (time_t)(atoi(json->params[2])), json->params[3]);
    client_event_thread_reply_received(json->params[0], json->params[1]
    , json->params[4], json->params[3]);
}
