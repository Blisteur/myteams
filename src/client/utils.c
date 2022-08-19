/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** utils
*/

#include "client.h"

char **my_str_to_wordarray(char *str, char *delim)
{
    char **tab = NULL;
    char *token = NULL;
    int i = 0;

    if (str == NULL)
        return (NULL);
    token = strtok(str, delim);
    while (token != NULL) {
        tab = realloc(tab, sizeof(char *) * (i + 2));
        tab[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    if (tab != NULL)
        tab[i] = NULL;
    return (tab);
}

static char **remove_negative_space(char **str)
{
    for (int x = 0; str[x] != NULL; x += 1)
        for (int y = 0; str[x][y] != '\0'; y += 1)
            str[x][y] = (str[x][y] == -1) ? ' ' : str[x][y];
    return (str);
}

char **my_str_to_wordarray_with_escape_in_quote(char *str, char delim
, char *escape_old, char escape_new)
{
    bool state = false;

    if (str == NULL)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim) {
            state = (state) ? false : true;
            memmove(str + i, str + i + 1, strlen(str + i));
        }
        if (str[i] == escape_old[0] && state)
            str[i] = escape_new;
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
    if (state)
        return (NULL);
    return (remove_negative_space(my_str_to_wordarray(str, escape_old)));
}

bool is_valid_separator(char *buffer, char separator)
{
    bool state = false;
    bool start = false;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"') {
            state = (state) ? false : true;
            start = true;
        }
        if (buffer[i] == '\n')
            return (true);
        if (!state && buffer[i] == '"' && buffer[i + 1] == '"')
            return (false);
        if (start && !state && buffer[i] != separator && buffer[i] != '"')
            return (false);
    }
    return (true);
}

bool is_valid_syntax(char *buffer)
{
    int i = 0;
    int space = 0;

    for (int count = 0; buffer[count]; count += 1) {
        if (buffer[count] == ' ')
            space += 1;
        if (buffer[count] == '"')
            i += 1;
    }
    if (i % 2 != 0 || (i == 0 && space != 0))
        return (false);
    return (true);
}
