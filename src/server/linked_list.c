/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** linked_list
*/

#include "server.h"

void debug_linked_client_list(linked_client_t *list)
{
    linked_client_t *tmp = list;

    for (; tmp != NULL; tmp = tmp->next) {
        printf("Client call fd %d | next: %p\n", tmp->client_fd, tmp->next);
    }
}

static void client_teams(linked_client_t *client)
{
    client->actual_user = NULL;
    client->actual_team = NULL;
    client->actual_channel = NULL;
    client->actual_thread = NULL;
    client->writeable = false;
}

linked_client_t *add_client(linked_client_t *list, int server_fd)
{
    linked_client_t *client = malloc(sizeof(linked_client_t));

    client->buffer[0] = '\0';
    client->next = list;
    client->buffer_lock = 0;
    client->auth = 0;
    client->actual_user = NULL;
    client->path = getcwd(NULL, 0);
    client->len = sizeof(struct sockaddr_in);
    client->client_fd = accept(server_fd
    , (struct sockaddr *)&client->client_addr, &client->len);
    client_teams(client);
    if (client->client_fd == -1) {
        fprintf(stdout, "Error: incoming client accept fail | %s\n"
        , strerror(errno));
        free(client);
        return (NULL);
    }
    return (client);
}

linked_client_t *delete_client(linked_client_t *list, linked_client_t *client)
{
    linked_client_t *tmp = list;

    if (list == client) {
        list = list->next;
        close(client->client_fd);
        free(client);
        return (list);
    }
    for (; tmp->next != client; tmp = tmp->next);
    tmp->next = client->next;
    close(client->client_fd);
    free(client);
    return (list);
}

void delete_all_client(linked_client_t *list)
{
    linked_client_t *tmp = list;

    while (list != NULL) {
        list = list->next;
        free(tmp);
        tmp = list;
    }
}
