#include "../../inc/minirt.h"
<<<<<<< HEAD

int	shadow(t_mrt *mrt, double *impact)
=======
/*
int	shadow(t_mrt *mrt, double *obj)
>>>>>>> a6756b4754e7e01a112e50092aba9af3fe3c35c7
{
	double	*ray;
	int		i;

	i = 0;
	if (!mrt->l || !impact)
		return (0);
	ray = connect(impact, mrt->l->cor);
	while (mrt->obj[i])
	{
<<<<<<< HEAD
		if (mrt->obj[i]->id == 'S' && hit_sphere(mrt->obj[i]->cor, mrt->obj[i]->rad, impact, ray))
			break ;
		if (mrt->obj[i]->id == 'P' && plane_intercept(mrt, ray, mrt->obj[i]))
			break ;
=======

			return (1);
>>>>>>> a6756b4754e7e01a112e50092aba9af3fe3c35c7
		i++;
	}
	if (mrt->obj[i])
		return (1);
	return (0);
}
*/

//starting over with new struct

int	shadow(t_mrt *mrt, double *obj)
{
	double	ray[3];
  int     i;

  i = 0;
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
