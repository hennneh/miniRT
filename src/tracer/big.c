#include "../../inc/minirt.h"

void	printvec(t_vec *p, char *description)
{
	if (p)
		printf("%s : %lf %lf %lf\n", description, p->x, p->y, p->z);
	else
		printf("%s\n", description);
}

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

int	nachfolger(int x, int y, t_mrt *mrt, t_vec *scr, t_data *img, t_bool p)
{
	double	old_d;
	double	d;
	int		rgb;
	int		i;
	t_obj	*near;
	t_vec	ray;
	t_vec	norm;

	t_bool	is_cap = FALSE;

	near = NULL;
	old_d = RENDER_DISTANCE;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	unit(&ray);
	rgb = create_trgb(0, mrt->al->lr * mrt->al->r, mrt->al->lr * mrt->al->g, mrt->al->lr * mrt->al->b);
	i = 0;
	while (mrt && mrt->obj && mrt->obj[i] && mrt->obj[i]->id)
	{
		d = 0;
		if (mrt->obj[i]->id == 'S')
		{
			d = hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, mrt->cam->cor, ray) / 2;
		}
		if (mrt->obj[i]->id == 'P')
		{
			d = hit_plane(mrt->cam->cor, ray, mrt->obj[i]);
		}
		if (mrt->obj[i]->id == 'C')
		{
			d = hit_circle(mrt->cam->cor, ray, mrt->obj[i]);
		}
		if (mrt->obj[i]->id == 'O')
		{
			d = hit_line(mrt->cam->cor, ray, mrt->obj[i]);
		}
		if (mrt->obj[i]->id == 'Z')
		{
			d = hit_cylinder(*mrt->obj[i], mrt->cam->cor, ray, &is_cap);
		}
		if (d && d > 0 && d < old_d)
		{
			if(!near || near->id != 'O')
			{
				near = mrt->obj[i];
				old_d = d;
			}
		}
		if (p && d)
		{
			printf("hit %c\nDistance %lf\n", mrt->obj[i]->id, d);
		}
		i++;
	}

	if (!near)
	{
		if (img)
			my_mlx_pixel_put(img, x, y, rgb);
		return(0);
	}
	t_vec	impact = v_sum(mrt->cam->cor, v_product(v_unit(ray), old_d));
	t_vec	light;
	double	bright;

	norm = init_vec(0, 1, 0);
	if (near->id == 'S')
		norm = connect(near->cor, impact);
	else if (near->id == 'P' || near->id == 'C')
		norm = near->v_o;
	else if (near->id == 'Z')
	{
		if (is_cap)
			norm = near->v_o;
		else
			norm = v_invert(cross(near->v_o, cross(near->v_o, connect(near->cor, impact))));
	}

	light = connect(impact, mrt->l->cor);
	unit(&light);
	bright = 1 - (2 * angle(light, norm) / (PI));
	limit(&bright, 1, 0);
	if (near && p)
	{
		unit(&norm);
		printvec(&norm, "Norm");
		printvec(&light, "light");
		printvec(NULL, "angle");
		printf("	%lf\n", bright);
	}
	if (near->id == 'O')
		bright = 1;
	if (near)
	{
		rgb = create_trgb(0,	near->r * bright/* * (bright >= 0) + 0*/,
								near->g * bright/* * (bright >= 0) + 0*/,
								near->b * bright/* * (bright >= 0) + 0*/);
	}

	t_bool shadow = FALSE;

	i = 0;
	while(mrt && mrt->obj && mrt->obj[i] && mrt->obj[i]->id)
	{
		d = 0;
		if (mrt->obj[i]->id == 'S')
		{
			d = hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, impact, light);
		}
		if (mrt->obj[i]->id == 'P')
		{
			d = hit_plane(mrt->cam->cor, light, mrt->obj[i]);
		}
		// if (mrt->obj[i]->id == 'C')
		// {
		// 	d = hit_circle(mrt->cam->cor, ray, mrt->obj[i]);
		// }
		if (mrt->obj[i]->id == 'Z')
		{
			d = hit_cylinder(*mrt->obj[i], impact, light, &shadow);
		}
		if (d > 0.1 && d < veclen(connect(impact, mrt->l->cor)))
		{
			shadow = TRUE;
			break ;
		}
		i++;
	}
	if (shadow == TRUE)
		rgb = create_trgb(0, 0, 0, 0);
	if (img)
		my_mlx_pixel_put(img, x, y, rgb);
	return (0);
}
