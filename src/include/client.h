/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** client
*/

#pragma once

#include "../../libs/myteams/logging_client.h"
#include "../../libs/json_lib/json_lib.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define BUFFER 4096

typedef struct client_s client_t;

typedef enum cmd {
    HELP_CLI,
    LOGIN_CLI,
    LOGOUT_CLI,
    USERS_CLI,
    USER_CLI,
    SEND_CLI,
    MESSAGES_CLI,
    SUBSCRIBE_CLI,
    SUBSCRIBED_CLI,
    UNSUBSCRIBE_CLI,
    USE_CLI,
    CREATE,
    LIST_CLI,
    INFO_CLI
} cmd_cli;

typedef struct cli_s {
    char buffer_cli[BUFFER + 1];
    int buffer_cli_lock;
    void (*call_cmd[14])(client_t *);
} cli_t;

struct client_s {
    int server_fd;
    cli_t cli;
    uuid_t user_uuid;
    int is_logged;
    char user_name[MAX_NAME_LENGTH + 1];
    char buffer_read[BUFFER + 1];
    char buffer_write[BUFFER + 1];
    struct sockaddr_in addr;
    fd_set readfds;
    fd_set writefds;
    bool is_running;
    int buffer_lock_read;
    int buffer_lock_write;
    bool is_write;
};

int client(int port, char *ip);
client_t *creat_client(char *ip, int port);
void destroy_client(client_t *client);
void cli(client_t *client);
void send_msg_to_server(client_t *client);
void receive_msg_from_server(client_t *client);

// CLI
void cli_cmd_help(client_t *client);
void cli_cmd_login(client_t *client);
void cli_cmd_logout(client_t *client);
void cli_cmd_users(client_t *client);
void cli_cmd_user(client_t *client);
void cli_cmd_send(client_t *client);
void cli_cmd_messages(client_t *client);
void cli_cmd_subscribe(client_t *client);
void cli_cmd_subscribed(client_t *client);
void cli_cmd_unsubscribe(client_t *client);
void cli_cmd_use(client_t *client);
void cli_cmd_create(client_t *client);
void cli_cmd_list(client_t *client);
void cli_cmd_info(client_t *client);

//utils
bool is_valid_cli_cmd(client_t *client);
bool is_valid_syntax(char *buffer);
char **str_to_wordarray(char *str, char *delim);
char **my_str_to_wordarray_with_escape_in_quote(char *str, char delim
, char *escape_old, char escape_new);
bool is_valid_separator(char *buffer, char separator);
