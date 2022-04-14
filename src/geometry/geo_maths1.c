#include "../../inc/minirt.h"

/**
 * @brief Return the dot calculations of two Vectors
 * 
 * @param a Pointer of type double
 * @param b Pointer of type double
 * @return double
 */
double	calculate_dot(double *a, double *b)
{
	double	dot;

	if (b != NULL)
		dot = a[0] * b[0] + a[1] * b[1] + a[2] + b[2];
	else
		dot = a[0] * a[0] + a[1] * a[1] + a[2] + a[2];
	return (dot);
}