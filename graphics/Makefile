##
## EPITECH PROJECT, 2022
## epitechjam
## File description:
## Makefile
##

NAME = zappy_gui

SRC =	src/main.cpp				\
		src/Player.cpp				\
		src/Drawer.cpp				\
		src/mEntity.cpp				\
		src/Hud.cpp					\
		src/Cell.cpp				\
		src/Network.cpp				\
		src/Population.cpp			\
		src/Menu.cpp

OBJ	=	$(SRC:.cpp=.o)

CC = g++

CPPFLAGS += -std=c++20 -Wextra -Wall -Wreorder -Wshadow
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -g -std=c++11 $(OBJ) -L/usr/local/lib/

re: fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

.PHONY : all main clean fclean
