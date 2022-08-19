/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** client_reply_code_cmd
*/

#pragma once

#include "client.h"

//ptr sur function

//CODE 100
void event_code_100(client_t *client, receive_json_t *json);
void event_code_101(client_t *client, receive_json_t *json);
void event_code_102(client_t *client, receive_json_t *json);
void event_code_103(client_t *client, receive_json_t *json);
//CODE 200
void event_code_200(client_t *client, receive_json_t *json);
void event_code_201(client_t *client, receive_json_t *json);
void event_code_202(client_t *client, receive_json_t *json);
void event_code_203(client_t *client, receive_json_t *json);
void print_code_210(client_t *client, receive_json_t *json);
void print_code_211(client_t *client, receive_json_t *json);
void print_code_212(client_t *client, receive_json_t *json);
void print_code_219(client_t *client, receive_json_t *json);
void print_code_220(client_t *client, receive_json_t *json);
void print_code_221(client_t *client, receive_json_t *json);
void print_code_222(client_t *client, receive_json_t *json);
void print_code_223(client_t *client, receive_json_t *json);
void print_code_224(client_t *client, receive_json_t *json);
void print_code_225(client_t *client, receive_json_t *json);
void print_code_226(client_t *client, receive_json_t *json);
void print_code_227(client_t *client, receive_json_t *json);
void print_code_228(client_t *client, receive_json_t *json);
void print_code_229(client_t *client, receive_json_t *json);
void print_code_230(client_t *client, receive_json_t *json);
void print_code_231(client_t *client, receive_json_t *json);
void print_code_232(client_t *client, receive_json_t *json);
void print_code_233(client_t *client, receive_json_t *json);

//code 300

//code 400
void error_code_401(client_t *client, receive_json_t *json);
void error_code_403(client_t *client, receive_json_t *json);
void error_code_410(client_t *client, receive_json_t *json);
void error_code_411(client_t *client, receive_json_t *json);
void error_code_412(client_t *client, receive_json_t *json);
void error_code_413(client_t *client, receive_json_t *json);
void error_code_414(client_t *client, receive_json_t *json);

typedef struct client_reply_cmd_s {
    char *reply;
    void (*ptr) (client_t *, receive_json_t *);
} client_reply_cmd_t ;

const client_reply_cmd_t cmd_reply_code_array[] = {
    {"100", &event_code_100},
    {"101", &event_code_101},
    {"102", &event_code_102},
    {"103", &event_code_103},
    {"200", &event_code_200},
    {"201", &event_code_201},
    {"202", &event_code_202},
    {"203", &event_code_203},
    {"210", &print_code_210},
    {"211", &print_code_211},
    {"212", &print_code_212},
    {"219", &print_code_219},
    {"220", &print_code_220},
    {"221", &print_code_221},
    {"222", &print_code_222},
    {"223", &print_code_223},
    {"224", &print_code_224},
    {"225", &print_code_225},
    {"226", &print_code_226},
    {"227", &print_code_227},
    {"228", &print_code_228},
    {"229", &print_code_229},
    {"230", &print_code_230},
    {"231", &print_code_231},
    {"232", &print_code_232},
    {"233", &print_code_233},
    {"401", &error_code_401},
    {"403", &error_code_403},
    {"410", &error_code_410},
    {"411", &error_code_411},
    {"412", &error_code_412},
    {"413", &error_code_413},
    {"414", &error_code_414},
    {"", NULL}
};
