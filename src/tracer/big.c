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

int	colorme(t_mrt *mrt, int k, void *obj, double *ray)
{
	double	*impact;
	double	*ref;
	double	*norm;
	double	*light;
	int		res;
	double	bright;

	impact = ray_alloc(mrt->cam->cor[0], mrt->cam->cor[1], mrt->cam->cor[2]);
	addto(impact, ray);
	if (k == 1)
	{
		norm = connect(((t_sph *)obj)->cor, impact);
	}
	else //if (k == 2)
	{
		norm = ray_alloc(((t_pl *)obj)->v_o[0], ((t_pl *)obj)->v_o[1], ((t_pl *)obj)->v_o[2]);
	}
	ref = reflect(ray, norm);
	light = connect(impact, mrt->l->cor);
	bright = ((PI / 2) - angle(light, ref)) * 10 * mrt->l->brit;
	// if henne shadow -> bright = 0
	if (obj && k == 1)
		res = create_trgb(0	, bright * ((t_sph *)obj)->r + (mrt->al->lr * mrt->al->r)
							, bright * ((t_sph *)obj)->g + (mrt->al->lr * mrt->al->g)
							, bright * ((t_sph *)obj)->b + (mrt->al->lr * mrt->al->b));
	else if (obj && k == 2)
		res = create_trgb(0	, bright * ((t_pl*)obj)->r + (mrt->al->lr * mrt->al->r)
							, bright * ((t_pl*)obj)->g + (mrt->al->lr * mrt->al->g)
							, bright * ((t_pl*)obj)->b + (mrt->al->lr * mrt->al->b));
	else
		res = create_trgb(0, mrt->al->lr * mrt->al->r, mrt->al->lr * mrt->al->g, mrt->al->lr * mrt->al->b);
	return (res);
}

int	nachfolger(int x, int y, t_mrt *mrt, double **scr, t_data *img)
{
	int		k;
	int		sd;
	int		col;
	double	*ray;
	void	*tmp;
	void	*obj;

	k = 0;
	sd = RENDER_DISTANCE;
	ray = single_ray(x - (WDTH/2), y - (HGHT/2), mrt->cam, scr);
	tmp = scour_sph(mrt, ray, &k, &sd);
	if (k == 1)
		obj = tmp;
	tmp = scour_pl(mrt, ray, &k, &sd);
	if (k == 2)
		obj = tmp;
	// tmp = scour_cyl(mrt, ray, &k, &sd);
	// if (k == 3)
	// 	obj = tmp;
	resize(ray, sd);
	col = colorme(mrt, k, obj, ray);
	if (obj && k == 1)
		my_mlx_pixel_put(img, x, y, col);
	else if (obj && k == 2)
		my_mlx_pixel_put(img, x, y, col);
	else
		my_mlx_pixel_put(img, x, y, col);
	return (0);
}
