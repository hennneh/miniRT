#include "../../inc/minirt.h"

/*
 * if the ray vector given to the function times the normal of the plane is equal 
 * to 0, they are in parallel.
 * l * n = 0
 *
 * if some point on the plane and some point on the
 * ray substracted times the normal of the plane are equal to 0 they are on the 
 * same plane and there are infinite intersections. 
 * (p0 - l0) * n = 0
 * ->not relevant for us as the plane won't be displayed if a ray is inside
 * the plane
 *
 * the distance from the origin of a ray to the interception point of a plane
 * is calculated by substracting the origin of the ray from the coordinates of 
 * the plane and multipliyng that result with the normal of the plane. 
 * this then need's to be divided by the product of the vector of the ray and
 * the planes normal.
 * t = ((p0 - l0) * n) / (l * n)
 */

double	plane_intercept(t_mrt *mrt, double *l, t_pl *plane)
{
	double	t;

	t = 0;
	if (!calculate_dot(plane->v_o, l))
		return (0);
	else
	{
		t = (calculate_dot(connect(mrt->cam->cor, plane->cor), plane->v_o)) / calculate_dot(plane->v_o, l);
		if (t > 0)
			return (t);
		return (0);
	}
}
