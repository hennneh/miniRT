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

int	main(void)
{
	t_mrt	mrt;
	t_cam	cam;
	cam.pos = {0,0,0};
	cam.v_o = {1,1,0};
	mrt.cam = &cam;
	t_obj	obj[3];
	obj[2] = NULL;
	mrt.obj = &obj;
	obj[0].id = 'S';
	obj[1].id = 'S';
	obj[0].cor = {5,5,0};
	obj[1].cor = {10,10,0};
	obj[0].rad = 1.0;
	obj[1].rad = 1.0;
	double	vec = {4,4,0};
	int	ret = shadow(&mrt, vec);
	if (ret == 1)
		printf("1\n");
	else
		printf("0\n");
	return (0);
}
