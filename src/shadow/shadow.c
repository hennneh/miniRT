#include "../../inc/minirt.h"

int	shadow(t_mrt *mrt, t_vec impact, char p)
{
	t_vec	ray;
	int		i;
	int		res;

	// if (!mrt->l || impact)
	// 	return (0);
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
			if (hit_plane(mrt, ray, mrt->obj[i]) > 0)
			{
				res = i + 1;
				break ;
			}
		}
		i++;
	}
	if (res)
		return(1);
	return (0);
}

// int	main(void)
// {
// 	t_mrt	mrt;
// 	t_cam	cam;
// 	cam.pos = init_vec(0,0,0);
// 	cam.v_o = init_vec(1,1,0);
// 	mrt.cam = &cam;
// 	t_obj	obj[3];
// 	obj[2] = NULL;
// 	mrt.obj = &obj;
// 	obj[0].id = 'S';
// 	obj[1].id = 'S';
// 	obj[0].cor = init_vec(5,5,0);
// 	obj[1].cor = init_vec(10,10,0);
// 	obj[0].rad = 1.0;
// 	obj[1].rad = 1.0;
// 	t_vec	vec = init_vec(4,4,0);
// 	int	ret = shadow(&mrt, vec);
// 	if (ret == 1)
// 		printf("1\n");
// 	else
// 		printf("0\n");
// 	return (0);
// }
