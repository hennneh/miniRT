NAME = miniRT
CC = gcc
FLAGS = -Wall -Werror -Wextra

SR = ./src/
IN = $(SR)input/
IT = $(IN)init/
UT = $(IN)util/

SRC =	$(SR)main.c \
		$(IN)rt_input.c \
		$(IT)ft_init.c \
		$(IT)init_objects.c \
		$(IT)init_scene.c \
		$(UT)rt_count.c \
		$(UT)rt_whtspc.c \
		src/geometry/geo_maths.c \
		src/geometry/geo_maths1.c \
		src/geometry/plane_interception.c \
		src/geometry/ray_sphere.c \
		src/setup/rayinit.c \
		src/tracer/big.c
		src/shadow/shadow.c \
#		src/geometry/ray_cylinder.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C lft/
	@make -C mlx/
	$(CC) $(FLAGS) -Lmlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm $(OBJ) mlx/libmlx.a lft/libft.a -o $@

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C mlx/
	@make clean -C lft/

fclean: clean
	rm -f $(NAME)
	@make fclean -C lft/

re: fclean all

.PHONY: all clean fclean re
