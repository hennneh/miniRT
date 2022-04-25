#include "../../inc/minirt.h"

int	shadow(t_mrt *mrt, double *obj)
{
	double	*ray;
	int		i;

  i = 0;
	if (!mrt->l || !obj)
		return (0);
	ray = connect(mrt->l->cor, obj);
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id == 'S')
		{
			if (hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, obj, ray))
				break ;
		}
		else if (mrt->obj[i]->id == 'Z')
		{
			//add function to calculate intersection with cylinder
		}
		else if (mrt->obj[i]->id == 'P')
		{
			if (plane_intercept(mrt, ray, mrt->obj[i]))
				break ;
		}
		i++;
	}
	free(ray);
	if (mrt->obj[i])
		return(1);
	return (0);
}
