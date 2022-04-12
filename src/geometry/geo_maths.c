#include "../../inc/minirt.h"

/**
 * @brief return a vector orthogonal to both the given vectors
 * @param a [double*]
 * @param b [double*]
 * @return [double*]
*/
double	*cross(double *a, double *b)
{
	double	*res;

	res = malloc(3, sizeof(double));
	res[0] = a[2] * b[3] - a[3] * b[2];
	res[1] = a[3] * b[1] - a[1] * b[3];
	res[2] = a[1] * b[2] - a[2] * b[1];
	return (res);
}

double	*ray_alloc(double x, double y, double z)
{
	double	*res;

	res = malloc(3, sizeof(double));
	res[0] = x;
	res[1] = y;
	res[2] = z;
	return (res);
}

/**
 * @brief return the length of a vector
 * @param a [double*]
 * @return [double*]
*/
double	veclen(double *a)
{
	if (a && (a[0] || a[1] || a[2]))
		return(pow(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2), 0.5));
	return(0);
}

/**
 * @brief return a vector connecting two points (! order counts)
 * @param a [double*] starting point
 * @param b [double*] ending point
 * @return [double*]
*/
double	connect(double *a, double *b)
{
	double	*res;

	res = malloc(3, sizeof(double));
	res[0] = a[0] - b[0];
	res[1] = a[1] - b[1];
	res[2] = a[2] - b[2];
	return (res);
}

/**
 * @brief add a two vectors together
 * @param a [double*] the vector being added to
 * @param b [double*] the vector to add
*/
void	addto(double *a, double *b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

/**
 * @brief multiply a vector by a constant
 * @param a [double*] the vector mutiplied
 * @param m [double] the multiplicant
*/
void	product(double *a, double m)
{
	a[0] *= m;
	a[1] *= m;
	a[2] *= m;
}

/**
 * @brief change a vecto to have the total lenth of 1, no change direction
 * @param a [double*] vector to operade on
 * @return [void]
*/
void	unit(double	*a)
{
	double	d;

	d = 1 / veclen(a);
	a[0] *= d;
	a[1] *= d;
	a[2] *= d;
}
