#include "../inc/minirt.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	double	**scr;
	t_data	img;
	t_mrt	mrt;

	if (argc != 2)
		return (1);
	input(&mrt, argv[1]);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, WDTH, HGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_PIxel, &img.line_length, &img.endian);
	scr = scream(mrt.cam);
	printf("debug1\n");
	for (int y = 0; y < HGHT; y++)
	{
		for (int x = 0; x < WDTH; x++)
		{
			my_mlx_pixel_put(img.img, x, y, nachfolger(x, y, &mrt, scr));
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
