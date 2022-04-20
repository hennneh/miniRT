
#include "../rt_input.h"

/**
 * initilzes a sphere struct
 * @param sp [t_sph] sphere struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_sph(t_sph *sp, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		sp->id = 'S';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &sp->cor, 0))
		return (1);
	if (!info[i] || init_dim(info[i ++], &sp->rad, 1))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &sp->r, &sp->g, &sp->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}

/**
 * initilzes a Plane struct with bonus RGB
 * @param l [t_pl *]plane struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_pl(t_pl *pl, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		pl->id = 'P';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &pl->cor, 0))
		return (1);
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &pl->v_o, 1))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &pl->r, &pl->g, &pl->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}

/**
 * initilzes a cylinder struct
 * @param cy [t_cyl ] Cylinder struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_cyl(t_cyl *cy, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		cy->id = 'Z';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &cy->cor, 0))
		return (1);
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &cy->v_o, 1))
		return (1);
	if (!info[i] || init_dim(info[i ++], &cy->rad, 1))
		return (1);
	if (!info[i] || init_dim(info[i ++], &cy->hght, 0))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &cy->r, &cy->g, &cy->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}
