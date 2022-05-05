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

void	limit(double *var, double upper, double lower)
{
	if (*var > upper)
		*var = upper;
	if (*var < lower)
		*var = lower;
}

void	calc(t_mrt *mrt)
{
	t_data	img;
	int	y;
	int	x;
	t_vec	*scr;

	scr = scream(mrt->cam);
	img.img = mlx_new_image(mrt->mlx, WDTH, HGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < HGHT)
	{
		x = 0;
		while (x < WDTH)
		{
			nachfolger(x, y, mrt, scr, &img, FALSE);
			x++;
		}
		y++;
	}
	mrt->img = img.img;
	// need to free scr
}

// Trace me baby one more time
void	debug(t_mrt *mrt)
{
	int	x;
	int	y;
	t_vec	ray;
	t_vec	*scr;

	mlx_mouse_get_pos(mrt->mlx, mrt->win, &x, &y);
	scr = scream(mrt->cam);
	printf("ray trough x %i, y %i\n", x, y);
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	nachfolger(x, y, mrt, scr, NULL, TRUE);
}


int	render(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
	return (0);
}

int	end(t_mrt *mrt)
{
	//exit functions
	if (mrt)
		exit(0);
	return (0);
}

int	key_hook(int key, t_mrt *mrt)
{
	static t_bool	swtch;


	if (key == 65307)
		end(mrt);
	if (key == 100) // d
	{
		printf("Toggle debugger\n");
		if (swtch)
			swtch = FALSE;
		else
			swtch = TRUE;
	}
	if (key == 114 && swtch) // r
		debug(mrt);
	if (key == 43 && swtch) // +
	{
		mrt->l->lr *= 1.125;
		limit(&mrt->l->lr, 1, 0);
		printf("brighter light\n");
		calc(mrt);
	}
	if (key == 45 && swtch) // -
	{
		mrt->l->lr *= 0.875;
		limit(&mrt->l->lr, 1, 0);
		printf("dimmer light\n");
		calc(mrt);
	}
	if (swtch)
		printf("%i\n", key);
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
	mrt.mlx = mlx_init();
	mrt.win = mlx_new_window(mrt.mlx, WDTH, HGHT, "I wanna be Tracer");
	calc(&mrt);
	mlx_mouse_show(mrt.mlx, mrt.win);
	mlx_loop_hook(mrt.mlx, render, &mrt);
	mlx_key_hook(mrt.win, key_hook, &mrt);
	mlx_hook(mrt.win, 33, (1L << 17), end, &mrt);
	mlx_loop(mrt.mlx);
	rt_exit(&mrt);
	return (0);
}
