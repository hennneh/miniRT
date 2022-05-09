#include "../../inc/minirt.h"

/**
 * @brief change a vecto to have the total lenth of 1, no change direction
 * @param a [t_vec] vector to operade on
 * @return [void]
*/
void	unit(t_vec	*a)
{
	double	d;

	if (!a)
		return ;
	d = 1 / veclen(*a);
	a->x *= d;
	a->y *= d;
	a->z *= d;
}

/**
 * @brief change a vecto to have the total lenth of 1, no change direction
 * @param a [t_vec] vector to operade on
 * @return [void]
*/
t_vec	v_unit(t_vec	a)
{
	t_vec	res;
	double	d;

	d = 1 / veclen(a);
	res.x = a.x * d;
	res.y = a.y * d;
	res.z = a.z * d;
	return (res);
}

/**
 * @brief calculate the angle between two vectors
 * @param a [t_vec]
 * @param b [t_vec]
*/
double	angle(t_vec a, t_vec b)
{
	double	scalar;

	unit(&a);
	unit(&b);
	scalar = calculate_dot(&a, &b);
	return ((acos(scalar)));
}

/**
 * @brief Return the dot calculations of two Vectors
 * 
 * @param a Pointer of type double
 * @param b Pointer of type double
 * @return double
 */
double	calculate_dot(t_vec *a, t_vec *b)
{
	double	dot;

	if (b != NULL)
		dot = a->x * b->x + a->y * b->y + a->z * b->z;
	else
		dot = a->x * a->x + a->y * a->y + a->z * a->z;
	return (dot);
}

/**
 * @brief return a vector wit all the inverted values of the argument
 * @param a vector to invert
*/
t_vec	v_invert(t_vec a)
{
	t_vec	res;

	res.x = -a.x;
	res.y = -a.y;
	res.z = -a.z;
	return (res);
}
