/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:29:35 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:29:36 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Return the the distance to the given sphere
 * if it hitting as a double else it return -1
 * @param sph_org Pointer of type double that save the coordinate
 * 				of the sphere point[3]
 * @param sph_rad Radius of the sphere as double
 * @param ray_or Ray Vector as Pointer of type double ray[3]
 * @param ray_dir
 * 
 * @return Distance to object on this ray vector
 */
double	hit_sphere(t_vec sph_org, double sph_rad, t_vec ray_or, t_vec ray_dir)
{
	t_vec	oc;
	t_vec	tmp;
	double	disc;

	oc = connect(sph_org, ray_or);
	tmp.x = calculate_dot(&ray_dir, NULL);
	tmp.y = 2.0 * calculate_dot(&oc, &ray_dir);
	tmp.z = calculate_dot(&oc, NULL) - sph_rad * sph_rad;
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (0);
	else
		return (-((tmp.y) + sqrt(disc)) / tmp.x);
}
