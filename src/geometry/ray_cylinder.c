/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:29:19 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:29:20 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define EPSILON 0.00001

int	cylinder_coefficient(t_obj cyl, double *x, t_vec *ray_or, t_vec *ray_dir)
{
	t_vec	v;
	t_vec	u;
	t_vec	normalized;
	t_vec	tmp;

	normalized = cyl.v_o;
	unit(&normalized);
	v = v_product(normalized, calculate_dot(ray_dir, &normalized));
	v = connect(v, *ray_dir);
	tmp = connect(cyl.cor, *ray_or);
	u = v_product(normalized, calculate_dot(&tmp, &normalized));
	u = connect(u, connect(cyl.cor, *ray_or));
	tmp.x = calculate_dot(&v, &v);
	tmp.y = 2 * calculate_dot(&v, &u);
	tmp.z = calculate_dot(&u, &u) - pow(cyl.rad, 2);
	x[0] = (-tmp.y + sqrt(pow(tmp.y, 2) - 4 * tmp.x * tmp.z)) / (2 * tmp.x);
	x[1] = (-tmp.y - sqrt(pow(tmp.y, 2) - 4 * tmp.x * tmp.z)) / (2 * tmp.x);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

t_vec	calc_cy_normal(double *x, t_obj cyl, t_vec ray_or, t_vec ray_dir)
{
	double	d[2];

	unit(&cyl.v_o);
	if ((x[2] >= 0 && x[2] <= cyl.hght && x[0] > EPSILON) && (x[3] >= \
		0 && x[3] <= cyl.hght && x[1] > EPSILON))
	{
		d[0] = (x[0] < x[1]) * x[2] + (x[0] >= x[1]) * x[3];
		d[1] = (x[0] < x[1]) * x[0] + (x[0] >= x[1]) * x[1];
	}
	else if (x[2] >= 0 && x[2] <= cyl.hght && x[0] > EPSILON)
	{
		d[0] = x[2];
		d[1] = x[0];
	}
	else
	{
		d[0] = x[3];
		d[1] = x[1];
	}
	x[0] = d[1];
	return (v_unit(connect(connect(ray_or, cyl.cor), connect(\
	v_product(v_unit(cyl.v_o), d[0]), v_product(ray_dir, d[1])))));
}

t_vec	new_pos(t_vec *posi, t_vec *dir, double height, t_vec *norm)
{
	t_vec	pos;

	*norm = *dir;
	unit(norm);
	pos.x = posi->x - (norm->x * (height / 2));
	pos.y = posi->y - (norm->y * (height / 2));
	pos.z = posi->z - (norm->z * (height / 2));
	return (pos);
}

double	new_cylinder_intersect(t_obj cyl, t_vec *ray_or, t_vec *ray_dir)
{
	double	x[4];
	t_vec	normalized;
	t_vec	helper;

	cyl.cor = new_pos(&cyl.cor, &cyl.v_o, cyl.hght, &normalized);
	if (cylinder_coefficient(cyl, x, ray_or, ray_dir) == 0)
		return (0);
	helper = connect(connect(*ray_or, cyl.cor), v_product(*ray_dir, x[0]));
	x[2] = calculate_dot(&normalized, &helper);
	helper = connect(connect(*ray_or, cyl.cor), v_product(*ray_dir, x[1]));
	x[3] = calculate_dot(&normalized, &helper);
	if (!((x[2] >= 0 && x[2] <= cyl.hght && x[0] > EPSILON) || (x[3] >= 0 && \
			x[3] <= cyl.hght && x[0] > EPSILON)))
		return (0);
	calc_cy_normal(x, cyl, *ray_or, *ray_dir);
	return (x[0]);
}

double	hit_cylinder(t_obj cyl, t_vec ray_or, t_vec ray_dir)
{
	double	cylinder_inter;

	cylinder_inter = new_cylinder_intersect(cyl, &ray_or, &ray_dir);
	return (cylinder_inter);
}
