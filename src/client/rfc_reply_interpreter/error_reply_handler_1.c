/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** error_reply_handler_1
*/

#include "client.h"

void error_code_401(client_t *client, receive_json_t *json)
{
    fprintf(stdout, "Error: 401 | You are not logged in\n");
    client->is_running = false;
    json = json;
}

void error_code_403(client_t *client, receive_json_t *json)
{
    client = client;
    json = json;
    client_error_unauthorized();
}

void error_code_410(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_error_unknown_user(json->params[0]);
}

void error_code_411(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_error_unknown_team(json->params[0]);
}

void error_code_412(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_error_unknown_channel(json->params[0]);
}
