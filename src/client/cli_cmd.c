/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli_cmd 1
*/

#include "client.h"

void cli_cmd_help(client_t *client)
{
    FILE *fd = fopen("src/client/help_cmd.txt", "r");
    char *buffer = NULL;
    size_t size = 0;

    if (fd == NULL) {
        fprintf(stdout, "Error: help file not found\n");
        return;
    }
    while (getline(&buffer, &size, fd) != -1)
        printf("%s", buffer);
    printf("\n");
    free(buffer);
    fclose(fd);
    client->buffer_lock_write = 0;
    client->is_write = false;
}

void cli_cmd_login(client_t *client)
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
    strcpy(client->user_name, cmd[0]);
    char *json = json_message_to_server("login", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    client->is_logged = 1;
    free(cmd);
    free(json);
}

void cli_cmd_logout(client_t *client)
{
    char uuid[37];
    strcpy(client->buffer_write
        , "{\"cmd\":\"logout\",\"nb_params\":\"0\"}\r\n");
    uuid_unparse(client->user_uuid, uuid);
    if (client->is_logged == 1) {
        client_event_logged_out(uuid, client->user_name);
    }
    client->is_write = true;
}

void cli_cmd_user(client_t *client)
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
    char *json = json_message_to_server("user", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_users(client_t *client)
{
    strcpy(client->buffer_write
    , "{\"cmd\":\"users\",\"nb_params\":\"0\"}\r\n");
}
