#ifndef MINIRT_H
# define MINIRT_H

/*
 * DEFINES
 */

# define RENDER_DISTANCE 20000
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
	t_sph	**sp;
	t_pl	**pl;
	t_cyl	**cy;
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

double	*single_ray(int x, int y, t_cam *cam, double **scr);
double	**scream(t_cam *cam);
void	init_rays(t_mrt *mrt);
double	hit_sphere(double *point, double radius, double *ray_or, double *ray_dir);
double	plane_intercept(t_mrt *mrt, double *l, t_pl *plane);
double	cylinder_intersect(double *pos, double radius, double height, double *ray_or, double *ray_dir);

int	nachfolger(int x, int y, t_mrt *mrt, double **scr);

//SRC

int		main(int argc, char **argv);

// INPUT

void	*extract_line(char **lines, t_mrt *mrt);

//UTILES

int	create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

char	*trm_whtsp(char *s, int dir);
int		is_whspace(char *s, int dir);
int		ft_white(char c);

int		count_input(t_list *lst, int count[6], char *tmp);
int		check_count(int count[6]);

//INITIALIZATION

int		check_deci(char *s);
int		init_cor(char **info, double *cor, int flag);
int		init_rgb(char **info, int *r, int *g, int *b);
int		init_fov(char *info, double *fov);
int		init_dim(char *info, double *dim, int flag);

int		init_al(t_al *al, char **info);
int		init_cam(t_cam *ca, char **info);
int		init_lol(t_lol *l, char **info);
int		init_lol_b(t_lol_b *l, char **info);

int		init_sph(t_sph *sp, char **info);
int		init_pl(t_pl *pl, char **info);
int		init_cyl(t_cyl *cy, char **info);

//FUNCTIONS

int		input(t_mrt *mrt, char *file);

#endif
