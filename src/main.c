
#include "../inc/minirt.h"

void	calc(t_mrt *mrt)
{
	t_data	img;
	int		y;
	int		x;
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
			nachfolger(x, y, mrt, scr, &img);
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
	int	i;
	// int	shad;
	double	d;
	// double	bright;
	t_vec	ray;
	t_vec	impact;
	t_vec	norm;
	// t_vec	light;
	t_vec	*scr;

	mlx_mouse_get_pos(mrt->mlx, mrt->win, &x, &y);
	scr = scream(mrt->cam);
	printf("ray trough x %i, y %i\n", x, y);
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	i = 0;
	while (mrt && mrt->obj && mrt->obj[i] && mrt->obj[i]->id)
	{
		d = 0;
		impact = init_vec(mrt->cam->cor.x, mrt->cam->cor.y, mrt->cam->cor.z);
		addto(&impact, ray);
				norm = init_vec(1,0,0);
		if (mrt->obj[i]->id == 'S')
		{
			d = hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, mrt->cam->cor, ray);
			norm = connect(impact, mrt->obj[i]->cor);
		}
		if (mrt->obj[i]->id == 'P')
		{
			d = hit_plane(mrt, ray, mrt->obj[i]);
			norm = init_vec(mrt->obj[i]->v_o.x, mrt->obj[i]->v_o.y, mrt->obj[i]->v_o.z);
		}
		if (d)
		{
			resize(&ray, d);
			printf("KIND %C	, at a distance of %lf\n", mrt->obj[i]->id, d);
			printf("Input Colors R%d G%d B%d\n", mrt->obj[i]->r, mrt->obj[i]->g, mrt->obj[i]->b);
			// printf("norm of object  %lf  %lf  %lf\n", norm.x, norm.y, norm.z);
			// impact = mrt->cam->cor;
			// addto(&impact, ray);
			// light = connect(impact, mrt->l->cor);
			// unit (&norm);
			// bright = angle(light, norm);
			// printf("light %lf %lf %lf\n", light.x, light.y, light.z);
			// printf("\t\t\tangle %lf \n", bright + 1);
			// shad = shadow(mrt, impact, 'P');
			printf("object nr %i\n", i);
		}
		i++;
	}
	// i = 0;
	// while (mrt && mrt->cy && mrt->cy[i])
	// {
	// 	d = cylinder_intersect(mrt->cy[i]->cor, mrt->cy[i]->rad, mrt->cy[i]->hght, mrt->cam->cor, ray);
	// 	if (d)
	// 		printf("cylinder hit	%i, at a distance of %i\n", i, d);
	// 	i++;
	// }
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
	if (key == 65307)
		end(mrt);
	if (key == 100)
		debug(mrt);
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
