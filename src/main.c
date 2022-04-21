#include "../inc/minirt.h"

int	print_mrt(t_mrt *m)
{
	printf("\nLIGHT\n{\n");
	printf("id : [%c]\n", m->l->id);
	printf("cor : [%f][%f][%f]\n", m->l->cor[0], m->l->cor[1], m->l->cor[2]);
	printf("brit : [%f]\n}\n", m->l->brit);
	printf("\nSPHERE\n{\n");
	printf("id : [%c]\n", m->sp[0]->id);
	printf("cor : [%f][%f][%f]\n", m->sp[0]->cor[0], m->sp[0]->cor[1], m->sp[0]->cor[2]);
	printf("rad : [%f]\n", m->sp[0]->rad);
	printf("rgb : [%d][%d][%d]\n}\n", m->sp[0]->r, m->sp[0]->g, m->sp[0]->b);
	return (1);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_mrt	mrt;

	if (argc != 2)
		return (1);
	if (input(&mrt, argv[1]))
		return (printf("ERROR INPUT\n"));
	else
		return (print_mrt(&mrt));
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	return (0);
}
