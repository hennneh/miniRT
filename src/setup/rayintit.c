#include "../../inc/minirt.h"

//	distance = acos (FOV/2) * ("wdth")
/**
 * @brief to initialize i use an imaginary screen plane, to which i point my rays
 * @param	cam [t_cam*] the camera in the scene
 * @return	[double**] [0]: vector on the screenplane, orthogonal to the g_z axis
 * 					[1]: vector on the screenplane, orthogonal to the vector in [0]
 * 					[2]: address of the distance to the screen
*/
double	**screen(t_cam *cam)
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
	res[2] = malloc(1 * sizeof(double));
	res[2] = acos(cam->fov / 2) * wdth * divergence;
	return(res);
}

// double	*single_ray(int x, int y, t_cam *cam, double **scr)
// {
	
// }
