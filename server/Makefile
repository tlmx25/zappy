##
## EPITECH PROJECT, 2022
## lib
## File description:
## Makefile
##

MAKEFLAGS += -silent
CC = gcc

VPATH += src/
VPATH += src/network/
VPATH += src/utils/
VPATH += src/option/
VPATH += src/client/
VPATH += src/client/AI
VPATH += src/client/graphic_pending/
VPATH += src/server/
VPATH += src/server/utils
VPATH += src/server/manager
VPATH += src/client/classic/
VPATH += src/client/graphic/
VPATH += src/game/
VPATH += src/game/eggs
VPATH += src/game/AI_commands
VPATH += src/game/initialization
VPATH += src/game/graphic_cmd/

SRC += main.c
SRC += management_socket.c
SRC += read_write_socket.c
SRC += create_client.c
SRC += delete_client.c
SRC += get_client.c
SRC += create_server.c
SRC += delete_server.c
SRC += option.c
SRC += delete_option.c
SRC += parse_port.c
SRC += parse_width_height.c
SRC += parse_name.c
SRC += parse_client_nb.c
SRC += parse_freq.c
SRC += server.c
SRC += manage_server.c
SRC += manager_pending.c
SRC += check_team.c
SRC += create_client_ai.c
SRC += delete_client_ai.c
SRC += read_write_pending_graphic.c
SRC += read_write_ai_client.c
SRC += exec_graphic.c
SRC += exec_pending.c
SRC += exec_ai.c
SRC += debug_print.c
SRC += debug_option.c
SRC += init_game.c
SRC += create_eggs.c
SRC += delete_eggs.c
SRC += get_eggs.c
SRC += init_team.c
SRC += init_world.c
SRC += sending.c
SRC += map_cmd.c
SRC += player_cmd.c
SRC += team_cmd.c
SRC += time_cmd.c
SRC += position.c
SRC += time_utils.c
SRC += right_left_forward_command.c
SRC += connect_nbr_command.c
SRC += inventory_command.c
SRC += fork_command.c
SRC += look_command.c

CFLAGS = -Wall -Wextra -I includes/

LDFLAGS += -L ./libs/ -lmy

BUILD_DIR = build/

NAME = zappy_server

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

$(BUILD_DIR)%.o: %.c
	@mkdir -p $(@D)
	#@echo "  CC       $<      $@"
	#@echo "$(notdir $(CURDIR)): C '$<'"
	@$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(SRC:%.c=$(BUILD_DIR)%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C libs/my
	@ echo "$(BLUE)Compilation of $(NAME)...$(NC)"
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@ echo "$(GREEN)$(NAME) created$(NC)"

clean: tests_clean
	rm -rf $(BUILD_DIR)
	rm -f $(OBJ)
	rm -f *~
	rm -f \#*\#
	rm -f vgcore.*
	@ make clean -C libs/my
	@ echo "$(RED)clean successful !"

fclean: clean tests_clean
	rm -f $(NAME)
	make fclean -C libs/my
	@ echo "$(RED)fclean successful !$(NC)"

CFLAGSTEST += -lcriterion --coverage

tests_run:
	$(CC) -o unit_tests $(filter-out build/main.o, $(SRCT))\
 	tests/tests.cpp -I include/ $(LDFLAGS) $(CFLAGS) $(CFLAGSTEST)
	-./unit_tests

tests_clean:
	@ rm -f *.gcno
	@ rm -f *.gcda
	@ rm -f unit_tests


re: 	fclean all

.PHONY: all clean fclean re .SILENT

BLUE = \033[1;34m
RED = \033[1;31m
GREEN = \033[1;32m
NC = \033[0m
