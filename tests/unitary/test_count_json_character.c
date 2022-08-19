/*
** EPITECH PROJECT, 2022
** test_json_message_to_server.c
** File description:
** unitary test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../libs/json_lib/json_lib.h"

int count_json_size(char *cmd, char **params, int *i);

void redirect_all_stdout(void);
TestSuite(json_lib_count, .init = redirect_all_stdout);

Test(json_lib_count, count_size_of_json_format_message1)
{
    char *cmd = "/login";
    char **params = malloc(sizeof(char*) * 2);
    int i = 0;

    params[0] = "Thomas";
    params[1] = NULL;
    cr_assert_geq(count_json_size(cmd, params, &i),
    strlen("{\"cmd\":\"/login\",\"nb_params\":\"1\",\"param1\":\"Thomas\"}"));
    free(params);
}

Test(json_lib_count, count_size_of_json_format_message2)
{
    char *cmd = "/create";
    char **params = malloc(sizeof(char*) * 3);
    int i = 0;

    params[0] = "123";
    params[1] = "456";
    params[2] = NULL;
    cr_assert_geq(count_json_size(cmd, params, &i),
    strlen("{\"cmd\":\"/create\",\"nb_params\":\"2\",\"param1\":\"123\",\"param2\":\"456\"}"));
    free(params);
}
