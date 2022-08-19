/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** main
*/

#include "client.h"

int help(void)
{
    FILE *fd = fopen("src/client/help.txt", "r");
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
    if (argc == 2 && (strcmp(argv[1], "-h") == 0
        || strcmp(argv[1], "--help") == 0
        || strcmp(argv[1], "-help") == 0)) {
        return (help());
    }
    if (argc != 3) {
        help();
        return (84);
    }
    return (client(atoi(argv[2]), argv[1]));
}
