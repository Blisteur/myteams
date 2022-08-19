/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** struct_handler
*/

#include "server.h"

static server_t *load_myteams(server_t *srv)
{
    srv->first_user = NULL;
    srv->first_conv = NULL;
    srv->first_team = NULL;
    return (srv);
}

server_t *create_server(int port)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return (NULL);
    if (init_socket(server) == 84) {
        free(server);
        return (NULL);
    }
    if (init_bind_and_listen(server, port) == 84) {
        close(server->server_fd);
        free(server);
        return (NULL);
    }
    init_listen_fd(server);
    server->first_client = NULL;
    server->len = sizeof(struct sockaddr_in);
    server->is_running = true;
    init_cli(server);
    return (load_myteams(server));
}

void delete_user(server_t *server)
{
    user_t *tmp = server->first_user;
    user_t *old = server->first_user;

    if (server->first_user != NULL) {
        while (tmp != NULL ) {
            old = tmp->_next;
            free(tmp);
            tmp = old;
        }
    }
}

void delete_pv(server_t *server)
{
    pvconv_t *tmp = server->first_conv;
    pvconv_t *old = server->first_conv;

    if (server->first_conv != NULL) {
        while (tmp != NULL ) {
            old = tmp->_next;
            free(tmp);
            tmp = old;
        }
    }
}

void delete_server(server_t *server)
{
    if (server == NULL)
        return;
    delete_all_client(server->first_client);
    delete_user(server);
    delete_pv(server);
    close(server->server_fd);
    free(server);
}
