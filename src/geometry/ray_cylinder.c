#include "../../inc/minirt.h"

double	cylinder_intersect(double *pos, double *dir, double radius, double height, double *ray_or, double *ray_dir)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	a = (ray_dir[0] * ray_dir[0]) + (ray_dir[1] * ray_dir[1]);
	b = 2 * (ray_dir[0] * ray_or[0] + ray_dir[1] * ray_or[1]);		//(ray_dir[0] * (ray_or[0] - pos[0]) + ray_dir[2] * (ray_or[2] - pos[2]));
	c = ray_or[0] * ray_or[0] + ray_or[1] * ray_or[1] - radius*radius;				//(ray_or[0] - pos[0]) * (ray_or[0] - pos[0]) + (ray_or[2] - pos[2]) * (ray_or[2] - pos[2]) - (radius * radius);
	delta = b * b - 4 * (a * c);
	if (fabs(delta) < 0.001)
	{
		printf(".");
		return (-1.0);
	}
	//if (delta < 0.0) return -1.0;
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t1 < t2 && t2 < 0)
		t1 = t2;
	//return t1;
	t2 = ray_or[2] + t1 * ray_dir[2];
	if (t2 >= pos[2] && t2 <= pos[2] + height/2)
		return (t1);
	else
		return (-1.0);
}

double	*normalize(double *vector)
{
	double	len;
	double	*v;

	v = malloc(sizeof(double) * 3);
	len = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	v[0] = vector[0] / len;
	v[1] = vector[1] / len;
	v[2] = vector[2] / len;
	return (v);
}

double	*get_vector(double *point_one, double *point_two)
{
	double	*vec;

	vec = malloc(sizeof(double) * 3);
	vec[0] = point_two[0] - point_one[0];
	vec[1] = point_two[1] - point_one[1];
	vec[2] = point_two[2] - point_one[2];
	return (vec);
}

void	cylinder_coefficient(double *pos, double *dir, double *a, double *ray_or, double *ray_dir)
{
	double	*v;
	double	*n;
	double	*a;

	n = normalize(dir);
	v = get_vector(pos, ray_or);
	a = malloc(sizeof(double) * 3);
	a[0] = ;
	a[1] = ;
	a[2] = ;
	free(n);
	free(v);
}

double	new_cylinder_intersect()
{
	
}
