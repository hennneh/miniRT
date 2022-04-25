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
	t_obj	**obj;
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

//SRC

int		main(int argc, char **argv);

// EXIT

void	rt_er_exit(t_mrt *mrt, int good, int count);
// INPUT

void	*extract_line(char **lines, t_mrt *mrt);//proto

//UTILES

char	*trm_whtsp(char *s, int dir);
int		is_whspace(char *s, int dir);
int		ft_white(char c);
char	**split_wh(char const *s);

int		count_input(t_list *lst, int *count, char *tmp);
int		check_count(int *count);

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

int		init_sph(t_obj **sp, char **info, int p);
int		init_pl(t_obj **pl, char **info, int p);
int		init_cyl(t_obj **cy, char **info, int p);

//FUNCTIONS

int		input(t_mrt *mrt, char *file);

#endif
