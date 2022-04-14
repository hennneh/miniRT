NAME = miniRT
CC = gcc
FLAGS = -Wall -Werror -Wextra

SRC = src/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make bonus -C lft/
	make -C mlx/
	$(CC) $(FLAGS) -Lmlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm $(OBJ) mlx/libmlx.a lft/libft.a -o $@

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C mlx/
	make clean -C lft/

fclean: clean
	rm -f $(NAME)
	make fclean -C lft/

re: fclean all

.PHONY: all clean fclean re
