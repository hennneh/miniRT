/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_maths1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:29:02 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:29:03 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief add a two vectors together
 * @param a [t_vec] the vector being added to
 * @param b [t_vec] the vector to add
*/
void	addto(t_vec *a, t_vec b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
}

/**
 * @brief add a two vectors together
 * @param a [t_vec] the vector being added to
 * @param b [t_vec] the vector to add
*/
t_vec	v_sum(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/**
 * @brief multiply a vector by a constant
 * @param a [t_vec] the vector mutiplied
 * @param m [double] the multiplicant
*/
void	product(t_vec *a, double m)
{
	if (!a)
		return ;
	a->x *= m;
	a->y *= m;
	a->z *= m;
}

/**
 * @brief multiply a vector by a constant, and return a dublicate
 * @param a [t_vec] the vector mutiplied
 * @param m [double] the multiplicant
 */
t_vec	v_product(t_vec a, double m)
{
	t_vec	res;

	res.x = a.x * m;
	res.y = a.y * m;
	res.z = a.z * m;
	return (res);
}

/**
 * @brief add a set distance to a vector
 * @param a [t_vec] the vector
 * @param m [double] to be added length
*/
void	resize(t_vec *a, double m)
{
	t_vec	o;

	if (!a)
		return ;
	o.x = a->x;
	o.y = a->y;
	o.z = a->z;
	unit(&o);
	m -= 1;
	product(&o, m);
	addto(a, o);
}
