/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** event_reply_handler_1
*/

#include "client.h"

void event_code_200(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    printf("%s\n", json->params[0]);
}

void event_code_201(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 2) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_private_message_received(json->params[0], json->params[1]);
}

void event_code_202(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 2) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    if (client->is_logged == 1
    && strcmp(client->user_name, json->params[1]) == 0)
        uuid_parse(json->params[0], client->user_uuid);
    client_event_logged_in(json->params[0], json->params[1]);
}

void event_code_203(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 2) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_event_logged_out(json->params[0], json->params[1]);
}
