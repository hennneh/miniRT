
#include "../../../inc/minirt.h"

/**
 * initilzes a Ambient Light struct
 * @param al [t_al *] ambient light struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_al(t_al *al, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		al->id = 'A';
	if (!info[i] || init_dim(info[i ++], &al->lr, 2))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &al->r, &al->g, &al->b))
		return (1);
	if (info[i])
		return (1);
	// printf("good ambient light\n");//DELETE
	return (0);
}

/**
 * initilzes a Camara struct
 * @param ca [t_cam] Camera struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_cam(t_cam *ca, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		ca->id = 'K';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &ca->cor, 0))
		return (1);
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &ca->v_o, 1))
		return (1);
	if (!info[i] || init_fov(info[i ++], &ca->fov))
		return (1);
	if (info[i])
		return (1);
	if (ca->v_o.x == 0.0 && ca->v_o.y == 0.0 && ca->v_o.z == 0.0)
		ca->v_o.x = 1.0;
	// printf("good Camera\n");//DELETE
	return (0);
}

/**
 * initilzes a Light struct
 * @param l [t_lol *] light struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_lol(t_lol *l, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		l->id = 'L';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &l->cor, 0))
		return (1);
	if (!info[i] || init_dim(info[i ++], &l->lr, 2))
		return (1);
	if (info[i])
		return (1);
	// printf("good light\n");//DELETE
	return (0);
}

/**
 * initilzes a Light struct with bonus RGB
 * @param l [t_lol_b *] light bonus struct
 * @param info [char **] information line split by whitespace
 * @return [int] 0 if successful; 1 if error in line
*/
int	init_lol_b(t_lol_b *l, char **info)
{
	int	i;

	i = 1;
	if (!info || !info[0])// check the indentifyer ??
		return (1);
	else
		l->id = 'l';
	if (!info[i] || init_cor(ft_split(info[i ++], ','), &l->cor, 0))
		return (1);
	if (!info[i] || init_dim(info[i ++], &l->brit, 2))
		return (1);
	if (!info[i] || init_rgb(ft_split(info[i ++], ','), &l->r, &l->g, &l->b))
		return (1);
	if (info[i])
		return (1);
	// printf("good light bonus\n");//DELETE
	return (0);
}
