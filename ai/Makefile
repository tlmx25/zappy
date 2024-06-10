##
## EPITECH PROJECT, 2024
## groundhog
## File description:
## Makefile
##
.PHONY: all clean fclean re
MAKEFLAGS += --silent

NAME = zappy_ai

all: $(NAME)

$(NAME):
	@echo "Making script executable"
	cp main.py $(NAME)
	chmod +x $(NAME)

clean:
	@echo "Cleaning Python cache"
	find . -type f -name "*.pyc" -delete
	find . -type d -name "__pycache__" -delete

fclean: clean
	@echo "Full clean - removing executable"
	rm -f $(NAME)

test_run:
	@ cp tests/main.py tests/zappy_ai_test
	@ chmod +x tests/zappy_ai_test
	@ chmod +x tests/ai_test.sh
	@ ./tests/ai_test.sh

re: fclean all
