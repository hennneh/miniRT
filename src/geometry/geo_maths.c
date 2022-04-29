#include "../../inc/minirt.h"

/**
 * @brief return a vector orthogonal to both the given vectors
 * @param a [double*]
 * @param b [double*]
 * @return [double*]
*/
double	*cross(double *a, double *b)
{
	if (!a || !b)
		return(NULL);
	double	*res;

	res = malloc(3 * sizeof(double));
	res[0] = (a[1] * b[2]) - (a[2] * b[1]);
	res[1] = (a[2] * b[0]) - (a[0] * b[2]);
	res[2] = (a[0] * b[1]) - (a[1] * b[0]);
	unit(res);
	return (res);
}

double	*ray_alloc(double x, double y, double z)
{
	double	*res;

	res = malloc(3 * sizeof(double));
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
double	*connect(double *a, double *b)
{
	if (!a || !b)
		return(NULL);
	double	*res;

	res = malloc(3 * sizeof(double));
	res[0] = b[0] - a[0];
	res[1] = b[1] - a[1];
	res[2] = b[2] - a[2];
	return (res);
}

/**
 * @brief add a two vectors together
 * @param a [double*] the vector being added to
 * @param b [double*] the vector to add
*/
void	addto(double *a, double *b)
{
	if (!a || !b)
		return ;
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
	if (!a)
		return ;
	a[0] *= m;
	a[1] *= m;
	a[2] *= m;
}

/**
 * @brief add a set distance to a vector
 * @param a [double*] the vector
 * @param m [double] to be added length
*/
void	resize(double *a, double m)
{
	double	o[3];

	if (!a)
		return ;
	o[0] = a[0];
	o[1] = a[1];
	o[2] = a[2];
	unit(o);
	product(o, m);
	addto(a, o);
}

/**
 * @brief change a vecto to have the total lenth of 1, no change direction
 * @param a [double*] vector to operade on
 * @return [void]
*/
void	unit(double	*a)
{
	if (!a)
		return ;
	double	d;

	d = 1 / veclen(a);
	a[0] *= d;
	a[1] *= d;
	a[2] *= d;
}
/**
 * @brief calculate the angle between two vectors
 * @param a [double*]
 * @param b [double*]
*/
double	angle(double *a, double *b)
{
	double scalar;

	if (!a || !b)
		return(0);
	scalar = calculate_dot(a, b);
	return (acos((scalar / (veclen(a) * veclen(b)))));
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
double	*reflect(double in[3], double norm[3])
{
	double	*tmp;
	double	*tang;
	double	*res;

	unit(in);
	tmp = cross(in, norm);
	tang = cross(tmp, norm);
	free(tmp);
	unit(tang);
	product(tang, -2 * cos(angle(in, tang)));
	res = connect(in, tang);
	return (res);
}
