/*
** EPITECH PROJECT, 2022
** file_buffer.c
** File description:
** file_buffer
*/

#include "../json_lib.h"

char *file_buffer(char *db_path)
{
    FILE *fptr = fopen(db_path, "r");
    struct stat st;
    char *buff = NULL;

    if (!fptr) {
        fptr = fopen(db_path, "w");
        if (!fptr) return NULL;
        fprintf(fptr,
        "{\"_teamList\":[],\"_userList\":[],\"_privateConversationList\":[]}");
        fclose(fptr);
        fptr = fopen(db_path, "r");
        if (!fptr) return NULL;
    }
    stat(db_path, &st);
    buff = malloc(sizeof(char) * st.st_size + 1);
    if (!buff) return NULL;
    fread(buff, st.st_size, 1, fptr);
    buff[st.st_size] = '\0';
    fclose(fptr);
    return (buff);
}
