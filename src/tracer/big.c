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

int	colorme(t_mrt *mrt, t_obj *obj, double *ray)
{
	double	*impact;
	double	*norm;
	double	*light;
	int		res;
	double	bright;

	if (!obj)
		return (create_trgb(0, mrt->al->r, mrt->al->g, mrt->al->b));
	res = 0;
	impact = ray_alloc(mrt->cam->cor[0], mrt->cam->cor[1], mrt->cam->cor[2]);
	addto(impact, ray);
	if (obj->id == 'S')
	{
		norm = connect(obj->cor, impact);
	}
	else
	{
		norm = ray_alloc(obj->v_o[0], obj->v_o[1], obj->v_o[2]);
	}
	light = connect(impact, mrt->l->cor);
	bright = (angle(light, norm)) * mrt->l->brit;
	// if (shadow(mrt, impact))
	// 	bright = 0;
	if (obj && obj->id == 'S')
		res = create_trgb(0	, bright * obj->r
							, bright * obj->g
							, bright * obj->b);
	else if (obj && obj->id == 'P')
		res = create_trgb(0	, bright * obj->r
							, bright * obj->g
							, bright * obj->b);
	return (res);
}

int	nachfolger(int x, int y, t_mrt *mrt, double **scr, t_data *img)
{
	int		sd;
	int		col;
	int		i;
	t_obj	*near;
	double	*ray;

	sd = RENDER_DISTANCE;
	near = NULL;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	i = 0;
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
			col = ROUND_ERROR * plane_intercept(mrt, ray, mrt->obj[i]);
			if (col < sd && col > 0)
			{
				near = mrt->obj[i];
				sd = col;
			}
		}
		i++;
	}
	resize(ray, sd - 1);
	col = colorme(mrt, near, ray);
	my_mlx_pixel_put(img, x, y, col);
	return (0);
}
