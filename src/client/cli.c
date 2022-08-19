/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** cli
*/

#include "client.h"

bool is_valid_cli_cmd(client_t *client)
{
    if (is_valid_syntax(client->buffer_write) == false) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return (false);
    }
    if (is_valid_separator(client->buffer_write, ' ') == false) {
        fprintf(stdout, "Error: invalid syntax\n");
        client->buffer_lock_write = 0;
        client->is_write = false;
        return (false);
    }
    return (true);
}

static cmd_cli get_command_cli(char *cmd)
{
    cmd_cli index = -1;
    index = (strstr(cmd, "/help") != NULL) ? HELP_CLI : index;
    index = (strstr(cmd, "/login ") != NULL) ? LOGIN_CLI : index;
    index = (strstr(cmd, "/logout") != NULL) ? LOGOUT_CLI : index;
    index = (strstr(cmd, "/users") != NULL) ? USERS_CLI : index;
    index = (strstr(cmd, "/user ") != NULL) ? USER_CLI : index;
    index = (strstr(cmd, "/send ") != NULL) ? SEND_CLI : index;
    index = (strstr(cmd, "/messages ") != NULL) ? MESSAGES_CLI : index;
    index = (strstr(cmd, "/subscribe ") != NULL) ? SUBSCRIBE_CLI : index;
    index = (strstr(cmd, "/subscribed") != NULL) ? SUBSCRIBED_CLI : index;
    index = (strstr(cmd, "/unsubscribe ") != NULL) ? UNSUBSCRIBE_CLI : index;
    index = (strstr(cmd, "/use ") != NULL) ? USE_CLI : index;
    index = (strstr(cmd, "/create ") != NULL) ? CREATE : index;
    index = (strstr(cmd, "/list") != NULL) ? LIST_CLI : index;
    index = (strstr(cmd, "/info") != NULL) ? INFO_CLI : index;
    return (index);
}

static void catch_ctrl_d(client_t *client)
{
    char uuid[37];

    if (client->is_logged == 1) {
        write(client->server_fd
        , "{\"cmd\":\"logout\",\"nb_params\":\"0\"}\r\n", 35);
        uuid_unparse(client->user_uuid, uuid);
        client_event_logged_out(uuid, client->user_name);
    }
    close(client->server_fd);
    client->is_running = false;
}

static void cli_internal(client_t *cli, int lenght, cmd_cli tmp)
{
    strcpy(cli->buffer_write + cli->buffer_lock_write, cli->cli.buffer_cli);
    strcpy(cli->buffer_write + cli->buffer_lock_write
    + lenght + cli->cli.buffer_cli_lock, "\r\n");
    cli->buffer_lock_write += cli->cli.buffer_cli_lock + lenght + 2;
    cli->cli.buffer_cli_lock = 0;
    cli->is_write = true;
    cli->cli.call_cmd[tmp](cli);
}

void cli(client_t *cli)
{
    cmd_cli tmp = -1;
    int lenght = read(0, cli->cli.buffer_cli
    + cli->cli.buffer_cli_lock, BUFFER);
    if (lenght == 0) {
        if (cli->is_write == true)
            return;
        catch_ctrl_d(cli);
        return;
    }
    cli->cli.buffer_cli[lenght + cli->cli.buffer_cli_lock] = '\0';
    if (strstr(cli->cli.buffer_cli, "\n") == NULL) {
        cli->cli.buffer_cli_lock += lenght;
        return;
    }
    tmp = get_command_cli(cli->cli.buffer_cli);
    if ((int)tmp == -1) {
        printf("Unknown command\n");
        return;
    }
    cli_internal(cli, lenght, tmp);
}
