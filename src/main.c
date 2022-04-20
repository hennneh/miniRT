#include "../inc/minirt.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_mrt	mrt;

	if (argc != 2)
	{
		printf("not exactly one arguemnt\n");
		return (1);
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	input(&mrt, argv[1]);
	return (0);
}
