#ifndef STRUCT_H
# define STRUCT_H

/**
 * struct for the Ambient lighting
 * @param id [char] char identifier
 * @param lr [double] lighting ratio [0.0 - 1.0]
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_al
{
	char	id;
	double	lr;
	int		r;
	int		g;
	int		b;
}	t_al;

/**
 * struct for the Camara; If v_o == [0][0][0], -> [1][0][0]
 * @param id [char] char identifier
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param v_o [double[3]] orientation vector [x][y][z] [-1 - 1]
 * @param fov [double] field of view in degrees [0 - 180]
*/
typedef struct s_cam
{
	char	id;
	double	cor[3];
	double	v_o[3];
	double	fov;// double! NOTE TO VINNY: multiply initial value by (π / 180)
}	t_cam;

/**
 * struct for Light 
 * @param id [char] char identifier
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param brit [double] light brightness ratio [0.0 - 1.0]
*/
typedef struct s_lol
{
	char	id;
	double	cor[3];
	double	brit;
}	t_lol;

/**
 * struct for Light bonus with RGB
 * @param id [char] char identifier
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param brit [double] light brightness ratio [0.0 - 1.0]
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_lol_b
{
	char	id;
	double	cor[3];
	double	brit;
	int		r;
	int		g;
	int		b;
}	t_lol_b;

/**
 * struct for object
 * @param id [char] char identifier S = sphere; P = plane; Z = cylinder
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param v_o [double[3]] 3d normalization orientation vector [x][y][z] [-1 - 1]
 * @param rad [double] object rad 
 * @param hght [double] object hight
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_obj
{
	char	id;
	double	cor[3];
	double	v_o[3];
	double	rad;
	double	hght;
	int		r;
	int		g;
	int		b;
}	t_obj;

#endif

// /**
//  * struct for sphere
//  * @param id [char] char identifier
//  * @param cor [double[3]] coordinates of view point [x][y][z]
//  * @param rad [double] sphere rad 
//  * @param r [int] Red [0 - 255]
//  * @param g [int] Green [0 - 255]
//  * @param b [int] Blue [0 - 255]
// */
// typedef struct s_sph
// {
// 	char	id;
// 	double	cor[3];
// 	double	rad;
// 	int		r;
// 	int		g;
// 	int		b;
// }	t_sph;

// /**
//  * struct for plane
//  * @param id [char] char identifier
//  * @param cor [double[3]] coordinates of view point [x][y][z]
//  * @param v_o [double[3]] 3d normalization orientation vector [x][y][z] [-1 - 1]
//  * @param r [int] Red [0 - 255]
//  * @param g [int] Green [0 - 255]
//  * @param b [int] Blue [0 - 255]
// */
// typedef struct s_pl
// {
// 	char	id;
// 	double	cor[3];
// 	double	v_o[3];
// 	int		r;
// 	int		g;
// 	int		b;
// }	t_pl;

// /**
//  * struct for cylinder
//  * @param id [char] char identifier
//  * @param cor [double[3]] coordinates of view point [x][y][z]
//  * @param v_o [double[3]] 3d normalization orientation vector [x][y][z] [-1 - 1]
//  * @param rad [double] cylinder radius
//  * @param hght [double] cylinder hight
//  * @param r [int] Red [0 - 255]
//  * @param g [int] Green [0 - 255]
//  * @param b [int] Blue [0 - 255]
// */
// typedef struct s_cyl
// {
// 	char	id;
// 	double	cor[3];
// 	double	v_o[3];
// 	double	rad;
// 	double	hght;
// 	int		r;
// 	int		g;
// 	int		b;
// }	t_cyl;