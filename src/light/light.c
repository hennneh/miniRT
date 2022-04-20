#include "../../inc/minirt.h"

int	light(t_mrt *mrt, double *obj)
{
	double	ray[3];
	
	if (!mrt->l || !obj)
		return (0);
	ray = connect(mrt->l, obj);
	while (mrt->sp[i])
	{
		if (calc_intersec(ray, obj, mrt))
			set_shadow();
		else
			set_light();
	}
	//repeat for planes and cylinders
	return (0);
}
