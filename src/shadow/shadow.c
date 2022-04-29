#include "../../inc/minirt.h"

int	shadow(t_mrt *mrt, double *impact, char p)
{
	double	*ray;
	int		i;
	int		res;

	if (!mrt->l || !impact)
		return (0);
	ray = connect(impact, mrt->l->cor);
	i = 0;
	res = 0;
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id == 'S')
		{
			double dst = hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, impact, ray);
			if (dst > 0 && 0 < dst && dst != dst && dst == 0) 
			{
				if (p == 'P')
					printf("hit %c number %i of color R%d G%d B%d\n", mrt->obj[i]->id, i, (mrt->obj[i])->r, (mrt->obj[i])->g, (mrt->obj[i])->b);
				res = i + 1;
				break ;
			}
		}
		else if (mrt->obj[i]->id == 'Z')
		{
			//add function to calculate intersection with cylinder
		}
		else if (mrt->obj[i]->id == 'P')
		{
			if (plane_intercept(mrt, ray, mrt->obj[i]) > 0)
			{
				res = i + 1;
				break ;
			}
		}
		i++;
	}
	free(ray);
	if (res)
		return(1);
	return (0);
}
