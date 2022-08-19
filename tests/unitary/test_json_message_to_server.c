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
char *json_message_to_server(char *cmd, char **params);

void redirect_all_stdout(void);
TestSuite(json_lib_converter, .init = redirect_all_stdout);

Test(json_lib_converter, convert_a_string_to_json_format1)
{
    char *cmd = "/login";
    char **params = malloc(sizeof(char*) * 2);
    int i = 0;
    char *tmp = NULL;

    params[0] = "Thomas";
    params[1] = NULL;
    tmp = json_message_to_server(cmd, params);
    cr_assert_geq(strcmp(tmp,
    "{\"cmd\":\"/login\",\"nb_params\":\"1\",\"param1\":\"Thomas\"}"), 0);
    free(tmp);
    free(params);
}

Test(json_lib_converter, convert_a_string_to_json_format2)
{
    char *cmd = "/create";
    char **params = malloc(sizeof(char*) * 3);
    int i = 0;
    char *tmp = NULL;

    params[0] = "123";
    params[1] = "456";
    params[2] = NULL;
    tmp = json_message_to_server(cmd, params);
    cr_assert_str_eq(json_message_to_server(cmd, params),
    "{\"cmd\":\"/create\",\"nb_params\":\"2\",\"param1\":\"123\",\"param2\":\"456\"}");
    free(tmp);
    free(params);
}
