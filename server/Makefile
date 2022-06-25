##
## EPITECH PROJECT, 2022
## B-YEP-400-NAN-4-1-zappy-emile.ettel
## File description:
## Makefile
##

SRC = 	src/main.c						\
		src/server_loop.c				\
		src/argument_handling.c			\
		src/error_handling.c 			\
		src/inventory.c					\
		src/client_init.c				\
		src/get_client_line.c			\
		src/tick_update.c				\
		src/str_to_strarr.c				\
		src/check_ritual.c 				\
		src/generate_map_ressources.c	\
		src/map_info.c					\
		src/movement.c					\
		src/set_client_team.c			\
		src/toolbox.c					\
		src/gui_protocole/player.c		\
		src/gui_protocole/egg.c			\
		src/gui_protocole/ressource.c	\
		src/connect_gui.c				\
		src/take.c						\
		src/set.c						\
		src/broadcast.c					\
		src/action_look.c				\
		src/inventory_to_string.c		\
		src/lay_egg.c			 		\
		src/elevation.c			 		\
		src/eject.c			 			\
		src/connect_nbr.c			 	\
		src/action_inventory.c

NAME = zappy_server

CC = gcc

CFLAGS = -I ./include
CFLAGS += -Wall -Wextra -g -luuid

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
