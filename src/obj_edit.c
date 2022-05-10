#include "../inc/minirt.h"

size_t	ft_pointlen(t_obj **str)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
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

double	hell(t_vec *norm, t_vec *light, t_vec *ray)
{
	double	s[2];

	s[0] = calculate_dot(norm, light);
	s[1] = calculate_dot(norm, ray);
	if (s[0] < 0)
		*norm = init_vec(-((*norm).x), -((*norm).y), -((*norm).z));
	if ((s[0] < 0 && s[1] < 0) || (s[0] >= 0 && s[1] >= 0))
		return (1);
	return (0);
}