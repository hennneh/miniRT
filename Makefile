NAME = miniRT
CC = gcc
FLAGS = -Wall -Werror -Wextra

SR = ./src/
EX = $(SR)exit/
IN = $(SR)input/
IT = $(IN)init/
UT = $(IN)util/
GE = $(SR)geometry/
TR = $(SR)tracer/

SRC =	$(SR)main.c \
		$(EX)rt_exit.c \
		$(IN)rt_input.c \
		$(IT)ft_init.c \
		$(IT)init_objects.c \
		$(IT)init_scene.c \
		$(UT)rt_count.c \
		$(UT)rt_whtspc.c \
		$(GE)geo_maths.c \
		$(GE)geo_maths1.c \
		$(GE)geo_maths2.c \
		$(GE)ray_plane.c \
		$(GE)ray_cylinder.c \
		$(GE)ray_sphere.c \
		$(TR)rayinit.c \
		$(TR)trace.c \
		$(SR)debug.c \
		$(SR)rearrange.c \
		$(SR)obj_edit.c \
		$(SR)utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) inc/minirt.h
	@make bonus -C lft/
	@make -C mlx/
	$(CC) $(FLAGS) -Lmlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm $(OBJ) mlx/libmlx.a lft/libft.a -o $@

%.o: %.c inc/minirt.h
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
