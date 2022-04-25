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

void	calc(t_mrt *mrt)
{
	t_data	img;
	int	y;
	int	x;
	double	**scr;

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
}

// Trace me baby one more time
void	debug(t_mrt *mrt)
{
	int	x;
	int	y;
	int	i;
	double	d;
	double	*ray;
	double	**scr;

	mlx_mouse_get_pos(mrt->mlx, mrt->win, &x, &y);
	scr = scream(mrt->cam);
	printf("ray trough x %i, y %i\n", x, y);
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	i = 0;
	while (mrt && mrt->sp && mrt->sp[i])
	{
		d = hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, mrt->cam->cor, ray);
		if (d)
		{
			printf("sphere hit		%i, at a distance of %lf\n", i, d);
			double	*impact;
			double	*ref;
			double	*norm;
			double	*light;
			double	bright;
			impact = ray_alloc(mrt->cam->cor[0], mrt->cam->cor[1], mrt->cam->cor[2]);
			addto(impact, ray);
			norm = connect(mrt->sp[i]->cor, impact);
			ref = reflect(ray, norm);
			light = connect(impact, mrt->l->cor);
			bright = angle(light, ref) * (180 / PI);
			printf("impact at	%lf %lf %lf\n", impact[0], impact[1], impact[2]);
			printf("light per at	 %lf %lf %lf\n", light[0], light[1], light[2]);
			printf("reflection	 %lf %lf %lf angle to light %lf\n", ref[0], ref[1], ref[2], angle(light, ref) * (180/PI));
			printf("brightness factor %lf\n", bright);
		}
		i++;
	}
	i = 0;
	while (mrt && mrt->pl && mrt->pl[i])
	{
		d =  plane_intercept(mrt, ray, mrt->pl[i]);
		if (d)
			printf("plane hit		%i, at a distance of %lf\n", i, d);
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
		printf("not exactly one argument\n");
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
	return (0);
}
