
void	limit(double *var, double upper, double lower)
{
	if (*var > upper)
		*var = upper;
	if (*var < lower)
		*var = lower;
}

void	calc(t_mrt *mrt)
{
	int		cord[2];
	t_vec	*scr;

	scr = scream(mrt->cam);
	mrt->img.img = mlx_new_image(mrt->mlx, WDTH, HGHT);
	mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bits_per_pixel, \
	&mrt->img.line_length, &mrt->img.endian);
	cord[1] = 0;
	while (cord[1] < HGHT)
	{
		cord[0] = 0;
		while (cord[0] < WDTH)
		{
			nachfolger(cord, mrt, scr, FALSE);
			cord[0]++;
		}
		cord[1]++;
	}
	free(scr);
}

void	light(t_mrt *mrt, int key)
{
	if (key == 43)
		mrt->l->lr *= 1.125;
	if (key == 45)
		mrt->l->lr *= 0.875;
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

void	print_object(t_obj *obj)
{
	if (obj->id == 'S')
		printf("%s %lf,%lf,%lf %lf %i,%i,%i\n", "sp", obj->cor.x, \
		obj->cor.y, obj->cor.z, obj->rad * 2, \
		obj->r, obj->g, obj->b);
	if (obj->id == 'P')
		printf("%s %lf,%lf,%lf %lf,%lf,%lf %i,%i,%i\n", "pl", \
		obj->cor.x, obj->cor.y, obj->cor.z, \
		obj->v_o.x, obj->v_o.y, obj->v_o.z, \
		obj->r, obj->g, obj->b);
	if (obj->id == 'Z')
		printf("%s %lf,%lf,%lf %lf,%lf,%lf %lf %lf %i,%i,%i\n", "cy", \
		obj->cor.x, obj->cor.y, obj->cor.z, \
		obj->v_o.x, obj->v_o.y, obj->v_o.z, \
		obj->rad * 2, obj->hght, obj->r, \
		obj->g, obj->b);
}

void	print_config(t_mrt *mrt, int i)
{
	printf("%c %lf %i,%i,%i\n", 'A', mrt->al->lr, mrt->al->r, mrt->al->g, \
	mrt->al->b);
	printf("%c %lf,%lf,%lf %lf,%lf,%lf %lf\n", 'C', mrt->cam->cor.x, \
	mrt->cam->cor.y, mrt->cam->cor.z, mrt->cam->v_o.x, mrt->cam->v_o.y, \
	mrt->cam->v_o.z, mrt->cam->fov * (180 / PI));
	printf("%c %lf,%lf,%lf %lf\n", 'L', mrt->l->cor.x, mrt->l->cor.y, \
	mrt->l->cor.z, mrt->l->lr);
	while (mrt->obj[i])
	{
		print_object(mrt->obj[i]);
		i++;
	}
}

void	controls(void)
{
	printf("\n\t\033[0;34mControls :\033[0m\n\n");
	printf("\033[0mCamera Tilt   \033[0;32m┏┉┉┉┓\033[0m  Field of vision \033[\
	1;33m┏┉┉┉┓\033[0m Light                \033[1;31m┏┉┉┉┓\033[0m           \
	\033[1;31m┏┉┉┉┓\033[0m Position          \033[0;34m┏┉┉┉┓    \n");
	printf("\033[0m              \033[0;32m┇ ⇧ ┇\033[0m                  \033[\
	1;33m┇ Ä ┇\033[0m      Position        \033[1;31m┇ W ┇\033[0m Intensity \
	\033[1;31m┇ + ┇\033[0m                   \033[0;34m┇ I ┇    \n");
	printf("\033[0m          \033[0;32m┏┉┉┉┛   ┗┉┉┉┓\033[0m              \033[\
	1;33m┇ ↑ ┇\033[0m                  \033[1;31m┏┉┉┉┛ ↑ ┗┉┉┉┓\033[0m       \
	\033[1;31m┇ ↑ ┇\033[0m               \033[0;34m┏┉┉┉┛   ┗┉┉┉┓\n");
	printf("\033[0m          \033[0;32m┇ ⇦       ⇨ ┇\033[0m              \033[\
	1;33m┇   ┇\033[0m   Front   Back   \033[1;31m┇ A ←   → S ┇\033[0m       \
	\033[1;31m┇   ┇\033[0m Far    Close  \033[0;34m┇ J       L ┇\n");
	printf("\033[0m          \033[0;32m┗┉┉┉┓   ┏┉┉┉┛\033[0m              \033[\
	1;33m┇ ↓ ┇\033[0m   \033[1;31m┏┉┉┉┉┉┉┉┉┉┉┉┓  ┗┉┉┉┓ ↓ ┏┉┉┉┛\033[0m       \
	\033[1;31m┇ ↓ ┇\033[0m \033[0;34m┏┉┉┉┉┉┉┉┉┉┉┉┓ ┗┉┉┉┓   ┏┉┉┉┛\n");
	printf("\033[0m              \033[0;32m┇ ⇩ ┇\033[0m                  \033[\
	1;33m┇ # ┇\033[0m   \033[1;31m┇ F ↙   ↗ B ┇      ┇ D ┇\033[0m           \
	\033[1;31m┇ - ┇\033[0m \033[0;34m┇ Ö ↙   ↗ Ü ┇     ┇ K ┇    \n");
	printf("\033[0m              \033[0;32m┗┉┉┉┛\033[0m                  \033[\
	1;33m┗┉┉┉┛\033[0m   \033[1;31m┗┉┉┉┉┉┉┉┉┉┉┉┛      ┗┉┉┉┛\033[0m           \
	\033[1;31m┗┉┉┉┛\033[0m \033[0;34m┗┉┉┉┉┉┉┉┉┉┉┉┛     ┗┉┉┉┛\033[0m    \n\n");
	printf("T  Toggle Debug info\nC  Show this Menu\nR  Retrace the Pixel at \
current Mouse-Position\nO  Toggle Origin visualisation\nP  Print Input of \
current Scene\nESC  Exit Process\n\n");
}

// Trace me baby one more time
void	debug(t_mrt *mrt)
{
	int		cord[2];
	t_vec	ray;
	t_vec	*scr;

	mlx_mouse_get_pos(mrt->mlx, mrt->win, &cord[0], &cord[1]);
	scr = scream(mrt->cam);
	printf("ray trough x %i, y %i\n", cord[0], cord[1]);
	ray = single_ray(cord[0] - (WDTH / 2), cord[1] - (HGHT / 2), mrt->cam, scr);
	nachfolger(cord, mrt, scr, TRUE);
}

int	render(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img.img, 0, 0);
	return (0);
}

