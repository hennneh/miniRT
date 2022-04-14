NAME = miniRT

S = ../src/
P=./
M=$(S)geometry/
U=$(S)setup/

SRC =	$(P)proto.c \
		$(U)rayinit.c \
		$(M)geo_maths.c \
		$(P)main.c

OBJ =	$(P)proto.o \
		$(U)rayinit.o \
		$(M)geo_maths.o \
		$(P)main.o

CC = gcc

LIB = ../../lft/

LIBMLX = ../../mlx/libmlx42.a
# LIBMLX = ./newmlx/libmlx42.a

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) -c -Wall -Werror -Wextra -o $@ $<

$(NAME): $(OBJ)
	make -C ../mlx
	make -C ../lft
	gcc $(SRC) ../lft/libft.a ../mlx/libmlx.a -L /usr/X11/lib -lXext -lX11 -o $(NAME)

clean:
	rm $(OBJ)
	make clean -C ../mlx
	make clean -C ../lft

fclean:
	rm $(OBJ)
	make clean -C ../mlx
	make fclean -C ../lft
	rm -f $(NAME)

re: fclean all

.PHONY : re clean all fclean
