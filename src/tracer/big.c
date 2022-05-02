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

	// if (!obj) // point of failiure
	// 	return (0);
	res = 0;
	impact = mrt->cam->cor;
	addto(&impact, ray);
	if (obj && obj->id == 'S')
	{
		norm = connect(obj->cor, impact);
	}
	else if (obj)
	{
		norm = obj->v_o;
	}
	light = connect(impact, mrt->l->cor);
	bright = angle(&light, &norm) * PI/2;
	return (create_trgb(0,(int)(bright * light.x),(int)(bright * light.y),(int)(bright * light.z)));
	// if (shadow(mrt, impact, 0) == 1)
	// {
	// 	return 0;
	// }
	if (obj && (obj->id == 'S' || obj->id == 'P'))
		res = create_trgb(0,	obj->r
							,	obj->g
							,	obj->b);
	return (res);
}

int	nachfolger(int x, int y, t_mrt *mrt, t_vec *scr, t_data *img)
{
	double	sd;
	double	col;
	int		rgb;
	int		i;
	t_obj	*near;
	t_vec	ray;

	sd = RENDER_DISTANCE;
	near = NULL;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	i = 0;
	col = 0;
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id == 'S')
		{
			col = ROUND_ERROR * hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, mrt->cam->cor, ray);
			if (col < sd && col > 0)
			{
				near = mrt->obj[i];
				sd = col;
			}
		}
		else if (mrt->obj[i]->id == 'P')
		{
			col = ROUND_ERROR * hit_plane(mrt, ray, mrt->obj[i]);
			if (col < sd && col > 0)
			{
				near = mrt->obj[i];
				sd = col;
			}
		}
		i++;
	}
	unit(&ray);
	product(&ray, col);
	rgb = colorme(mrt, NULL, ray);
	my_mlx_pixel_put(img, x, y, rgb);
	return (0);
}
