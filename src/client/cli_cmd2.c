/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli_cmd 1
*/

#include "client.h"

void cli_cmd_send(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    char **cmd = my_str_to_wordarray_with_escape_in_quote(
        strstr(client->buffer_write, " "), '"', " ", -1);
    if (cmd == NULL) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return;
    }
    char *json = json_message_to_server("send", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_messages(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    char **cmd = my_str_to_wordarray_with_escape_in_quote(
        strstr(client->buffer_write, " "), '"', " ", -1);
    if (cmd == NULL) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return;
    }
    char *json = json_message_to_server("messages", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_subscribe(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    char **cmd = my_str_to_wordarray_with_escape_in_quote(
        strstr(client->buffer_write, " "), '"', " ", -1);
    if (cmd == NULL) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return;
    }
    char *json = json_message_to_server("subscribe", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_subscribed(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    char **cmd = my_str_to_wordarray_with_escape_in_quote(
        strstr(client->buffer_write, " "), '"', " ", -1);
    if (cmd == NULL) {
        strcpy(client->buffer_write
        , "{\"cmd\":\"subscribed\",\"nb_params\":\"0\"}\r\n");
        return;
    }
    char *json = json_message_to_server("subscribed", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_unsubscribe(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    char **cmd = my_str_to_wordarray_with_escape_in_quote(
        strstr(client->buffer_write, " "), '"', " ", -1);
    if (cmd == NULL) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return;
    }
    char *json = json_message_to_server("unsubscribe", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}
