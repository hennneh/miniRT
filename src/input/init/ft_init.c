/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:29:55 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:29:56 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minirt.h"

/**
 * checks how many decimals a string has
 * @param s [char *] string to be checked
 * @return [int] number of decimals
*/
int	check_deci(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '.')
			count ++;
		i ++;
	}
	return (count);
}

/**
 * Function to initilize the double[3] array
 * @param info [char **] information split by ','
 * @param cor [double *[3]] pointer to the double array
 * @param flag [int] 0 if x,y,z, cor; 1 if v_o
 * @return [int] 0 if succesful; 1 if error;
*/
int	init_cor(char **info, t_vec *cor, int flag)
{
	int		i;
	double	tmp[3];

	ft_bzero(cor, 3 * sizeof(double));
	i = 0;
	while (info[i])
	{
		if (i > 2 || check_deci(info[i]) > 1 || ft_isdouble(info[i]))
			return (free_2dstr(info) + 1);
		tmp[i] = ft_atof(info[i]);
		if (flag == 1 && (tmp[i] < -1 || tmp[i] > 1))
			return (free_2dstr(info) + 1);
		i ++;
	}
	cor->x = tmp[0];
	cor->y = tmp[1];
	cor->z = tmp[2];
	if (i != 3)
		return (free_2dstr(info) + 1);
	return (free_2dstr(info));
}

/**
 * initializes the R,G,B; Checks that in int is inside the range
 * @param info [char **] information split by ','
 * @param r [int *] point to the r value
 * @param g [int *] point to the g value
 * @param b [int *] point to the b value
 * @return [int] 0 if succesful; 1 if error;
*/
int	init_rgb(char **info, int *r, int *g, int *b)
{
	int	i;
	int	tmp;

	i = 0;
	*r = -1;
	*g = -1;
	*b = -1;
	while (info[i])
	{
		if (i > 2 || ft_isnumeric(info[i]))
			return (free_2dstr(info) + 1);
		tmp = ft_atoi(info[i]);
		if (tmp < 0 || tmp > 255)
			return (free_2dstr(info) + 1);
		if (i == 0)
			*r = tmp;
		if (i == 1)
			*g = tmp;
		if (i == 2)
			*b = tmp;
		i ++;
	}
	if (i != 3)
		return (free_2dstr(info) + 1);
	return (free_2dstr(info));
}

/**
 * initializes the Field of view; Checks that the double is inside the range
 * @param info [char *] information string
 * @param fov [double *] point to the fov double
 * @return [int] 0 if succesful; 1 if error;
*/
int	init_fov(char *info, double *fov)
{
	double	tmp;

	*fov = -1.0;
	if (ft_isdouble(info) || check_deci(info) > 1)
		return (1);
	tmp = ft_atof(info);
	if (tmp < 0 || tmp > 180)
		return (1);
	*fov = (tmp * (PI / 180.0));
	return (0);
}

/**
 * initializes the dimensions; Checks that the double is valid
 * @param info [char *] information string
 * @param dim [double *] point to the dimension double
 * @param flag [int] 0 if hight; 1 if diameter; 2 if brigh ratio
 * @return [int] 0 if succesful; 1 if error;
*/
int	init_dim(char *info, double *dim, int flag)
{
	*dim = -1.0;
	if (ft_isdouble(info) || check_deci(info) > 1)
		return (1);
	*dim = ft_atof(info);
	if (*dim < 0)
		return (1);
	if (flag == 1)
		*dim = *dim / 2;
	if (flag == 2 && (*dim < 0.0 || *dim > 1.0))
		return (1);
	return (0);
}
