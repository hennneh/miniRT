/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:28:18 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:28:20 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_obj	*line_obj(t_vec	origin, t_vec direction, char color)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	res->id = 'O';
	res->cor = origin;
	res->v_o = direction;
	res->r = 0;
	res->g = 0;
	res->b = 0;
	if (color == 'r')
		res->r = 255;
	if (color == 'g')
		res->g = 255;
	if (color == 'b')
		res->b = 255;
	return (res);
}

/**
 * add 3 elements to the object list that disply the coordinate center
 * but it also displays the intersection point behinf the camera
*/
void	origin(t_mrt *mrt, int i)
{
	static int	s;
	t_obj		**new;

	while (mrt->obj[i])
		i++;
	new = ft_calloc((i + 4), sizeof(t_obj *));
	i = 0;
	while (mrt->obj[i] && i < (i + 4 - s))
	{
		if (!(s && mrt->obj[i]->id == 'O'))
		new[i] = mrt->obj[i];
		i++;
	}
	if (!s)
	{
		new[i++] = line_obj(init_vec(0, 0, 0), init_vec(0, 0, 1), 'r');
		new[i++] = line_obj(init_vec(0, 0, 0), init_vec(0, 1, 0), 'g');
		new[i++] = line_obj(init_vec(0, 0, 0), init_vec(1, 0, 0), 'b');
		s = 3;
	}
	else
		s = 0;
	free(mrt->obj);
	mrt->obj = new;
	calc(mrt);
}

void	light(t_mrt *mrt, int key)
{
	if (key == 43)
		mrt->l->lr += 0.125;
	if (key == 45)
		mrt->l->lr -= 0.125;
	if (key == 119)
		mrt->l->cor.z += 5;
	if (key == 97)
		mrt->l->cor.x += 5;
	if (key == 115)
		mrt->l->cor.z -= 5;
	if (key == 100)
		mrt->l->cor.x -= 5;
	if (key == 102)
		mrt->l->cor.y += 5;
	if (key == 98)
		mrt->l->cor.y -= 5;
	limit(&mrt->l->lr, 1, 0);
	calc(mrt);
}

void	camera(t_mrt *mrt, int key)
{
	t_vec	*scr;

	scr = scream(mrt->cam);
	unit(&mrt->cam->v_o);
	if (key == 65362)
		addto(&mrt->cam->v_o, v_product(scr[1], -0.2));
	if (key == 65364)
		addto(&mrt->cam->v_o, v_product(scr[1], 0.2));
	if (key == 65361)
		addto(&mrt->cam->v_o, v_product(scr[0], -0.2));
	if (key == 65363)
		addto(&mrt->cam->v_o, v_product(scr[0], 0.2));
	if (key == 228)
		mrt->cam->fov = mrt->cam->fov + (10 * (PI / 180));
	if (key == 35)
		mrt->cam->fov = mrt->cam->fov - (10 * (PI / 180));
	limit(&mrt->cam->fov, 179 * (PI / 180), 0);
	unit(&mrt->cam->v_o);
	calc(mrt);
	free(scr);
}

void	move(t_mrt *mrt, int key)
{
	if (key == 105)
		mrt->cam->cor.z += 5;
	if (key == 107)
		mrt->cam->cor.z -= 5;
	if (key == 106)
		mrt->cam->cor.x += 5;
	if (key == 108)
		mrt->cam->cor.x -= 5;
	if (key == 252)
		mrt->cam->cor.y -= 5;
	if (key == 246)
		mrt->cam->cor.y += 5;
	calc(mrt);
}
