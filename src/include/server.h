/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** server
*/

#pragma once

#include "../../libs/myteams/logging_server.h"
#include "../../libs/json_lib/json_lib.h"
#include "teams_struct.h"


#define BUFFER 4096

#include "../../libs/myteams/logging_server.h"

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
#include <signal.h>
#include <stdarg.h>
#include "teams_struct.h"
#include "../../libs/json_lib/json_lib.h"
#include <uuid/uuid.h>

// struct
typedef struct server_s server_t;
typedef struct linked_client_s linked_client_t;

typedef enum cmd {
    HELP_CLI,
    EXIT_CLI,
    CLIENTS_CLI,
    STATUS_CLI,
    PWD_CLI
} cmd_cli;

typedef struct cli_s {
    char buffer_cli[BUFFER + 1];
    void (*call_cmd[5])(server_t *);
} cli_t;

typedef struct linked_client_s {
    int client_fd;
    char buffer[BUFFER + 1];

    char out[BUFFER + 1];
    bool writeable;

    int buffer_lock;
    struct sockaddr_in client_addr;
    socklen_t len;
    int auth;
    char *path;
    struct linked_client_s *next;

    user_t *actual_user;

    team_t *actual_team;
    channel_t *actual_channel;
    thread_t *actual_thread;

} linked_client_t;

typedef struct server_s {
    int server_fd;
    bool is_running;
    cli_t cli;
    struct sockaddr_in server_addr;
    socklen_t len;
    fd_set readfds;
    fd_set writefds;
    int max_fd;
    linked_client_t *first_client;
    team_t *first_team;
    user_t *first_user;
    pvconv_t *first_conv;
} server_t;

//define code
#define CODE_220 "Service ready for new user.\r\n"
#define CODE_403 "{\"cmd\":\"403\",\"nb_params\":\"0\"}\r\n"

//Utils
char *get_date(void);

//create server
server_t *create_server(int port);
void delete_server(server_t *server);

//init server
int init_socket(server_t *server);
int init_bind_and_listen(server_t *server, int port);
int init_listen_fd(server_t *server);
void init_cli(server_t *server);

int teams_server(int port);

void debug_linked_client_list(linked_client_t *list);
linked_client_t *add_client(linked_client_t *list, int server_fd);
linked_client_t *delete_client(linked_client_t *list, linked_client_t *client);
void delete_all_client(linked_client_t *list);

//cli cmd
void cli(server_t *server);
void cli_cmd_help(server_t *server);
void cli_cmd_exit(server_t *server);
void cli_cmd_clients(server_t *server);
void cli_cmd_status(server_t *server);

void client_cmd(linked_client_t *client, server_t *server);
int client_handler_extended(server_t *server, int len, linked_client_t *tmp);

int command_handle(linked_client_t *client, server_t *server);

// Teams linked list getter
channel_t *get_channel(team_t *team, char const *uuid);
thread_t *get_thread(channel_t *channel, char const *uuid);
team_t *get_team(server_t *server, char const *uuid);
user_t *get_user(server_t *server, char const *uuid);
pvconv_t *get_conv(char *uuid_participant, server_t *server, char *sender);

//signal handler
void catch_sigint_and_sigterm(void);
void sig_handler(int signum);

//handler
void send_json(int client_fd, char *json, linked_client_t *cli);
char *get_json(int size, char *code, ...);
int is_online(char *uuid, server_t *srv);
void get_info_thread(thread_t *thread, linked_client_t *cl, server_t *s);
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
void create(linked_client_t *client, server_t *server, receive_json_t *content);
char *default_json(char *cmd, int size, int size_n);
int message_size(pvconv_t *conv);
char *json_dynamic_message(char *origin, message_t *u, int n, server_t *srv);
char *json_dynamic_sub_user(char *origin, user_t *sub, int n, server_t *srv);
void list_all_user(char *team_uuid, server_t *server, linked_client_t *client);
int sub_size(user_t *user);
char *json_dynamic_teams(char *origin, team_t *team, int n);
message_t *create_resp(linked_client_t *client, server_t *server
, receive_json_t *content);
thread_t *create_thread(linked_client_t *client, server_t *server
, receive_json_t *content);
channel_t *create_channel(linked_client_t *client, server_t *server
, receive_json_t *content);
void list_reply(thread_t *thread, server_t *server, linked_client_t *client);
void list_thread(channel_t *channel, server_t *server
, linked_client_t *client);
void list_channels(server_t *server, team_t *team, linked_client_t *client);
void list_teams(server_t *server, linked_client_t *client);
void send_spe_json(int client_fd, char *json, linked_client_t *cli);
int is_sub_team(char *team_uuid, user_t *user);
void broadcast_content(char *content, server_t *server);
void broadcast_sub(char *team_uuid, char *content, server_t *server);
team_t *create_team(linked_client_t *client, server_t *server
, receive_json_t *content);
user_t *create_user(linked_client_t *client, server_t *server
, receive_json_t *content);
int user_size(server_t *srv);
char *json_dynamic_user(char *origin, user_t *u, int n, server_t *srv);
int team_size(server_t *server);
int channel_size(team_t *team);
char *json_dynamic_channel(char *origin, channel_t *channel, int n
, server_t *srv);
int thread_size(channel_t *channel);
char *json_dynamic_thread(char *origin, thread_t  *thread, int n
, server_t *srv);
int message_size_thread(thread_t *conv);
char *json_dynamic_message_re(char *origin, message_t *u, int n
, thread_t *t);
void send_data_to_online_user(server_t *srv, char *uuid, char *content);
void send_json_final(linked_client_t *client);
int teams_server_loop(server_t *server, int port);
void add_size(char *buff, char *t_uuid, int *i, int *stop);
pvconv_t *getter_conv(char *first, char *second, pvconv_t *tmp, char *buffer);
char *json_dynamic_sub_t(char *origin, subscribe_t *sub, int n, server_t *srv);
void logout_tkt(linked_client_t *old, linked_client_t *client);
