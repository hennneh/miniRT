/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:28:42 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:28:44 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * Error Exit, goes through mrt and frees all inputs
 * @param mrt [t_mrt *] mrt struct
 * @param good [int] first position filled
 * @param count [int] max number of objects
 * @return [void] exits at end of function with (1)
*/
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
	perror("Error\n Invalid input\n");
	exit(1);
}

/**
 * Exit, goes through mrt and frees all inputs
 * @param mrt [t_mrt *] mrt struct
 * @return [int] exits at end of function with (0)
*/
int	rt_exit(t_mrt *mrt)
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
		free(mrt->obj[x ++]);
	if (mrt->obj)
		free(mrt->obj);
	mlx_destroy_image(mrt->mlx, mrt->img.img);
	mlx_destroy_window(mrt->mlx, mrt->win);
	mlx_destroy_display(mrt->mlx);
	if (mrt->mlx)
		free(mrt->mlx);
	exit(0);
	return (0);
}
