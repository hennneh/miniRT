#include "../inc/minirt.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_mrt	mrt;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	if (argc != 2)
		return (1);
	input(&mrt, argv[1]);
	return (0);
}
