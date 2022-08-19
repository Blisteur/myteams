/*
** EPITECH PROJECT, 2022
** B_NWP_400_NCY_4_1_myteams_nathan_chiodin
** File description:
** utils.c
*/

#include <time.h>

char *get_date(void)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return asctime(tm);
}
