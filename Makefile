##
## EPITECH PROJECT, 2022
## B-YEP-410-NAN-4-1-zappy-emile.ettel
## File description:
## Makefile
##

##
## EPITECH PROJECT, 2022
## B-NWP-400-NAN-4-1-myteams-emile.ettel
## File description:
## Makefile
##

all:
	$(MAKE) -C ./server -f Makefile -s
	$(MAKE) -C ./graphics -f Makefile -s
	cp ./server/zappy_server ./zappy_server
	cp ./graphics/zappy_graphical_user ./zappy_graphical_user

clean:
	$(MAKE) -C ./server clean -f Makefile -s
	$(MAKE) -C ./graphics clean -f Makefile -s


fclean:
	$(MAKE) -C ./server fclean -f Makefile -s
	rm -f zappy_server
	$(MAKE) -C ./graphics fclean -f Makefile -s
	rm -f zappy_graphical_user

re: fclean all

.PHONY: all clean fclean re
