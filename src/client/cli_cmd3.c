/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli_cmd 1
*/

#include "client.h"

static bool cli_cmd_use_error(client_t *client, char **cmd)
{
    int nb_params = 0;

    for (int i = 0; cmd[i] != NULL; i++)
        nb_params += 1;
    if (nb_params < 1 || nb_params > 3) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return (true);
    }
    return (false);
}

void cli_cmd_use(client_t *client)
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
    if (cli_cmd_use_error(client, cmd)) {
        free(cmd);
        return;
    }
    char *json = json_message_to_server("use", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(json);
    free(cmd);
}

void cli_cmd_create(client_t *client)
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
    char *json = json_message_to_server("create", cmd);
    strcpy(client->buffer_write, json);
    strcpy(client->buffer_write + strlen(client->buffer_write), "\r\n");
    free(cmd);
    free(json);
}

void cli_cmd_list(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    strcpy(client->buffer_write, "{\"cmd\":\"list\",\"nb_params\":\"0\"}\r\n");
}

void cli_cmd_info(client_t *client)
{
    if (!is_valid_cli_cmd(client))
        return;
    strcpy(client->buffer_write, "{\"cmd\":\"info\",\"nb_params\":\"0\"}\r\n");
}
