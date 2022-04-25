#include "../../inc/minirt.h"

int	shadow(t_mrt *mrt, double *obj)
{
	double	ray[3];
	
	if (!mrt->l || !obj)
		return (NULL);
	ray = connect(mrt->l, obj);
	while (mrt->sp[i])
	{
		if (hit_sphere(mrt->sp[i]->cor, mrt->sp[i]->rad, obj, ray)
			return (1);
		i++;
	}
	//repeat for planes and cylinders
	return (0);
}
