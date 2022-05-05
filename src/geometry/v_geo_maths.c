#include "../../inc/minirt.h"

/**
 * @brief return a vector orthogonal to both the given vectors
 * @param a [double*]
 * @param b [double*]
 * @return [double*]
*/
t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	res = vec_unit(res);
	return (res);
}

t_vec	create_vec(double x, double y, double z)
{
	t_vec	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

/**
 * @brief return the length of a vector
 * @param a [double*]
 * @return [double*]
*/
double	vec_veclen(t_vec a)
{
	return(pow(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2), 0.5));
}

/**
 * @brief return a vector connecting two points (! order counts)
 * @param a [double*] starting point
 * @param b [double*] ending point
 * @return [double*]
*/
t_vec	connect(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/**
 * @brief add a two vectors together
 * @param a [double*] the vector being added to
 * @param b [double*] the vector to add
*/
void	vec_add(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/**
 * @brief multiply a vector by a constant
 * @param a [double*] the vector mutiplied
 * @param m [double] the multiplicant
*/
t_vec	vec_product(t_vec a, double m)
{
	t_vec	res;

	res.x = a.x * m;
	res.y = a.y * m;
	res.z = a.z * m;
	return (res);
}

/**
 * @brief add a set distance to a vector
 * @param a [double*] the vector
 * @param m [double] to be added length
*/
void	resize(t_vec *a, double m)
{
	t_vec	o;

	if (!a)
		return ;
	o = *a;
	unit(&o);
	product(&o, m);
	addto(a, o);
}

/**
 * @brief change a vecto to have the total lenth of 1, no change direction
 * @param a [double*] vector to operade on
 * @return [void]
*/
t_vec	vec_unit(t_vec input)
{
	double	d;
	t_vec	res;

	d = 1 / vec_veclen(input);
	res.x = input.x * d;
	res.y = input.y * d;
	res.z = input.z * d;
	return (res);
}
/**
 * @brief calculate the angle between two vectors
 * @param a [double*]
 * @param b [double*]
*/
double	angle(t_vec a, t_vec b)
{
	double scalar;

	scalar = ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	if (scalar < 0)
		scalar *= -1;
	return (acos(scalar / (vec_veclen(a) * vec_veclen(b))));
}

/**
 * @brief reflect a given vector on a normal-vector
 * @param in [double*] the vector to be reflected
 * @param norm [double*] the achse to reflect over
 * we create a vector perpendiculliar to NORM and IN
 * and then use that vector to create another, perpendiculliar to NORM but in plane with IN
 * -> TANG; which we will use to calculate the reflection in 2d geometry.
 * a connecting vector between IN (1) and TANG (calc) is then returned as the result
*/
// double	*reflect(double in[3], double norm[3])
// {
// 	double	*tmp;
// 	double	*tang;
// 	double	*res;

// 	unit(in);
// 	tmp = cross(in, norm);
// 	tang = cross(tmp, norm);
// 	free(tmp);
// 	unit(tang);
// 	product(tang, -2 * cos(angle(in, tang)));
// 	res = connect(in, tang);
// 	return (res);
// }

/**
 * @brief Return the dot calculations of two Vectors
 * 
 * @param a Pointer of type double
 * @param b Pointer of type double
 * @return double
 */
double	vec_dot(t_vec a, t_vec b)
{
	double	dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
}
