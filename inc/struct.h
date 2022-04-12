#ifndef STRUCT_H
# define STRUCT_H

/**
 * struct for the Ambient lighting
 * @param lr [double] lighting ratio [0.0 - 1.0]
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_al
{
	double	lr;
	int		r;
	int		g;
	int		b;
}	t_al;

/**
 * struct for the Camara
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param v_o [double[3]] orientation vector [x][y][z] [-1 - 1]
 * @param fov [double] field of view in degrees [0 - 180]
*/
typedef struct s_cam
{
	double	cor[3];
	double	v_o[3];
	double	fov;// double! NOTE TO VINNY: multiply initial value by (π / 180)
}	t_cam;

/**
 * struct for Light
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param brit [double] light brightness ratio [0.0 - 1.0]
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_lol
{
	double	cor[3];
	double	brit;
	int		r;
	int		g;
	int		b;
}	t_lol;

typedef struct s_sph
{
	/**/
}	t_sph;

typedef struct s_pl
{
	/* data */
}	t_pl;

typedef struct s_cyl
{
	/* data */
}	t_cyl;

#endif
