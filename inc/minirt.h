#ifndef MINIRT_H
# define MINIRT_H

/*
 * DEFINES
 */

# define WDTH 640
# define HGHT 640
# define DIVERGENCE 0.1
# define PI 3.14159265359

/*
**	LIBRARY
*/

# include "../lft/libft.h"
# include "../mlx/mlx.h"

/*
**	INCLUDES
*/

# include <stdio.h>	//  printf, perror
# include <math.h>	//  math lol
# include <fcntl.h> // open
# include <unistd.h> // close, read, write
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

/*
** MACROS
*/

/*
**	STRUCTS
*/

# include "struct.h"

typedef struct s_mrt
{
	void	*mlx;
	void	*win;
	t_al	*al;
	t_lol	*l;
	t_cam	*cam;
	t_sph	*sp;
	t_pl	*pl;
	t_cyl	*cy;
	double	***ray;
}				t_mrt;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_PIxel;
	int		line_length;
	int		endian;
}				t_data;

/*
 * FUNCTIONS
*/

//GEOMETRY-

double	*cross(double *a, double *b);
double	*ray_alloc(double x, double y, double z);
double	veclen(double *a);
double	*connect(double *a, double *b);
void	addto(double *a, double *b);
void	unit(double	*a);
void	product(double *a, double m);
void	resize(double *a, double m);
double	angle(double *a, double *b);

double	calculate_dot(double *a, double *b);

//TRACER

void	init_rays(t_mrt *mrt);
double	hit_sphere(double *point, double radius, double *ray_or, double *ray_dir);
double	plane_intercept(t_mrt *mrt, double *l, t_pl *plane);
double	cylinder_intersect(double *pos, double radius, double height, double *ray_or, double *ray_dir);

//SRC

int		main(int argc, char **argv);

// INPUT

void	*extract_line(char **lines, t_mrt *mrt);

#endif
