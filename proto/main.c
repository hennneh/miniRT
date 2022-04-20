#include "../inc/minirt.h"

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
	// printf("%lf\n", angle(*mrt.pixels[0][WDTH/2]->ray, *mrt.pixels[HGHT - 1][WDTH/2]->ray));
	//write(1, "all pix\n", 9);

	void	*mlx;
	void	*win;
	t_data	img1;
	t_data	img2;
	t_data	img3;
	// t_data	*img4;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 2 * WDTH + 20, 2 * HGHT + 20, "Beautiful nonsense");
	img1.img = mlx_new_image(mlx, WDTH, HGHT);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel, &img1.line_length, &img1.endian);
	img2.img = mlx_new_image(mlx, WDTH, HGHT);
	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	img3.img = mlx_new_image(mlx, WDTH, HGHT);
	img3.addr = mlx_get_data_addr(img3.img, &img3.bits_per_pixel, &img3.line_length, &img3.endian);
	// img4 = mlx_new_image(mlx, WDTH, HGHT);
	//	printf("central ray: x: %lf\ty: %lf\tz: %lf\n angle to cam_dir, %lf\n", mrt.ray[HGHT / 2][WDTH / 2][0], mrt.ray[HGHT / 2][WDTH / 2][1], mrt.ray[HGHT / 2][WDTH / 2][2], angle(mrt.ray[HGHT / 2][WDTH / 2], mrt.cam->v_o) * (180/pi));
	for (int y = 0; y < HGHT; y++)
	{
		for (int x = 0; x < WDTH; x++)
		{
			// my_mlx_pixel_put(&img1, x, y, create_trgb(0, veclen(mrt.ray[y][x]), 0, 0));
			my_mlx_pixel_put(&img1, x, y, create_trgb(0, 0, -19 * plane_intercept(&mrt, mrt.ray[y][x], mrt.pl[0]), 0));
			my_mlx_pixel_put(&img2, x, y, create_trgb(0, 0, 0, (unsigned char)cylinder_intersect(mrt.cy[0]->cor, mrt.cy[0]->rad, mrt.cy[0]->hght, mrt.cam->cor, mrt.ray[y][x])));
			my_mlx_pixel_put(&img3, x, y, create_trgb(0, -100 * hit_sphere(mrt.sp[0]->cor, mrt.sp[0]->rad, mrt.cam->cor, mrt.ray[y][x]), 0, 0));
			// mlx_putpixel(img4, l, i, create_trgb(mrt.pixels[i][l]->clr_r, mrt.pixels[i][l]->clr_g, mrt.pixels[i][l]->clr_b, mrt.pixels[i][l]->light));
			if ((x == 0 || x == WDTH - 1) && (y == HGHT/2 || y == HGHT/2 + 1))
				printf("%0.1lf ", angle(mrt.ray[y][x], mrt.cam->v_o) * (180/PI));
		}
	}

	mlx_put_image_to_window(mlx, win, img1.img, 5, 10);
	mlx_put_image_to_window(mlx, win, img2.img, 15 + WDTH, 10);
	mlx_put_image_to_window(mlx, win, img3.img, 5, 15 + HGHT);
	// mlx_image_to_window(mlx, img4, 15 + WDTH, 15 + HGHT);

	mlx_loop(mlx);

	// for(int i = 0; i < HGHT; i++)
	// {
	// 	for (int l = 0; l < WDTH; l++)
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
