##
## EPITECH PROJECT, 2022
## epitechjam
## File description:
## Makefile
##

NAME = zappy_graphical_user

SRC =	src/main.cpp				\
		src/Player.cpp				\
		src/Drawer.cpp				\
		src/mEntity.cpp

OBJ	=	$(SRC:.cpp=.o)

CC = g++

CPPFLAGS += -std=c++20 -Wextra -Wall -Wreorder -Wshadow
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -g -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g -std=c++11 $(OBJ)

re: fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean 
	$(RM) $(NAME)

.PHONY : all main clean fclean