#include "../inc/minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(int argc, char **argv)
{
	if (argc != 2 || \
		!(argv[1][ft_strlen(argv[1]) - 1] == 't') || \
		!(argv[1][ft_strlen(argv[1]) - 2] == 'r') || \
		!(argv[1][ft_strlen(argv[1]) - 3] == '.'))
		return (1);
	int fd;
	fd = open(argv[1], O_RDONLY);
	char	*input = ft_calloc(10000, sizeof(char));
	read(fd, input, 10000);
	if (!input)
		return 1;
	char	**lines = ft_split(input, '\n');
	if (!lines)
		return 2;
	free(input);
	t_mrt	mrt;

	extract_line(lines, &mrt);

	init_rays(&mrt);

	printf("\n");
	// printf("\n");
	// printf("%lf\n", angle(*mrt.pixels[0][wdth/2]->ray, *mrt.pixels[HGHT - 1][wdth/2]->ray));
	//write(1, "all pix\n", 9);

	void	*mlx;
	void	*win;
	t_data	img1;
	t_data	img2;
	// t_data	*img3;
	// t_data	*img4;

	mlx = mlx_init(2 * WDTH + 20, 2 * HGHT + 20, "Beautiful nonsense", 1);
	win = mlx_new_window(mlx, 2 * WDTH + 20, 2 * HGHT + 20, "Beautiful nonsense");
	img1.img = mlx_new_image(mlx, WDTH, HGHT);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel, &img1.line_length, &img1.endian);
	img2.img = mlx_new_image(mlx, WDTH, HGHT);
	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	// img3 = mlx_new_image(mlx, WDTH, HGHT);
	// img4 = mlx_new_image(mlx, WDTH, HGHT);
	for (int y = 0; y < HGHT; y++)
	{
		for (int x = 0; x < WDTH; x++)
		{
			// my_mlx_pixel_put(&img1, x, y, create_trgb(0, veclen(mrt.ray[y][x]), 0, 0));
			my_mlx_pixel_put(&img1, x, y, create_trgb(0, 0, angle(mrt.ray[y][x], mrt.cam->v_o) * (180/PI), 0));
			my_mlx_pixel_put(&img2, x, y, create_trgb(0, 0, 2 * angle(mrt.ray[y][x], mrt.cam->v_o) * (180/PI), 0));
			// mlx_putpixel(img3, l, i, create_trgb(mrt.pixels[i][l]->clr_r, mrt.pixels[i][l]->clr_g, mrt.pixels[i][l]->clr_b, (725 * veclen(mrt.pixels[i][l]->impact))));
			// mlx_putpixel(img4, l, i, create_trgb(mrt.pixels[i][l]->clr_r, mrt.pixels[i][l]->clr_g, mrt.pixels[i][l]->clr_b, mrt.pixels[i][l]->light));
			if ((x == 0 || x == WDTH - 1) && (y == HGHT/2 || y == HGHT/2 + 1))
				printf("%0.1lf ", angle(mrt.ray[y][x], mrt.cam->v_o) * (180/PI));
		}
	}

	mlx_put_image_to_window(mlx, win, img1.img, 5, 10);
	mlx_put_image_to_window(mlx, win, img2.img, 15 + WDTH, 10);
	// mlx_image_to_window(mlx, img3, 5, 15 + HGHT);
	// mlx_image_to_window(mlx, img4, 15 + wdth, 15 + HGHT);

	mlx_loop(mlx);

	// for(int i = 0; i < HGHT; i++)
	// {
	// 	for (int l = 0; l < wdth; l++)
	// 	{
	// 		free(mrt.pixels[i][l]);
	// 	}
	// 	free(mrt.pixels[i]);
	// }
	// free(mrt.pixels);
	// for (int i = 0; lines[i]; i++)
	// {
	// 	if (mrt.element[i])
	// 		free(mrt.element[i]);
	// 	free(lines[i]);
	// }
	// free(lines);
	// close(fd);
	exit(0);
}
