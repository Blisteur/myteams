/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

char *json_dynamic_user(char *origin, user_t *u, int n, server_t *srv)
{
    int mul = 3 * n;
    char *example = ",\"param%d\":\"%s\",\"param%d\":\"%s\",\"param%d\":\"%s\"";
    char complete[1024];
    char *final;
    char buffer[37];

    uuid_unparse_lower(u->_uuid, buffer);
    sprintf(complete, example, (mul + 1), buffer, (mul + 2), u->_name,
    (mul + 3), (is_online(buffer, srv) ? "1" : "0"));
    final = realloc(origin, strlen(origin) + strlen(complete) + 1);
    strcat(final, complete);
    return final;
}

void send_json_final(linked_client_t *client)
{
    write(client->client_fd, client->out, strlen(client->out));
    client->writeable = false;
}

void send_spe_json(int client_fd, char *json, linked_client_t *cli)
{
    char *final = malloc(strlen(json) + 3);

    client_fd = client_fd;
    sprintf(final, "%s\r\n", json);
    strcpy(cli->out, final);
    cli->writeable = true;
    free(final);
}

void send_json(int client_fd, char *json, linked_client_t *cli)
{
    char *final = malloc(strlen(json) + 3);

    client_fd = client_fd;
    sprintf(final, "%s\r\n", json);
    strcpy(cli->out, final);
    cli->writeable = true;
    free(json);
    free(final);
}

int is_sub_team(char *team_uuid, user_t *user)
{
    subscribe_t *sub = user->_sub_list;
    char buffer[37];

    if (user->_sub_list == NULL) return 0;
    while (sub != NULL) {
        uuid_unparse_lower(sub->_uuid, buffer);
        if (strcmp(team_uuid, buffer) == 0) return 1;
        sub = sub->_next;
    }
    return 0;
}
