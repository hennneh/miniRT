#include "../../inc/minirt.h"

//	a functin that is given a position and calculates
//	1: the ray to that position in an imaginary screen (given, to reduce redundant calculation)
//	2: the closest intsersection with any object (within reasonable distance)
//	3: the light value on that position (trace again from there to light)
//	4: takes all information and crunches it into color, which is then returned as an int

//	suggestions for funky names:
//	i_wanna_be_tracer
//	i'm_already_tracer
//	Amazing_trace,how_sweet_the_sound

int	nachfolger(int x, int y, t_mrt *mrt, double **scr, t_data *img)
{
	int	i;
	int	k;
  int	sd;
	int	cd;
	double	*ray;
	void	*obj;

	i = 0;
	sd = RENDER_DISTANCE;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	obj = NULL;
	while (mrt && mrt->sp && mrt->sp[i])
	{
		cd = 1000 * hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, mrt->cam->cor, ray);
		if (cd < sd && cd != 0)
		{
			sd = cd;
			obj = mrt->sp[i];
			k = 1;
		}
		i++;
	}
	if (sd < 0)
		sd *= -1;
	i = 0;
	while (mrt && mrt->pl && mrt->pl[i])
	{
		cd = 1000 * plane_intercept(mrt, ray, mrt->pl[i]);
		if (cd < sd && cd != 0)
		{
			sd = cd;
			obj = mrt->pl[i];
			k = 2;
		}
		i++;
	}
	// i = 0;
	// while (mrt && mrt->cy && mrt->cy[i])
	// {
	// 	cd = cylinder_intersect(mrt->cy[i]->cor, mrt->cy[i]->rad, mrt->cy[i]->hght, mrt->cam->cor, mrt->ray[y][x]);
	// 	if (cd >= 0 && cd < sd)
	// 	{
	// 		sd = cd;
	// 		obj = mrt->cy[i];
	// 	}
	// 	i++;
	// }
	if (obj && k == 1)
		my_mlx_pixel_put(img, x, y, create_trgb(0, ((t_sph *)obj)->r, ((t_sph *)obj)->g, ((t_sph *)obj)->b));
	else if (obj && k == 2)
		my_mlx_pixel_put(img, x, y, create_trgb(0, ((t_pl*)obj)->r, ((t_pl*)obj)->g, ((t_pl*)obj)->b));
	else
		my_mlx_pixel_put(img, x, y, create_trgb(0, mrt->al->lr * mrt->al->r, mrt->al->lr * mrt->al->g, mrt->al->lr * mrt->al->b));
	return (0);
}
