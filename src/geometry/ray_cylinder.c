#include "../../inc/minirt.h"

#define EPSILON 0.00001

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

double	*get_vector(double *point_one, double *point_two)
{
	double	*vec;

	vec = malloc(sizeof(double) * 3);
	vec[0] = point_two[0] - point_one[0];
	vec[1] = point_two[1] - point_one[1];
	vec[2] = point_two[2] - point_one[2];
	return (vec);
}

t_vec	vec_product(t_vec a, double m)
{
	t_vec	res;

	res.x = a.x * m;
	res.y = a.y * m;
	res.z = a.z * m;
	return (res);
}

void	cylinder_coefficient(t_vec *pos, t_vec *dir, double radius, double *x, t_vec *ray_or, t_vec *ray_dir)
{
	t_vec	v;
	t_vec	u;
	t_vec	normalized;
	t_vec	dir;

	normalized = *dir;
	unit(&normalized);
	v = vec_product(normalized, calculate_dot(ray_dir, &normalized));
	u = vec_product(normalized, calculate_dot(ray_or, pos));
	u = connect(u, connect(*pos, *ray_or));
	double a = calculate_dot(&v, &v);//1 - pow(calculate_dot(ray_dir, n), 2);
	double b = 2 * calculate_dot(&v, &u);
	double c = calculate_dot(&u, &u) - pow(radius, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) - (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) - (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

double	new_cylinder_intersect(t_vec *pos, t_vec *dir, double radius, double height, t_vec *ray_or, t_vec *ray_dir)
{
	double	x[2];
	double	dist[2];
	t_vec	normalized;

	normalized = *dir;
	dist[0] = calculate_dot();

}
