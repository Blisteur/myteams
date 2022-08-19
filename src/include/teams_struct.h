/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** teams_struct
*/

#pragma once

#include <uuid/uuid.h>

typedef struct subscribe_s subscribe_t;
struct subscribe_s {
    uuid_t _uuid;
    subscribe_t *_next;
};

typedef struct user_s user_t;
struct user_s {
    uuid_t _uuid;
    char *_name;
    char *_password;
    subscribe_t *_sub_list;
    user_t *_next;
};

typedef struct message_s message_t;
struct message_s {
    uuid_t _uuid;
    uuid_t _user_uuid;
    time_t _date;
    char *_content;
    message_t *_next;
};

typedef struct thread_s thread_t;
struct thread_s {
    uuid_t _uuid;
    uuid_t _user_uuid;
    time_t _date;
    char *_title;
    char *_content;
    message_t *_msg_list;
    thread_t *_next;
};

typedef struct channel_s channel_t;
struct channel_s {
    uuid_t _uuid;
    char *_name;
    char *_description;
    thread_t *_thread_list;
    channel_t *_next;
};

typedef struct team_s team_t;
struct team_s {
    uuid_t _uuid;
    char *_name;
    char *_description;
    channel_t *_channel_list;
    team_t *_next;
};

typedef struct pvconv_s pvconv_t;
struct pvconv_s {
    uuid_t _uuid;
    uuid_t _user_uuid1;
    uuid_t _user_uuid2;
    message_t *_msg_list;
    pvconv_t *_next;
};

typedef struct database_s database_t;
struct database_s {
    team_t *_team_list;
    user_t *_user_list;
    pvconv_t *_pvconv_list;
};
