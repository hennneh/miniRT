/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:30:36 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:30:37 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief to initialize i use an imaginary screen plane, to which i point my rays
 * @param	cam [t_cam*] the camera in the scene
 * @return	[double**] [0]: vector on the screenplane, orthogonal to the g_z axis
 * 					[1]: vector on the screenplane, orthogonal to the vector in [0]
 * 					[2]: direction vector of the correct length
 * distance = acos (FOV/2) * ("WDTH")
*/
t_vec	*scream(t_cam *cam)
{
	t_vec	*res;

	res = malloc(3 * sizeof(t_vec));
	if (cam->v_o.x == 0 && cam->v_o.y == 0)
		res[0] = init_vec(1, 0, 0);
	else
	{
		res[0] = cross(cam->v_o, init_vec(0, 0, 1));
		unit(&res[0]);
	}
	res[1] = cross(cam->v_o, res[0]);
	unit(&res[1]);
	res[2] = init_vec(cam->v_o.x, cam->v_o.y, cam->v_o.z);
	resize(&res[2], cos(cam->fov / 2) * (((WDTH * DIVERGENCE) / 2) / cos(PI / \
	2 - (cam->fov / 2))));
	return (res);
}

/**
 * NOTE: the offset is from the middle ray to a projection screen
 * meaning that to represent all pixels x and y need to start at -(max / 2)
 * @param x [int] horizontal PIxelcoordinate
 * @param y [int] vertical PIxelcoordinate
 * @param cam [t_cam*] originating viewpoint
 * @param scr [double**] defining parameters of the projection screen
 * @brief return a ray representing a PIxel with the xy offset given
*/
t_vec	single_ray(int x, int y, t_cam *cam, t_vec	scr[3])
{
	t_vec	summand;
	t_vec	tmp;

	summand = cam->cor;
	addto(&summand, scr[2]);
	tmp = scr[0];
	product(&tmp, x * DIVERGENCE);
	addto(&summand, tmp);
	tmp = scr[1];
	product(&tmp, y * DIVERGENCE);
	addto(&summand, tmp);
	return (connect(cam->cor, summand));
}
