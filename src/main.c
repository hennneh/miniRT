#include "../inc/minirt.h"

void	calc(t_mrt *mrt)
{
	int		cord[2];
	t_vec	*scr;

	scr = scream(mrt->cam);
	if (!mrt->img.img)
	{
		mrt->img.img = mlx_new_image(mrt->mlx, WDTH, HGHT);
		mrt->img.addr = mlx_get_data_addr(mrt->img.img, \
			&mrt->img.bits_per_pixel, &mrt->img.line_length, &mrt->img.endian);
	}
	cord[1] = 0;
	while (cord[1] < HGHT)
	{
		cord[0] = 0;
		while (cord[0] < WDTH)
		{
			nachfolger(cord, mrt, scr, FALSE);
			cord[0]++;
		}
		cord[1]++;
	}
	free(scr);
}

int	render(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img.img, 0, 0);
	return (0);
}

int	key_hook(int key, t_mrt *mrt)
{
	static t_bool	swtch;

	if (key == 65307)
		rt_exit(mrt);
	if (key == 116)
		swtch = !swtch;
	if (!swtch && key == 99)
		controls();
	else if (swtch && key == 112)
		print_config(mrt, 0);
	else if (swtch && key == 114)
		debug(mrt);
	else if (swtch && (key == 105 || key == 106 || key == 107 || key == 108 \
	|| key == 246 || key == 252))
		move(mrt, key);
	else if (swtch && (key == 65362 || key == 65364 || key == 65361 || key \
	== 65363 || key == 228 || key == 35))
		camera(mrt, key);
	else if (swtch && (key == 119 || key == 97 || key == 115 || key == 100 \
	|| key == 102 || key == 98 || key == 43 || key == 45))
		light(mrt, key);
	else if (swtch && key == 111)
		origin(mrt, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mrt	mrt;

	if (argc != 2)
	{
		printf("Error\nIncorrect number of Args\n");
		return (1);
	}
	if (input(&mrt, argv[1]))
		return (printf("ERROR INPUT\n"));
	expand_obj(&mrt);
	flip(&mrt);
	mrt.mlx = mlx_init();
	mrt.win = mlx_new_window(mrt.mlx, WDTH, HGHT, "I wanna be Tracer");
	mrt.img.img = NULL;
	calc(&mrt);
	controls();
	mlx_mouse_show(mrt.mlx, mrt.win);
	mlx_loop_hook(mrt.mlx, render, &mrt);
	mlx_key_hook(mrt.win, key_hook, &mrt);
	mlx_hook(mrt.win, 33, (1L << 17), rt_exit, &mrt);
	mlx_loop(mrt.mlx);
	rt_exit(&mrt);
	return (0);
}
