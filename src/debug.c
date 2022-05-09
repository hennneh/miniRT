#include "../inc/minirt.h"

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
