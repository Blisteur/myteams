/*
** EPITECH PROJECT, 2022
** size_int.c
** File description:
** size_int
*/

int size_int(int nb)
{
    int counter = 1;

    for (; nb > 0; nb = nb / 10, counter++);
    return (counter);
}
