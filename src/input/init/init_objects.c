
#include "../../../inc/minirt.h"

/**
 * initilzes a sphere struct
 * @param ob [t_obj **] sphere struct
 * @param info [char **] information line split by whitespace
 * @param p [int] position in array
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_sph(t_obj **sp, char **info, int p)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	sp[p] = ft_calloc(sizeof(t_obj), 1);
	sp[p]->id = 'S';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), sp[p]->cor, 0))
		return (1);
	if (!info[i] || init_dim(info[i ++], &sp[p]->rad, 1))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &sp[p]->r, &sp[p]->g, &sp[p]->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}

/**
 * initilzes a Plane struct with bonus RGB
 * @param l [t_obj **]object struct
 * @param info [char **] information line split by whitespace
 * @param p [int] position in array
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_pl(t_obj **pl, char **info, int p)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	pl[p] = ft_calloc(sizeof(t_obj), 1);
	pl[p]->id = 'P';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), pl[p]->cor, 0))
		return (1);
	if (!info[i] || init_cor(ft_split(info[i ++], ','), pl[p]->v_o, 1))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &pl[p]->r, &pl[p]->g, &pl[p]->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}

/**
 * initilzes a cylinder struct
 * @param cy [t_obj **] Cylinder struct
 * @param info [char **] information line split by whitespace
 * @param p [int] position in array
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_cyl(t_obj **cy, char **info, int p)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	cy[p] = ft_calloc(sizeof(t_obj), 1);
	cy[p]->id = 'Z';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), cy[p]->cor, 0))
		return (1);
	if (!info[i] || init_cor(ft_split(info[i ++], ','), cy[p]->v_o, 1))
		return (1);
	if (!info[i] || init_dim(info[i ++], &cy[p]->rad, 1))
		return (1);
	if (!info[i] || init_dim(info[i ++], &cy[p]->hght, 0))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &cy[p]->r, &cy[p]->g, &cy[p]->b))
		return (1);
	if (info[i])
		return (1);
	return (0);
}
