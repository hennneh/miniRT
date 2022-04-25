#include "../../inc/minirt.h"

double	cylinder_intersect(double *pos, double *dir, double radius, double height, double *ray_or, double *ray_dir)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;

	(void) dir;
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
	if (t2 >= pos[2] && t2 <= pos[2] + height)
		return (t1);
	else
		return (-1.0);
}

double	newer_cylinder_intersect(double *pos, double *dir, double radius, double height, double *ray_or, double *ray_dir)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t1;
	double	t2;
	double	tmp[3];

	(void) dir;
	// a = (ray_dir[0] * ray_dir[0]) + (ray_dir[1] * ray_dir[1]);
	// b = 2 * (ray_dir[0] * ray_or[0] + ray_dir[1] * ray_or[1]);		//(ray_dir[0] * (ray_or[0] - pos[0]) + ray_dir[2] * (ray_or[2] - pos[2]));
	// c = ray_or[0] * ray_or[0] + ray_or[1] * ray_or[1] - radius*radius;				//(ray_or[0] - pos[0]) * (ray_or[0] - pos[0]) + (ray_or[2] - pos[2]) * (ray_or[2] - pos[2]) - (radius * radius);
	cylinder_coefficient(pos, dir, radius, tmp, ray_or, ray_dir);
	a = tmp[0];
	b = tmp[1];
	c = tmp[2];
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
	if (t2 >= pos[2] && t2 <= pos[2] + height)
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

void	cylinder_coefficient(double *pos, double *dir, double radius, double *tmp, double *ray_or, double *ray_dir)
{
	double	*v;
	double	*n;

	n = normalize(dir);
	v = get_vector(pos, ray_or);
	
	tmp[0] = 1 - pow(calculate_dot(ray_dir, n), 2);
	tmp[1] = 2 * (calculate_dot(ray_dir, n) - calculate_dot(ray_dir, dir) * calculate_dot(dir, v));
	tmp[2] = calculate_dot(v, NULL) - pow(calculate_dot(v, n), 2) - pow(radius, 2);
	free(n);
	free(v);
	tmp[3] = pow(tmp[1], 2) - 4 * tmp[0] * tmp[2];
}

double	new_cylinder_intersect(double *pos, double *dir, double radius, double height, double *ray_or, double *ray_dir)
{
	double	t[2];
	double	*tmp;

	(void) height;
	tmp = malloc(sizeof(double) * 4);
	cylinder_coefficient(pos, dir, radius, tmp, ray_or, ray_dir);
	if (tmp[3] < 0)
	{
		free(tmp);
		// printf(".");
		return (-1.0);
	}
	//printf("|");
	t[0] = (-tmp[1] - sqrt(tmp[3])) / (2 * tmp[0]);
	if (t[0] < 0)
		t[0] = (-tmp[1] + sqrt(tmp[3])) / (2 * tmp[0]);
	double	h[3];
	h[0] = ray_dir[0] * t[0] + ray_or[0] - pos[0];
	h[1] = ray_dir[1] * t[0] + ray_or[1] - pos[1];
	h[2] = ray_dir[2] * t[0] + ray_or[2] - pos[2];
	t[1] = calculate_dot(dir, h);
	free(tmp);
	if (t[1] < 0 || t[1] > height)
	{
		//printf("Value t[1] = %f\n", t[1]);
		return (0);
	}
	return(t[0]);

}
