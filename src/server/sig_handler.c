/*
** EPITECH PROJECT, 2022
** B-NWP-400-NCY-4-1-myteams-nathan.chiodin
** File description:
** sig_handler
*/

#include "server.h"
#include "sig_handler_server.h"

void sig_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM) {
        sig_handler_called = true;
    }
}

void catch_sigint_and_sigterm(void)
{
    struct sigaction sig;

    sig.sa_handler = sig_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
    sigaction(SIGTERM, &sig, NULL);
    signal(SIGPIPE, SIG_IGN);
}
