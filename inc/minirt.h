#ifndef MINIRT_H
# define MINIRT_H

/*
 * DEFINES
 */

# define wdth 640
# define hght 640

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
	double	***ray[3];
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

//SRC

int		main(int argc, char **argv);

// INPUT

#endif
