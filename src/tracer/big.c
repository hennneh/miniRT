#include "../../inc/minirt.h"

//	a function that is given a position and calculates
//	1: the ray to that position in an imaginary screen (given, to reduce redundant calculation)
//	2: the closest intsersection with any object (within reasonable distance)
//	3: the light value on that position (trace again from there to light)
//	4: takes all information and crunches it into color, which is then returned as an int

//	suggestions for funky names:
//	i_wanna_be_tracer
//	i'm_already_tracer
//	Amazing_trace,how_sweet_the_sound

/**
 * find the object closest to the camera
 * put the representing color to the position in the image
 * @param x X-coordinate of the current pixel to trace
 * @param y Y-coordinate of the current pixel to trace
 * @param mrt our struct containing objects and camera
 * @param scr information needed to create the ray
 * @param img the resulting image
 * note ot colors: the color is defined by
 * 	1 the object
 * 	2 the ambient light
 * 	3 the angle at which the light hits the object
 */

int	nachfolger(int x, int y, t_mrt *mrt, t_vec *scr, t_data *img)
{
	double	old_d;
	double	d;
	int		rgb;
	int		i;
	t_obj	*near;
	t_vec	ray;

	near = NULL;
	old_d = RENDER_DISTANCE;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	unit(&ray);
	i = 0;
	while (mrt && mrt->obj && mrt->obj[i] && mrt->obj[i]->id)
	{
		d = 0;
		if (mrt->obj[i]->id == 'S')
		{
			d = hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, mrt->cam->cor, ray);
		}
		if (mrt->obj[i]->id == 'P')
		{
			d = hit_plane(mrt, ray, mrt->obj[i]);
		}
		// if (mrt->obj[i]->id == 'Z')
		// {
		// 	d = new_cylinder_intersect(NULL);
		// }
		if (d && d > 0 && d < old_d)
		{
			near = mrt->obj[i];
			old_d = d;
		}
		i++;
	}
	product(&ray, d);

	t_vec	impact = mrt->cam->cor;

	addto(&impact, ray);
	rgb = create_trgb(0, mrt->al->lr * mrt->al->r, mrt->al->lr * mrt->al->g, mrt->al->lr * mrt->al->b);
	if (near)
	{
		rgb = create_trgb(0,	near->r + ((255 - near->r) * 0.6),
								near->g + ((255 - near->g) * 0.6),
								near->b + ((255 - near->b) * 0.6));
	}
	my_mlx_pixel_put(img, x, y, rgb);
	return (0);
}
