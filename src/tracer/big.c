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

int	colorme(t_mrt *mrt, t_obj *obj, t_vec ray)
{
	t_vec	impact;
	t_vec	norm;
	t_vec	light;
	int		res;
	double	bright = 10;

	if (!obj) // point of failiure
		return (0);
	res = 0;
	impact = mrt->cam->cor;
	addto(&impact, ray);
	if (obj && obj->id == 'S')
	{
		norm = connect(obj->cor, impact);
	}
	else
	{
		norm = obj->v_o;
	}
	unit(&norm);
	light = connect(impact, mrt->l->cor);
	bright = angle(light, norm) * 10;
	// if (shadow(mrt, impact, 0) == 1)
	// {
	// 	return 0;
	// }
	if (obj && (obj->id == 'S' || obj->id == 'P' || obj->id == 'Z'))
		res = create_trgb(0,	obj->r
							,	obj->g
							,	obj->b);
	return (res);
	return (create_trgb(0,(int)(bright * norm.x * 128),(int)(bright * norm.y * 128),(int)(bright * norm.z * 128)));
}

int	nachfolger(int x, int y, t_mrt *mrt, t_vec *scr, t_data *img)
{
	double	old_d;
	double	d;
	int		rgb;
	int		i;
	t_obj	*near;
	t_vec	ray;

	near = NULL;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	i = 0;
	old_d = RENDER_DISTANCE;
	while (mrt && mrt->obj && mrt->obj[i] && mrt->obj[i]->id)
	{
		d = 0;
		if (mrt->obj[i]->id == 'S')
		{
			d = ROUND_ERROR * hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, mrt->cam->cor, ray);
		}
		if (mrt->obj[i]->id == 'P')
		{
			d = ROUND_ERROR * hit_plane(mrt, ray, mrt->obj[i]);
		}
		if (mrt->obj[i]->id == 'Z')
		{
			d = ROUND_ERROR * new_cylinder_intersect(&mrt->obj[i]->cor, &mrt->obj[i]->v_o, mrt->obj[i]->rad, mrt->obj[i]->hght, &mrt->cam->cor, &ray);
		}
		if (d && d > 0 && d < old_d)
		{
			near = mrt->obj[i];
			unit(&ray);
			product(&ray, d);
			rgb = colorme(mrt, near, ray);
			my_mlx_pixel_put(img, x, y, rgb);
			old_d = d;
		}
		i++;
	}
	return (0);
}
