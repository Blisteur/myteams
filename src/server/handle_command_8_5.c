/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** handle_command.c
*/

#include "../include/server.h"

void logout_tkt(linked_client_t *old, linked_client_t *client)
{
    while (old->next != NULL) {
        if (old->next->client_fd == client->client_fd)
            break;
        old = old->next;
    }
}
