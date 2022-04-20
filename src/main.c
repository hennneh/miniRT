#include "../inc/minirt.h"

// int	print_mrt(t_mrt *m)
// {
// 	printf("\nLIGHT\n{\n");
// 	printf("id : [%c]\n", m->l->id);
// 	printf("cor : [%f][%f][%f]\n", m->l->cor[0], m->l->cor[1], m->l->cor[2]);
// 	printf("brit : [%f]\n}\n", m->l->brit);
// 	printf("\nSPHERE\n{\n");
// 	printf("id : [%c]\n", m->sp[0]->id);
// 	printf("cor : [%f][%f][%f]\n", m->sp[0]->cor[0], m->sp[0]->cor[1], m->sp[0]->cor[2]);
// 	printf("rad : [%f]\n", m->sp[0]->rad);
// 	printf("rgb : [%d][%d][%d]\n}\n", m->sp[0]->r, m->sp[0]->g, m->sp[0]->b);
// 	return (1);
// }

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	double	**scr;
	t_data	img;
	t_mrt	mrt;
  
	if (argc != 2)
	{
		printf("not exactly one arguemnt\n");
		return (1);
	}
	if (input(&mrt, argv[1]))
		return (printf("ERROR INPUT\n"));
	// input(&mrt, argv[1]);

	// mrt.sp = ft_calloc(4, sizeof(t_sph *));
	// mrt.sp[0] = ft_calloc(1, sizeof(t_sph));
	// mrt.sp[0]->cor[0] = 0;
	// mrt.sp[0]->cor[1] = 0;
	// mrt.sp[0]->cor[2] = 0;
	// mrt.sp[0]->rad = 6;
	// mrt.sp[0]->r = 0;
	// mrt.sp[0]->g = 0;
	// mrt.sp[0]->b = 255;

	// mrt.sp[1] = ft_calloc(1, sizeof(t_sph));
	// mrt.sp[1]->cor[0] = 255;
	// mrt.sp[1]->cor[1] = 0;
	// mrt.sp[1]->cor[2] = 0;
	// mrt.sp[1]->rad = 6;
	// mrt.sp[1]->r = 0;
	// mrt.sp[1]->g = 255;
	// mrt.sp[1]->b = 0;

	// mrt.sp[2] = ft_calloc(1, sizeof(t_sph));
	// mrt.sp[2]->cor[0] = 10;
	// mrt.sp[2]->cor[1] = 0;
	// mrt.sp[2]->cor[2] = 0;
	// mrt.sp[2]->rad = 6;
	// mrt.sp[2]->r = 100;
	// mrt.sp[2]->g = 100;
	// mrt.sp[2]->b = 0;

	// mrt.sp[3] = NULL;

	// mrt.cam = ft_calloc(1, sizeof(t_cam));
	// mrt.cam->cor[0] = 0;
	// mrt.cam->cor[1] = 30;
	// mrt.cam->cor[2] = 0;
	// mrt.cam->fov = 90;
	// mrt.cam->v_o[0] = 0;
	// mrt.cam->v_o[1] = -1;
	// mrt.cam->v_o[2] = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WDTH, HGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WDTH, HGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	scr = scream(mrt.cam);
	for (int y = 0; y < HGHT; y++)
	{
		for (int x = 0; x < WDTH; x++)
		{
			nachfolger(x, y, &mrt, scr, &img);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
