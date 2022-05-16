/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:28:55 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:28:57 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief return a vector orthogonal to both the given vectors
 * @param a [t_vec]
 * @param b [t_vec]
 * @return [t_vec]
*/
t_vec	cross(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	unit(&res);
	return (res);
}

t_vec	init_vec(double x, double y, double z)
{
	t_vec	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec	*vec_alloc(t_vec clone)
{
	t_vec	*res;

	res = malloc(sizeof(t_vec));
	res->x = clone.x;
	res->y = clone.y;
	res->z = clone.z;
	return (res);
}

/**
 * @brief return the length of a vector
 * @param a [t_vec]
 * @return [t_vec]
*/
double	veclen(t_vec a)
{
	if (a.x || a.y || a.z)
		return (pow(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2), 0.5));
	return (0);
}

/**
 * @brief return a vector connecting two points (! order counts)
 * @param a [t_vec] starting point
 * @param b [t_vec] ending point
 * @return [t_vec]
*/
t_vec	connect(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return (res);
}
