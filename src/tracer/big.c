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
		cd = hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, mrt->cam->cor, ray);
		// my_mlx_pixel_put(img, x, y, create_trgb(0, mrt->sp[i]->r, mrt->sp[i]->g, mrt->sp[i]->b));
		my_mlx_pixel_put(img, x, y, create_trgb(0, 0, 0, 0)); // AMB
		if (cd < sd && cd != 0)
		{
			sd = cd;
			my_mlx_pixel_put(img, x, y, create_trgb(0, mrt->sp[i]->r, mrt->sp[i]->g, mrt->sp[i]->b));
		}
		i++;
	}
	// i = 0;
	// while (mrt && mrt->pl && mrt->pl[i])
	// {
	// 	cd = plane_intercept(mrt, ray, mrt->pl[i]);
	// 	if (cd >= 0 && cd < sd)
	// 	{
	// 		sd = cd;
	// 		obj = mrt->pl[i];
	// 	}
	// 	i++;
	// printf("debug4\n");
	// }
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
	return (0);
}