int	end(t_mrt *mrt)
{
	if (mrt)
		exit(0);
	return (0);
}

int	key_hook(int key, t_mrt *mrt)
{
	static t_bool	swtch;

	if (key == 65307)
		end(mrt);
	if (key == 116)
		swtch = !swtch;
	if (!swtch && key == 99)
		controls();
	else if (!swtch && key == 112)
		print_config(mrt, 0);
	else if (!swtch && key == 114)
		debug(mrt);
	else if (!swtch && (key == 105 || key == 106 || key == 107 || key == 108 \
	|| key == 246 || key == 252))
		move(mrt, key);
	else if (!swtch && (key == 65362 || key == 65364 || key == 65361 || key \
	== 65363 || key == 228 || key == 35))
		camera(mrt, key);
	else if (!swtch && (key == 119 || key == 97 || key == 115 || key == 100 \
	|| key == 102 || key == 98 || key == 43 || key == 45))
		light(mrt, key);
	else if (!swtch && key == 111)
		origin(mrt, 0);
	return (0);
}

size_t	ft_pointlen(t_obj **str)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
		if (str[i]->id == 'Z')
			res += 2;
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

int	main(int argc, char **argv)
{
	t_mrt	mrt;

	if (argc != 2)
	{
		printf("Error\nIncorrect number of Args\n");
		return (1);
	}
	if (input(&mrt, argv[1]))
		return (printf("ERROR INPUT\n"));
	expand_obj(&mrt);
	mrt.mlx = mlx_init();
	mrt.win = mlx_new_window(mrt.mlx, WDTH, HGHT, "I wanna be Tracer");
	calc(&mrt);
	controls();
	mlx_mouse_show(mrt.mlx, mrt.win);
	mlx_loop_hook(mrt.mlx, render, &mrt);
	mlx_key_hook(mrt.win, key_hook, &mrt);
	mlx_hook(mrt.win, 33, (1L << 17), end, &mrt);
	mlx_loop(mrt.mlx);
	rt_exit(&mrt);
	return (0);
}
