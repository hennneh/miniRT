#include "../../inc/minirt.h"
/*
int	shadow(t_mrt *mrt, double *obj)
{
	double	ray[3];
	
	if (!mrt->l || !obj)
		return (NULL);
	ray = connect(mrt->l, obj);
	while (mrt->sp[i])
	{
		if (hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, obj, ray))
			return (1);
		i++;
	}
	//repeat for planes and cylinders
	return (0);
}
*/

//starting over with new struct

int	shadow(t_mrt *mrt, double *obj)
{
	double	ray[3];

	if (!mrt->l || !obj)
		return (NULL);
	ray = connect(mrt->l, obj);
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id == 'S')
		{
			if (hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, obj, ray))
				return (1);
		}
		else if (mrt->obj[i]->id == 'Z')
		{
			//add function to calculate intersection with cylinder
		}
		else if (mrt->obj[i]->id == 'P')
		{
			if (plane_intercept(mrt, ray, mrt->obj[i]->cor))
				return (1);
		}
		i++;
	}
	return (0);
}
