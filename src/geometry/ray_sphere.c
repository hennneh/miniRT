#include "../../inc/minirt.h"

/**
 * @brief Return the the distance to the given sphere
 * if it hitting as a double else it return -1
 * 
 * @param point Pointer of type double that save the coordinate
 * 				of the sphere point[3]
 * @param radius Radius of the sphere as double
 * @param ray_or Ray Vector as Pointer of type double ray[3]
 * @param ray_dir
 * 
 * @return Distance to object on this ray vector
 */
double	hit_sphere(double *point, double radius, double *ray_or, double *ray_dir)
{
	double	oc[3];
	double	tmp[3];
	double	disc;

	oc[0] = ray_or[0] - point[0];
	oc[1] = ray_or[1] - point[1];
	oc[2] = ray_or[2] - point[2];
	tmp[0] = calculate_dot(ray_dir, NULL);
	tmp[1] = 2.0 * calculate_dot(oc, ray_dir);
	tmp[2] = calculate_dot(oc, NULL) - radius * radius;
	disc = tmp[1] * tmp[1] - 4 * tmp[0] * tmp[2];
	if (disc < 0)
		return (0);
	else
		return (((tmp[1]) - sqrt(disc)) / (2.0 * tmp[0]));
}


// int main()
// {
// 	double sphere[3] = {-4.49801,1.14318,5.5404};
// 	double radius = 1.5;
// 	double ray_or[3] = {-0.19, 1.82, 1.0};
// 	double ray_dir[3] = {-6,0,7.62242};

// 	double result = hit_sphere(sphere, radius, ray_or, ray_dir);
// 	printf("Calculated result is: %f\n", result);
// }