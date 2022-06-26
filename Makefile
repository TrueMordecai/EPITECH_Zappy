##
## EPITECH PROJECT, 2022
## B-YEP-410-NAN-4-1-zappy-emile.ettel
## File description:
## Makefile
##

all:
	$(MAKE) -C ./server -f Makefile -s
	$(MAKE) -C ./graphics -f Makefile -s
	cp ./server/zappy_server ./zappy_server
	cp ./graphics/zappy_gui ./zappy_gui
	cp ./client/main.rb ./zappy_ai

clean:
	$(MAKE) -C ./server clean -f Makefile -s
	$(MAKE) -C ./graphics clean -f Makefile -s


fclean:
	$(MAKE) -C ./server fclean -f Makefile -s
	rm -f zappy_server
	$(MAKE) -C ./graphics fclean -f Makefile -s
	rm -f zappy_gui
	rm -f zappy_ai

re: fclean all

.PHONY: all clean fclean re
