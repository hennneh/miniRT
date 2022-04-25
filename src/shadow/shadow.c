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
		if (mrt->obj[i]->id == 'S' && hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, impact, ray))
			break ;
		if (mrt->obj[i]->id == 'P' && plane_intercept(mrt, ray, mrt->obj[i]))
			break ;
		i++;
	}
	if (mrt->obj[i])
		return (1);
	return (0);
}
