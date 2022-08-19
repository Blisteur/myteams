/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** test_responce_code_client
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "client.h"

//CODE 100
void event_code_100(client_t *client, receive_json_t *json);
void event_code_101(client_t *client, receive_json_t *json);
void event_code_102(client_t *client, receive_json_t *json);
void event_code_103(client_t *client, receive_json_t *json);
//CODE 200
void event_code_200(client_t *client, receive_json_t *json);
void event_code_201(client_t *client, receive_json_t *json);
void event_code_202(client_t *client, receive_json_t *json);
void event_code_203(client_t *client, receive_json_t *json);
void print_code_210(client_t *client, receive_json_t *json);
void print_code_211(client_t *client, receive_json_t *json);
void print_code_212(client_t *client, receive_json_t *json);
void print_code_219(client_t *client, receive_json_t *json);
void print_code_220(client_t *client, receive_json_t *json);
void print_code_221(client_t *client, receive_json_t *json);
void print_code_222(client_t *client, receive_json_t *json);
void print_code_223(client_t *client, receive_json_t *json);
void print_code_224(client_t *client, receive_json_t *json);
void print_code_225(client_t *client, receive_json_t *json);
void print_code_226(client_t *client, receive_json_t *json);
void print_code_227(client_t *client, receive_json_t *json);
void print_code_228(client_t *client, receive_json_t *json);
void print_code_229(client_t *client, receive_json_t *json);
void print_code_230(client_t *client, receive_json_t *json);
void print_code_231(client_t *client, receive_json_t *json);
void print_code_232(client_t *client, receive_json_t *json);
void print_code_233(client_t *client, receive_json_t *json);

//code 300

//code 400
void error_code_401(client_t *client, receive_json_t *json);
void error_code_403(client_t *client, receive_json_t *json);
void error_code_410(client_t *client, receive_json_t *json);
void error_code_411(client_t *client, receive_json_t *json);
void error_code_412(client_t *client, receive_json_t *json);
void error_code_413(client_t *client, receive_json_t *json);
void error_code_414(client_t *client, receive_json_t *json);

void redirect_all_stdout(void);

TestSuite(responce_code_client_error, .init = redirect_all_stdout);


Test(responce_code_client_error, test_reponse_code_100)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("100");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("test");
    json->params[1] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[2] = strdup("description");
    event_code_100(client, json);
    cr_assert_stderr_neq_str("New team created event id test: 04794982-5fea-4477-b50e-c5a0134a9e8e (description)\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_101)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("101");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("test");
    json->params[1] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[2] = strdup("description");
    event_code_101(client, json);
    cr_assert_stderr_neq_str("New channel created event id test: 04794982-5fea-4477-b50e-c5a0134a9e8e (description)\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_102)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("102");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 5);
    json->params[0] = strdup("04794982-5fea-4441-b50e-c5a0134a9e8e");
    json->params[1] = strdup("04794982-5fea-4442-b50e-c5a0134a9e8e");
    json->params[2] = strdup("1555555555");
    json->params[3] = strdup("test");
    json->params[4] = strdup("test");
    event_code_102(client, json);
    cr_assert_stderr_neq_str("New thread created event id 04794982-5fea-4441-b50e-c5a0134a9e8e by (04794982-5fea-4442-b50e-c5a0134a9e8e) at Thu Apr 18 04:45:55 2019: test (test)\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_103)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("103");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 4);
    json->params[0] = strdup("04794982-5fea-8888-b50e-c5a0134a9e8e");
    json->params[1] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[2] = strdup("04794982-5fea-4123-b50e-c5a0134a9e8e");
    json->params[3] = strdup("test");
    event_code_103(client, json);
    cr_assert_stderr_neq_str("New reply from 04794982-5fea-4123-b50e-c5a0134a9e8e in thread 04794982-5fea-4477-b50e-c5a0134a9e8e of team 04794982-5fea-8888-b50e-c5a0134a9e8e: [test]\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_201)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("201");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 2);
    json->params[0] = strdup("04794982-5fea-8888-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    event_code_201(client, json);
    cr_assert_stderr_neq_str("New private message from 04794982-5fea-8888-b50e-c5a0134a9e8e: [test]\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_202)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("202");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 2);
    json->params[0] = strdup("04794982-5fea-8888-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    event_code_202(client, json);
    cr_assert_stderr_neq_str("Client 04794982-5fea-8888-b50e-c5a0134a9e8e logged in with login test\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_203)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("203");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 2);
    json->params[0] = strdup("04794982-5fea-8888-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    event_code_203(client, json);
    cr_assert_stderr_neq_str("Client 04794982-5fea-8888-b50e-c5a0134a9e8e logged out with login test\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_210)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_211)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_212)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_219)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_220)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_221)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_222)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_223)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_224)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_225)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_226)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_227)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_228)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_229)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_230)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_231)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_232)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_233)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("210");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 3);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    json->params[1] = strdup("test");
    json->params[2] = strdup("1");
    print_code_210(client, json);
    cr_assert_stderr_neq_str("User \"test\" (04794982-5fea-4477-b50e-c5a0134a9e8e): 1\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_401)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));
    error_code_401(client, json);
    //cr_assert_stdout_eq_str("Error: 401 | You are not logged in\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_403)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    error_code_403(client, json);
    cr_assert_stderr_eq_str("Unauthorized: action prohibited\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_410)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("410");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 1);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    error_code_410(client, json);
    cr_assert_stderr_neq_str("Unknown user 04794982-5fea-4477-b50e-c5a0134a9e8e\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_411)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("411");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 1);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    error_code_411(client, json);
    cr_assert_stderr_neq_str("Unknown team 04794982-5fea-4477-b50e-c5a0134a9e8e\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_412)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("412");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 1);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    error_code_412(client, json);
    cr_assert_stderr_neq_str("Unknown channel 04794982-5fea-4477-b50e-c5a0134a9e8e\n", "");
    free(client);
    free(json);
}

Test(responce_code_client_error, test_reponse_code_413)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    json->cmd = strdup("413");
    json->nb_params = 0;
    json->params = malloc(sizeof(char *) * 1);
    json->params[0] = strdup("04794982-5fea-4477-b50e-c5a0134a9e8e");
    error_code_413(client, json);
    cr_assert_stderr_neq_str("Unknown thread 04794982-5fea-4477-b50e-c5a0134a9e8e\n", "");
    free(client);
    free(json);
}


Test(responce_code_client_error, test_reponse_code_414)
{
    client_t *client = malloc(sizeof(client_t));
    receive_json_t *json = malloc(sizeof(receive_json_t));

    error_code_414(client, json);
    cr_assert_stderr_eq_str("Already exist: action prohibited\n", "");
    free(client);
    free(json);
}