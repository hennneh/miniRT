#include "../../inc/minirt.h"

/**
 * @brief to initialize i use an imaginary screen plane, to which i point my rays
 * @param	cam [t_cam*] the camera in the scene
 * @return	[double**] [0]: vector on the screenplane, orthogonal to the g_z axis
 * 					[1]: vector on the screenplane, orthogonal to the vector in [0]
 * 					[2]: direction vector of the correct length
 * distance = acos (FOV/2) * ("wdth")
*/
double	**scream(t_cam *cam)
{
	double	**res;
	double	*tmp;

	res = malloc(3 * sizeof(double **));
	res[0] = malloc(3 * sizeof(double *));
	if (cam->cor[1] == 0 && cam->cor[2] == 0)
		res[1] = unit(ray_alloc(0, 1, 0));
	else
	{
		tmp = ray_alloc(1, 0, 0);
		res[1] = unit(cross(cam->v_o, tmp));
		free(tmp);
	}
	res[1] = malloc(3 * sizeof(double *));
	res[1] = unit(cross(cam->v_o, res[0]));
	res[2] = malloc(3 * sizeof(double));
	res[2] = ray_alloc(cam->v_o[0], cam->v_o[1], cam->v_o[2]);
	product(res[2], acos(cam->fov / 2) * wdth * divergence);
	return(res);
}

/**
 * 	vec			from			to
 * 	res			cam->cor		curr
 * 	curr		scr->cor		scr->o_v
 * 	scr->o_v	scr_h			scr_v
*/
double	*single_ray(int x, int y, t_cam *cam, double **scr)
{
	double	*addict;
	double	*tmp;

	addict = ray_alloc(cam->cor[0], cam->cor[1], cam->cor[2]);
	addto(addict, scr[2]);
	tmp = ray_alloc(scr[0][0], scr[0][1], scr[0][2]);
	product(tmp, x * divergence);
	addto(addict, tmp);
	free(tmp);
	tmp = ray_alloc(scr[1][0], scr[1][1], scr[1][2]);
	product(tmp, y * divergence);
	addto(addict, tmp);
	free(tmp);
	return (unit(connect(cam->cor, addict)));
}

void	init_rays(t_mrt *mrt)
{
	int		x;
	int		y;
	double	**screen;

	screen = scream(mrt->cam);
	y = 0;
	while(y <= hght)
	{
		x = 0;
		while (x <= wdth)
		{
			mrt->ray[x][y] = single_ray(x, y, mrt->cam, screen)
			x++;
		}
		y++;
	}
}
