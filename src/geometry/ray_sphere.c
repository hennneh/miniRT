#include "../../inc/minirt.h"

/**
 * @brief Return the the distance to the given sphere
 * if it hitting as a double else it return -1
 * 
 * @param sph_org Pointer of type double that save the coordinate
 * 				of the sphere point[3]
 * @param sph_rad Radius of the sphere as double
 * @param ray_or Ray Vector as Pointer of type double ray[3]
 * @param ray_dir
 * 
 * @return Distance to object on this ray vector
 */
double	hit_sphere(t_vec sph_org, double sph_rad, t_vec ray_or, t_vec ray_dir)
{
	t_vec	oc;
	t_vec	tmp;
	double	disc;

	oc.x = ray_or.x - sph_org.x;
	oc.y = ray_or.y - sph_org.y;
	oc.z = ray_or.z - sph_org.z;
	tmp.x = calculate_dot(&ray_dir, NULL);
	tmp.y = 2.0 * calculate_dot(&oc, &ray_dir);
	tmp.z = calculate_dot(&oc, NULL) - sph_rad * sph_rad;
	disc = tmp.y * tmp.y - 4 * tmp.x * tmp.z;
	if (disc < 0)
		return (0);
	else
		return (-1 *((tmp.y) - sqrt(disc)) / (2.0 * tmp.x));
}


// int main()
// {
// 	double sphere[3] = {-4.49801,1.14318,5.5404};
// 	double sph_rad = 1.5;
// 	double ray_or[3] = {-0.19, 1.82, 1.0};
// 	double ray_dir[3] = {-6,0,7.62242};

// 	double result = hit_sphere(sphere, sph_rad, ray_or, ray_dir);
// 	printf("Calculated result is: %f\n", result);
// }