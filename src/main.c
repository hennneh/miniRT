#include "../inc/minirt.h"

int	ft_exit(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	free(img->mlx);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
//	void	*mlx;
//	void	*mlx_win;
	t_data	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1920, 1080, "miniRT");
	mlx_hook(img.win, 17, 0, ft_exit, &img);
	mlx_loop(img.mlx);
	(void) argc;
	(void) argv;
//	input_handler(argc, argv);
	return (0);
}
