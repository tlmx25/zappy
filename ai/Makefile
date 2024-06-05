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

re: fclean all
