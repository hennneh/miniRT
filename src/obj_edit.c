#include "../inc/minirt.h"

size_t	ft_pointlen(t_obj **str)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
		if (str[i]->id == 'P')
			res += 2;
		if (str[i]->id == 'Z')
			res += 4;
		i++;
		res++;
	}
	return (res);
}

t_obj	*circle_obj(t_obj cyl, double dst)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	res->id = 'C';
	res->cor = v_sum(cyl.cor, v_product(v_unit(cyl.v_o), dst));
	if (dst > 0)
		res->v_o = cyl.v_o;
	else
		res->v_o = v_invert(cyl.v_o);
	res->r = cyl.r;
	res->g = cyl.g;
	res->b = cyl.b;
	res->rad = cyl.rad;
	return (res);
}

void	expand_obj(t_mrt *mrt)
{
	int		i;
	int		e;
	t_obj	**new;

	i = 0;
	e = 0;
	e = ft_pointlen(mrt->obj);
	new = ft_calloc(e + 1, sizeof(t_obj *));
	i = 0;
	e = 0;
	while (mrt->obj[i])
	{
		if (mrt->obj[i]->id != 'Z')
			new[i + e] = mrt->obj[i];
		else
		{
			new[i + e++] = mrt->obj[i];
			new[i + e++] = circle_obj(*mrt->obj[i], mrt->obj[i]->hght / 2);
			new[i + e] = circle_obj(*mrt->obj[i], mrt->obj[i]->hght / -2);
		}
		i++;
	}
	free(mrt->obj);
	mrt->obj = new;
}

int	obj_count(t_obj **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		i++;
	return (i);
}

void	flip(t_mrt *mrt)
{
	int	i;
	int	limit;
	int	pos;

	i = 0;
	limit = obj_count(mrt->obj);
	while (mrt->obj[i] && i < limit)
	{
		if (mrt->obj[i]->id == 'P' || mrt->obj[i]->id == 'C')
		{
			pos = obj_count(mrt->obj);
			mrt->obj[pos] = malloc(sizeof(t_obj));
			mrt->obj[pos]->cor = mrt->obj[i]->cor;
			mrt->obj[pos]->v_o = v_invert(mrt->obj[i]->v_o);
			mrt->obj[pos]->id = mrt->obj[i]->id;
			mrt->obj[pos]->r = mrt->obj[i]->r;
			mrt->obj[pos]->g = mrt->obj[i]->g;
			mrt->obj[pos]->b = mrt->obj[i]->b;
		}
		i++;
	}
}
