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
	cp main.py $(NAME)
	chmod +x $(NAME)

clean:
	find . -type f -name "*.pyc" -delete
	find . -type d -name "__pycache__" -delete

fclean: clean
	rm -f $(NAME)

test_run:
	@ cp tests/main.py tests/zappy_ai_test
	@ chmod +x tests/zappy_ai_test
	@ chmod +x tests/ai_test.sh
	@ ./tests/ai_test.sh
	@ rm tests/zappy_ai_test
	@ make fclean

re: fclean all
