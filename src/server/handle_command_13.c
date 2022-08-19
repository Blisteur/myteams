/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** command_handler_12.c
*/

#include "server.h"

void add_size(char *buff, char *t_uuid, int *i, int *stop)
{
    if (strcmp(buff, t_uuid) == 0) {
        (*i)++;
        *stop = 1;
    }
}

pvconv_t *getter_conv(char *first, char *second, pvconv_t *tmp, char *buffer)
{
    if (strcmp(first, buffer) == 0 || strcmp(second, buffer) == 0) {
        return tmp;
    }
    return NULL;
}

char *json_dynamic_sub_t(char *origin, subscribe_t *sub, int n, server_t *srv)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\","
                    "\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];
    char t_buffer[37];
    team_t *team;

    uuid_unparse_lower(sub->_uuid, t_buffer);
    team = get_team(srv, t_buffer);
    uuid_unparse_lower(team->_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), team->_name,
            (mul + 3), team->_description);
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

void list_sub(linked_client_t *client, server_t *server, receive_json_t *json)
{
    char *team_uuid = json->params[0];
    subscribe_t *tmp;
    char *final;

    if (json->nb_params >= 1) {
        if (get_team(server, team_uuid) == NULL) return;
        list_all_user(team_uuid, server, client);
        return;
    } else {
        final = default_json("221", sub_size(client->actual_user), 3);
        tmp = client->actual_user->_sub_list;
        if (client->actual_user->_sub_list == NULL) return;
        for (int i = 0; tmp != NULL; tmp = tmp->_next, i++) {
            final = json_dynamic_sub_t(final, tmp, i, server);
        }
    }
    final = realloc(final, strlen(final) + 2);
    strcat(final, "}");
    send_json(client->client_fd, final, client);
}
