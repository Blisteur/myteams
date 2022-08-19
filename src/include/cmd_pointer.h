/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** command.h
*/

#pragma once
#include "server.h"

// Structure

typedef struct client_cmd_s {
    char *cmd;
    void (*execute) (linked_client_t *client, server_t *server
    , receive_json_t *content);
    int needLogin;
    int argNeeded;
} client_cmd_t ;

//Function

void login (linked_client_t *client, server_t *server
, receive_json_t *content);
void list_users(linked_client_t *client, server_t *server
, receive_json_t *json);

void logout(linked_client_t *client, server_t *server, receive_json_t *json);
void use_command(linked_client_t *client, server_t *server
, receive_json_t *json);
void send_private(linked_client_t *client, server_t *server
, receive_json_t *json);
void get_info(linked_client_t *client, server_t *server, receive_json_t *json);
void get_user_information(linked_client_t *client, server_t *server
, receive_json_t *json);
void get_messages(linked_client_t *client, server_t *server
, receive_json_t *json);
void add_sub(linked_client_t *client, server_t *server, receive_json_t *json);
void list_sub(linked_client_t *client, server_t *server, receive_json_t *json);
void unsub_list(linked_client_t *client, server_t *server
, receive_json_t *json);
void list_cmd(linked_client_t *client, server_t *server, receive_json_t *json);
void create(linked_client_t *client, server_t *server
, receive_json_t *content);

//Pointer Array
const client_cmd_t cmd_array[] = {
    {"login", &login, 0, 1},
    {"users", &list_users, 1, 0},
    {"logout", &logout, 1, 0},
    {"use", &use_command, 1, -1},
    {"send", &send_private, 1, 2},
    {"info", &get_info, 1, 0},
    {"user", &get_user_information, 1, 1},
    {"messages", &get_messages, 1, 1},
    {"subscribe", &add_sub, 1, 1},
    {"subscribed", &list_sub, 1, -1},
    {"unsubscribe", &unsub_list, 1, 1},
    {"create", &create, 1, 1},
    {"list", &list_cmd, 1, 1},

    {"", NULL, 0, 0}
};
