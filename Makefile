##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

MAKEFLAGS += -silent

NAME = zappy

all:	$(NAME)

rm_binary:
	@rm -f zappy_server
	@rm -f zappy_ai
	@rm -f zappy_gui

server:
	echo "Building server"
	@make -C server

GUI:
	cd GUI && ./build.sh

ai:
	@make -C ai

$(NAME): server GUI ai
	@cp server/zappy_server .
	@cp ai/zappy_ai .
	@cp GUI/zappy_gui .

clean:
	@make clean -C server
	cd GUI && ./build.sh clean
	@make clean -C ai

fclean: rm_binary
	@make fclean -C server
	cd GUI && ./build.sh fclean
	@make fclean -C ai

re: fclean all

.PHONY: all clean fclean re server GUI ai
