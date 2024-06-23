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
	@mv server/zappy_server .
	@mv ai/zappy_ai .
	@mv GUI/zappy_gui .

clean:
	@make clean -C server
	cd GUI && ./build.sh clean
	@make clean -C ai
	@rm -fr target

fclean: rm_binary
	@make fclean -C server
	cd GUI && ./build.sh fclean
	@make fclean -C ai
	@rm -fr target
	@rm -f functional_tests_server
	@make tests_clean -C server

re: fclean all

tests_run:
	@cargo build --release
	@cp target/release/functional_tests_server .
	@make tests_run -C server

docs:
	@make doc -C server
	@make doc -C ai
	cd GUI && ./build.sh doc

.PHONY: all clean fclean re server GUI ai
