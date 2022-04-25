
#include "../../inc/minirt.h"

void	rt_er_exit(t_mrt *mrt, int good, int count)
{
	if (mrt->al)
		free(mrt->al);
	if (mrt->cam)
		free(mrt->cam);
	if (mrt->l)
		free(mrt->l);
	while (good < count)
	{
		if (mrt->obj[good])
			free(mrt->obj[good]);
		good ++;
	}
	if (mrt->obj)
		free(mrt->obj);
	perror("ERROR\n Invalid input\n");
	exit(1);
}

void	rt_exit(t_mrt *mrt)
{
	int	x;

	x = 0;
	if (mrt->al)
		free(mrt->al);
	if (mrt->cam)
		free(mrt->cam);
	if (mrt->l)
		free(mrt->l);
	while (mrt->obj[x])
	{
		free(mrt->obj[x]);
		x ++;
	}
	if (mrt->obj)
		free(mrt->obj);
	exit(0);
}
