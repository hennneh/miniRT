#include "../../inc/minirt.h"

#define EPSILON 0.00001

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

int	cylinder_coefficient(t_vec *pos, t_vec *dir, double radius, double *x, t_vec *ray_or, t_vec *ray_dir)
{
	t_vec	v;
	t_vec	u;
	t_vec	normalized;

	normalized = *dir;
	unit(&normalized);
	v = vec_product(normalized, calculate_dot(ray_dir, &normalized));
	v = connect(v, *ray_dir);
	t_vec tmp = connect(*pos, *ray_or);
	u = vec_product(normalized, calculate_dot(&tmp, &normalized));
	u = connect(u, connect(*pos, *ray_or));
	double a = calculate_dot(&v, &v);
	double b = 2 * calculate_dot(&v, &u);
	double c = calculate_dot(&u, &u) - pow(radius, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

t_vec	calc_cy_normal(double *x, t_vec pos, t_vec dir, double *dist, t_vec ray_or, t_vec ray_dir, double height)
{
	double	d;
	double	t;
	t_vec	normalized;

	normalized = dir;
	unit(&normalized);
	if ((dist[0] >= 0 && dist[0] <= height && x[0] > EPSILON) && (dist[1] >= 0 && dist[1] <= height && x[1] > EPSILON))
	{
		d = x[0] < x[1] ? dist[0] : dist[1];
		t = x[0] < x[1] ? x[0] : x[1];
	}
	else if(dist[0] >= 0 && dist[0] <= height && x[0] > EPSILON)
	{
		d = dist[0];
		t = x[0];
	}
	else
	{
		d = dist[1];     
		t = x[1];
	}
	x[0] = t;
	t_vec	tmp = connect(connect(ray_or, pos), connect(vec_product(normalized, d), vec_product(ray_dir, t)));
	unit(&tmp);
	return (tmp);
}

t_vec	new_pos(t_vec *posi, t_vec *dir, double height, t_vec *norm)
{
	t_vec	pos;

	*norm = *dir;
	unit(norm);
	pos.x = posi->x - (norm->x * (height / 2));
	pos.y = posi->y - (norm->y * (height / 2));
	pos.z = posi->z - (norm->z * (height / 2));
	return (pos);
}

double	new_cylinder_intersect(t_vec *posi, t_vec *dir, double radius, double height, t_vec *ray_or, t_vec *ray_dir)
{
	double	x[2];
	double	dist[2];
	t_vec	normalized;
	t_vec	pos;
	t_vec	helper;

	pos = new_pos(posi, dir, height, &normalized);
	if (cylinder_coefficient(&pos, dir, radius, x, ray_or, ray_dir) == 0)
		return (0);
	helper = connect(connect(*ray_or, pos), vec_product(*ray_dir, x[0]));
	dist[0] = calculate_dot(&normalized, &helper);
	helper = connect(connect(*ray_or, pos), vec_product(*ray_dir, x[1]));
	dist[1] = calculate_dot(&normalized, &helper);
	if (!((dist[0] >= 0 && dist[0] <= height && x[0] > EPSILON) || (dist[1] >= 0 && dist[1] <= height && x[0] > EPSILON)))
		return (0);
	calc_cy_normal(x, pos, *dir, dist, *ray_or, *ray_dir, height);
	return (x[0]);
}

double	hit_cylinder(t_obj cyl, t_vec ray_or, t_vec ray_dir)
{
	double	cylinder_inter;

	cylinder_inter = new_cylinder_intersect(&cyl.cor, &cyl.v_o, cyl.rad, cyl.hght, &ray_or, &ray_dir);
	// limit(&cylinder_inter, RENDER_DISTANCE, 0);
	return (cylinder_inter);
}

// t_vec	vsubstract(t_vec a, t_vec b)
// {
// 	t_vec	p;

// 	p.x = a.x - b.x;
// 	p.y = a.y - b.y;
// 	p.z = a.z - b.z;
// 	return (p);
// }

// double		dot(t_vec a, t_vec b)
// {
// 	return (a.x * b.x + a.y * b.y + a.z * b.z);
// }

// double	solve_plane(t_vec o, t_vec d, t_vec plane_p, t_vec plane_nv)
// {
// 	double	x;
// 	double	denom;

// 	denom = dot(plane_nv, d);
// 	if (denom == 0)
// 		return (INFINITY);
// 	x = (dot(plane_nv, vsubstract(plane_p, o))) / denom;
// 	return (x > 0 ? x : INFINITY);
// }

// t_vec	vadd(t_vec a, t_vec b)
// {
// 	t_vec	p;

// 	p.x = a.x + b.x;
// 	p.y = a.y + b.y;
// 	p.z = a.z + b.z;
// 	return (p);
// }

// t_vec		scal_x_vec(double n, t_vec p)
// {
// 	t_vec	v;

// 	v.x = n * p.x;
// 	v.y = n * p.y;
// 	v.z = n * p.z;
// 	return (v);
// }

// double		distance(t_vec p1, t_vec p2)
// {
// 	double d;

// 	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
// 	return (d);
// }

// double	caps_intersection(t_vec *posi, t_vec *dir, double radius, double height, t_vec *ray_or, t_vec *ray_dir)
// {
// 	double	id1;
// 	double	id2;
// 	t_vec	ip1;
// 	t_vec	ip2;
// 	t_vec	c2;

// 	c2 = vadd(*ray_or, scal_x_vec(height, *dir));	//gotta add normvec herre!!!!!!
// 	id1 = solve_plane(*ray_or, *ray_dir, *posi, *dir);//gotta add normvec herre!!!!!!
// 	id2 = solve_plane(*ray_or, *ray_dir, c2, *dir);  //gotta add normvec herre!!!!!!
// 	if (id1 < INFINITY || id2 < INFINITY)
// 	{
// 		ip1 = vadd(*ray_or, scal_x_vec(id1, *ray_dir));
// 		ip2 = vadd(*ray_or, scal_x_vec(id2, *ray_dir));
// 		if ((id1 < INFINITY && distance(ip1, *posi) <= radius) && (id2 < INFINITY && distance(ip2, c2) <= radius))
// 			return (id1 < id2 ? id1 : id2);
// 		else if (id1 < INFINITY && distance(ip2, c2) <= radius)
// 			return (id1);
// 		else if (id2 < INFINITY && distance(ip2, c2) <= radius)
// 			return (id2);
// 		return (INFINITY);
// 	}
// 	return (INFINITY);
// }

// double	hit_cylinder(t_vec *posi, t_vec *dir, double radius, double height, t_vec *ray_or, t_vec *ray_dir)
// {
// 	double	cylinder_inter;
// 	double	caps_inter;

// 	cylinder_inter = new_cylinder_intersect(posi, dir, radius, height, ray_or, ray_dir);
// 	caps_inter = caps_intersection(posi, dir, radius, height, ray_or, ray_dir);
// 	if (cylinder_inter > 0 || caps_inter > 0)
// 	{
// 		if (cylinder_inter < caps_inter)
// 			return (cylinder_inter);
// 		else
// 			return (caps_inter);
// 	}
// 	return (0);
// }

