/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** print_reply_handler_1
*/

#include "client.h"

void print_code_210(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params != 3) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    client_print_user(json->params[0], json->params[1], atoi(json->params[2]));
}

void print_code_211(client_t *client, receive_json_t *json)
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

void print_code_212(client_t *client, receive_json_t *json)
{
    client = client;
    if (json->nb_params % 3 != 0) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    for (int i = 0; i < json->nb_params; i += 3)
        client_private_message_print_messages(json->params[i]
        ,(time_t)(atoi(json->params[i + 1])), json->params[i + 2]);
}

void print_code_219(client_t *client, receive_json_t *json)
{
    char uuid[37];

    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    uuid_unparse(client->user_uuid, uuid);
    client_print_unsubscribed(uuid, json->params[0]);
}

void print_code_220(client_t *client, receive_json_t *json)
{
    char uuid[37];

    if (json->nb_params != 1) {
        fprintf(stdout, "Error: invalid syntax server reply\n");
        return;
    }
    uuid_unparse(client->user_uuid, uuid);
    client_print_subscribed(uuid, json->params[0]);
}
