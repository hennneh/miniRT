#ifndef MINIRT_H
# define MINIRT_H

/*
 * DEFINES
 */

# define wdth 640
# define hght 640
# define divergence 0.1
# define pi 3.14159265359

/*
**	LIBRARY
*/

# include "../lft/libft.h"
# include "../mlx/mlx.h"

/*
**	INCLUDES
*/

# include <stdio.h>	//  printf
# include <math.h>	//  math lol
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>	//  open

/*
** MACROS
*/

/*
**	STRUCTS
*/

#include "struct.h"

typedef struct s_mrt
{
	void	*mlx;
	void	*win;
	t_al	*al;
	t_lol	*l;
	t_cam	*cam;
	t_sph	**sp;
	t_pl	**pl;
	t_cyl	**cy;
	double	***ray;
}				t_mrt;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
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

//TRACER

void	init_rays(t_mrt *mrt);

//SRC

int		main(int argc, char **argv);

// INPUT

#endif
