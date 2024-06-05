##
## EPITECH PROJECT, 2022
## lib
## File description:
## Makefile
##

MAKEFLAGS += -silent
CC = gcc

VPATH += src/

SRC += main.c


CFLAGS = -Wall -Wextra -I includes/

LDFLAGS :=

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
	@ echo "$(BLUE)Compilation of $(NAME)...$(NC)"
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@ echo "$(GREEN)$(NAME) created$(NC)"

clean: tests_clean
	rm -rf $(BUILD_DIR)
	rm -f $(OBJ)
	rm -f *~
	rm -f \#*\#
	rm -f vgcore.*
	@ echo "$(RED)clean successful !"

fclean: clean tests_clean
	rm -f $(NAME)
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
