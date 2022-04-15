
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
