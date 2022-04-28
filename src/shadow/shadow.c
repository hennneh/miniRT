#include "../../inc/minirt.h"


int	shadow(t_mrt *mrt, double *impact)
{
	double	*ray;
	int		i;

	i = 0;
	if (!mrt->l || !impact)
		return (0);
	ray = connect(impact, mrt->l->cor);
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id == 'S')
		{
			if (hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, impact, ray) != 0)
				break ;
		}
		else if (mrt->obj[i]->id == 'Z')
		{
			//add function to calculate intersection with cylinder
		}
		else if (mrt->obj[i]->id == 'P')
		{
			if (plane_intercept(mrt, ray, mrt->obj[i]) != 0)
				break ;
		}
		i++;
	}
	free(ray);
	if (mrt->obj[i])
		return(1);
	return (0);
}
