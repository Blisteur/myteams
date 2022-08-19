/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/

#include "../json_lib.h"

int count_spaces(char *av)
{
    int count = 1;
    int checker = 1;

    if (av == NULL)
        return (0);
    for (int i = 0; av[i] != '\n' && av[i] != '\r' && av[i] != '\0'; i++) {
        if (av[i] == ' ' && checker == 0) {
            count++;
            checker = 1;
        } else if (av[i] != ' ')
            checker = 0;
    }
    count += 1;
    return (count);
}

char **my_str_to_word_array(char *av)
{
    char *original = NULL;
    int count = count_spaces(av);
    char **str = malloc(sizeof(char*) * count);
    char *tmp = malloc(sizeof(char) * strlen(av) + 1);
    int i = 0;

    strcpy(tmp, av);
    original = strtok(tmp, " ");
    for (; original != NULL; i++) {
        str[i] = original;
        original = strtok(NULL, " ");
    }
    str[i] = NULL;
    return (str);
}
