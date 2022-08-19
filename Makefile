##
## EPITECH PROJECT, 2022
## B-NWP-400-NCY-4-1-myteams-nathan.chiodin
## File description:
## Makefile
##

CFLAGS = -Wall -Wextra -I src/include/ -g

LDFLAGS = -L libs/myteams -lmyteams -luuid

CC = gcc

SRC_SERVER	=	$(wildcard src/server/*.c) \
				$(wildcard libs/json_lib/utils/*.c) \
				$(wildcard libs/json_lib/*.c)

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

NAME_SERVEUR	=	myteams_server

SRC_CLIENT	=	$(wildcard src/client/*.c) \
				$(wildcard src/client/rfc_reply_interpreter/*.c) \
				$(wildcard libs/json_lib/utils/*.c) \
				$(wildcard libs/json_lib/*.c)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_CLIENT	= 	myteams_cli

all: $(NAME_SERVEUR) $(NAME_CLIENT)

$(NAME_SERVEUR):        $(OBJ_SERVER)
		$(CC) -o $(NAME_SERVEUR) $(OBJ_SERVER) $(LDFLAGS)

$(NAME_CLIENT):        $(OBJ_CLIENT)
		$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)

debug: CFLAGS += -g

debug:  $(NAME_SERVEUR)	$(NAME_CLIENT)

final_test: CFLAGS += -Werror -g

final_test: $(NAME_SERVEUR)	$(NAME_CLIENT)

clean:
		find -name "*.o" -delete
		find -name "vgcore.*" -delete
		find -name "*.gcda" -delete
		find -name "*.gcno" -delete
		find -name "*.gcov" -delete
		find -name "tests_run" -delete

fclean: clean
		rm -f $(NAME_SERVEUR) $(NAME_CLIENT)

tests_run: LDFLAGS += -I src/include/ -lcriterion --coverage

SRC_TEST	=	$(filter-out src/client/main.c, $(SRC_CLIENT)) \
				$(wildcard tests/unitary/*.c)

tests_run: $(SRC_TEST)
		$(CC) -o tests_run $(SRC_TEST) $(LDFLAGS)
		LD_LIBRARY_PATH=libs/myteams/ ./tests_run
		./tests/unitary/test.sh

re: fclean all

re_debug: fclean debug

.PHONY: all debug final_test clean fclean re re_debug
