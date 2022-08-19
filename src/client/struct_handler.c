/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** init_connection
*/

#include "client.h"

static void init_ptr_cli(client_t *client)
{
    client->cli.call_cmd[HELP_CLI] = &cli_cmd_help;
    client->cli.call_cmd[LOGIN_CLI] = &cli_cmd_login;
    client->cli.call_cmd[LOGOUT_CLI] = &cli_cmd_logout;
    client->cli.call_cmd[USERS_CLI] = &cli_cmd_users;
    client->cli.call_cmd[USER_CLI] = &cli_cmd_user;
    client->cli.call_cmd[SEND_CLI] = &cli_cmd_send;
    client->cli.call_cmd[MESSAGES_CLI] = &cli_cmd_messages;
    client->cli.call_cmd[SUBSCRIBE_CLI] = &cli_cmd_subscribe;
    client->cli.call_cmd[SUBSCRIBED_CLI] = &cli_cmd_subscribed;
    client->cli.call_cmd[UNSUBSCRIBE_CLI] = &cli_cmd_unsubscribe;
    client->cli.call_cmd[USE_CLI] = &cli_cmd_use;
    client->cli.call_cmd[CREATE] = &cli_cmd_create;
    client->cli.call_cmd[LIST_CLI] = &cli_cmd_list;
    client->cli.call_cmd[INFO_CLI] = &cli_cmd_info;
}

static int init_socket(client_t *client, char *ip, int port)
{
    client->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->server_fd == -1) {
        fprintf(stdout, "Error: socket creation failed | %s\n"
        , strerror(errno));
        return (84);
    }
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(port);
    client->addr.sin_addr.s_addr = inet_addr(ip);
    return (0);
}

static void init_client(client_t *client)
{
    memset(client->buffer_read, 0, 4096);
    memset(client->buffer_write, 0, 4096);
    client->is_running = true;
    client->buffer_lock_read = 0;
    client->buffer_lock_write = 0;
    client->is_write = false;
    client->is_logged = 0;
    client->user_name[0] = '\0';
    uuid_clear(client->user_uuid);
    FD_ZERO(&client->readfds);
    FD_ZERO(&client->writefds);
    init_ptr_cli(client);
    client->cli.buffer_cli_lock = 0;
}

client_t *creat_client(char *ip, int port)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (NULL);
    init_client(client);
    if (init_socket(client, ip, port) == 84) {
        free(client);
        return (NULL);
    }
    if (connect(client->server_fd
        , (struct sockaddr *)&client->addr, sizeof(client->addr)) == -1) {
        fprintf(stdout, "Error: connection failed | %s\n", strerror(errno));
        free(client);
        return (NULL);
    }
    return (client);
}

void destroy_client(client_t *client)
{
    close(client->server_fd);
    free(client);
}
