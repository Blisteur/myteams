/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** main
*/

#include "../include/server.h"
#include "sig_handler_server.h"

int help(void)
{
    FILE *fd = fopen("src/server/help.txt", "r");
    char *buffer = NULL;
    size_t size = 0;

    if (fd == NULL) {
        fprintf(stdout, "Error: help file not found\n");
        return (84);
    }
    while (getline(&buffer, &size, fd) != -1)
        printf("%s", buffer);
    printf("\n");
    free(buffer);
    fclose(fd);
    return (0);
}

int main(int argc, char **argv)
{
    sig_handler_called = false;
    if (argc == 1)
        return (help());
    if (argc == 2 && (strcmp(argv[1], "-h") == 0
        || strcmp(argv[1], "--help") == 0
        || strcmp(argv[1], "-help") == 0))
        return (help());
    if (argc != 2) {
        fprintf(stdout, "Error: invalid number of arguments\n");
        return (84);
    }
    return (teams_server(atoi(argv[1])));
}
