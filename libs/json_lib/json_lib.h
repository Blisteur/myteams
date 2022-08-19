/*
** EPITECH PROJECT, 2022
** json_lib.h
** File description:
** json_lib
*/

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include <alloca.h>
#include "../../src/include/teams_struct.h"

#define MESSAGE_LIST "_messageList\":["
#define THREAD_LIST "_threadList\":["
#define CHANNEL_LIST "_channelList\":["
#define TEAM_LIST "_teamList\":["
#define USER_LIST "_userList\":["
#define PV_LIST "_privateConversationList\":["
#define SUB_LIST "_teamSubscribed\":["

typedef struct receive_json_s {
    char *cmd;
    int nb_params;
    char **params;
} receive_json_t;

char *json_message_to_server(char *, char **);
int count_json_size(char *, char **, int *);
int size_int(int);
receive_json_t *receive_json_to_struct(char *);
void generate_db_json(team_t *, user_t *, pvconv_t *, char *);
database_t *load_database(char *);
char *string_finder_json(char *, char *);
char *file_buffer(char *);
message_t *load_message(char **, message_t *);
pvconv_t *load_pvconv(char **, pvconv_t *);
user_t *load_user(char **, user_t *);
thread_t *load_thread(char **, thread_t *);
channel_t *load_channel(char **, channel_t *);
team_t *load_team(char **, team_t *);
message_t *load_message_loop(char **);
void generate_message_list(message_t *, FILE *);
void generate_thread_list(thread_t *, FILE *);
void generate_channel_list(channel_t *, FILE *);
void generate_team_list(team_t *, FILE *);
