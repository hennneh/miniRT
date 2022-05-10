#include "../inc/minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	color(t_mrt *mrt, t_obj *near, char c)
{
	double	alp;
	double	lp;

	alp = mrt->al->lr / (mrt->al->lr + mrt->l->lr);
	lp = mrt->l->lr / (mrt->al->lr + mrt->l->lr);
	if (c == 'r')
		return (mrt->al->r * alp + near->r * lp);
	if (c == 'g')
		return (mrt->al->g * alp + near->g * lp);
	if (c == 'b')
		return (mrt->al->b * alp + near->b * lp);
	return (0);
}

int	shadow_color(t_mrt *mrt, t_obj *near, char c)
{
	double	alp;

	alp = mrt->al->lr / (mrt->al->lr + mrt->l->lr);
	if (c == 'r')
		return (mrt->al->r * alp + near->r * SHADOW);
	if (c == 'g')
		return (mrt->al->g * alp + near->g * SHADOW);
	if (c == 'b')
		return (mrt->al->b * alp + near->b * SHADOW);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	limit(double *var, double upper, double lower)
{
	if (*var > upper)
		*var = upper;
	if (*var < lower)
		*var = lower;
}
