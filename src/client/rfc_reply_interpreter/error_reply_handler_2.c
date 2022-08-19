/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** error_reply_handler_1
*/

#include "client.h"

void error_code_413(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_error_unknown_thread(json->params[0]);
}

void error_code_414(client_t *client, receive_json_t *json)
{
    client = client;
    json = json;
    client_error_already_exist();
}
