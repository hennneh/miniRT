#include "../../inc/minirt.h"

void	*scour_sph(t_mrt *mrt, double *ray, int *k, int *sd)
{
	int		i;
	int		cd;
	void	*obj;

	i = 0;
	obj = NULL;
	while (mrt && mrt->sp && mrt->sp[i])
	{
		cd = ROUND_ERROR * hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, mrt->cam->cor, ray);
		if (cd < *sd && cd != 0)
		{
			*sd = cd;
			obj = mrt->sp[i];
			*k = 1;
		}
		i++;
	}
	return (obj);
}

void	*scour_pl(t_mrt *mrt, double *ray, int *k, int *sd)
{
	int		i;
	int		cd;
	void	*obj;

	i = 0;
	obj = NULL;
	while (mrt && mrt->pl && mrt->pl[i])
	{
		cd = ROUND_ERROR * plane_intercept(mrt, ray, mrt->pl[i]);
		if (cd < *sd && cd != 0)
		{
			*sd = cd;
			obj = mrt->pl[i];
			*k = 2;
		}
		i++;
	}
	return (obj);
}

void	*scour_cyl(t_mrt *mrt, double *ray, int *k, int *sd)
{
	int		i;
	int		cd;
	void	*obj;

	obj = NULL;
	i = 0;
	while (mrt && mrt->cy && mrt->cy[i])
	{
		cd = ROUND_ERROR * cylinder_intersect(mrt->cy[i]->cor, mrt->cy[i]->rad, mrt->cy[i]->hght, mrt->cam->cor, ray);
		if (cd < *sd && cd != 0)
		{
			*sd = cd;
			obj = mrt->cy[i];
			*k = 3;
		}
		i++;
	}
	return (obj);
}