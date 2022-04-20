#include "../../inc/minirt.h"

double	cylinder_intersect(double *pos, double radius, double height, double *ray_or, double *ray_dir)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	a = (ray_dir[0] * ray_dir[0]) + (ray_dir[2] * ray_dir[2]);
	b = 2 * (ray_dir[0] * (pos[0] * ray_or[0]) + ray_dir[2] * (pos[2] * ray_or[2]));
	c = (pos[0] - ray_dir[0]) * (pos[0] - ray_or[0]) + (pos[2] - ray_or[2]) * (pos[2] - ray_or[2]) - (radius * radius);
	delta = b * b - 4 * (4 * c);
	if (fabs(delta) < 0.001 | delta < 0.0)
		return (-1.0);
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t1 > t2)
		t1 = t2;
	t2 = pos[1] + t1 * ray_dir[1];
	if (r >= ray_or[1] && r <= ray_or[1] + height)
		return (t1);
	else
		return (-1);
}