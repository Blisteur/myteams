/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

char *default_json(char *cmd, int size, int size_n)
{
    char *pattern = "{\"cmd\":\"%s\",\"nb_params\":\"%d\"";
    char calc[1024];
    char *final;

    sprintf(calc, pattern, cmd, size * size_n);
    final = malloc(strlen(calc) + 1);
    final[0] = '\0';
    strcat(final, calc);
    return final;
}

int is_online(char *uuid, server_t *srv)
{
    linked_client_t *c = srv->first_client;
    char buffer[37];

    if (srv->first_client == NULL) return 0;
    while (c != NULL) {
        if (c->actual_user != NULL)
            uuid_unparse_lower(c->actual_user->_uuid, buffer);
        if (c->actual_user != NULL && strcmp(buffer, uuid) == 0)
            return 1;
        c = c->next;
    }
    return 0;
}

int thread_size(channel_t *channel)
{
    thread_t *thread = channel->_thread_list;
    int i;

    if (channel->_thread_list == NULL) return 0;
    for (i = 0; thread != NULL; i++, thread = thread->_next);
    return (i);
}

int message_size_thread(thread_t *conv)
{
    message_t *message = conv->_msg_list;
    int i;

    if (conv->_msg_list == NULL) return 0;
    for (i = 0; message != NULL; i++, message = message->_next);
    return (i);
}

int message_size(pvconv_t *conv)
{
    message_t *message = conv->_msg_list;
    int i;

    if (conv->_msg_list == NULL) return 0;
    for (i = 0; message != NULL; i++, message = message->_next);
    return (i);
}
