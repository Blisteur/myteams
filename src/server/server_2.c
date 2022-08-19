/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** server
*/

#include "server.h"

static void loop_user(server_t *srv)
{
    user_t *usr = srv->first_user;
    char buffer[37];

    while (usr != NULL) {
        uuid_unparse(usr->_uuid, buffer);
        server_event_user_loaded(buffer, usr->_name);
        usr = usr->_next;
    }
}

int teams_server(int port)
{
    server_t *server = create_server(port);
    if (server == NULL) {
        fprintf(stdout, "Error: server creation failed\n");
        return (84);
    }
    database_t *database = load_database("./storage.json");
    server->first_team = database->_team_list;
    server->first_conv = database->_pvconv_list;
    server->first_user = database->_user_list;
    loop_user(server);
    catch_sigint_and_sigterm();
    teams_server_loop(server, port);
    generate_db_json(server->first_team, server->first_user
    , server->first_conv, "storage.json");
    delete_server(server);
    return (0);
}
