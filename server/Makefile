##
## EPITECH PROJECT, 2022
## B-YEP-400-NAN-4-1-zappy-emile.ettel
## File description:
## Makefile
##

SRC = 	src/main.c					\
		src/server_loop.c			\
		src/argument_handling.c		\
		src/error_handling.c 		\
		src/inventory.c				\
		src/client_init.c			\
		src/get_client_line.c		\
		src/tick_update.c			\
		src/generate_map_ressources.c

NAME = zappy_server

CC = gcc

CFLAGS = -I ./include
CFLAGS += -Wall -Wextra -Werror -g -luuid

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -g -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
