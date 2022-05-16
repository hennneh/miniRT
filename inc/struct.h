/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlehmann <hlehmann@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:16:39 by hlehmann          #+#    #+#             */
/*   Updated: 2022/05/16 11:16:40 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/**
 * struct to represent vectors as one unit and to make returns easier
 * this includes directio vectors and location vectors
 * @param x [double] Value for the X-Component of the vector
 * @param y [double] Value for the Y-Component of the vector
 * @param z [double] Value for the Z-Component of the vector
*/
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

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
	t_vec	cor;
	t_vec	v_o;
	double	fov;
}	t_cam;

/**
 * struct for Light 
 * @param id [char] char identifier
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param brit [double] lighting ratio [0.0 - 1.0]
*/
typedef struct s_lol
{
	char	id;
	t_vec	cor;
	double	lr;
}	t_lol;

/**
 * struct for Light bonus with RGB
 * @param id [char] char identifier
 * @param cor [double[3]] coordinates of view point [x][y][z]
 * @param lr [double] lighting ratio [0.0 - 1.0]
 * @param r [int] Red [0 - 255]
 * @param g [int] Green [0 - 255]
 * @param b [int] Blue [0 - 255]
*/
typedef struct s_lol_b
{
	char	id;
	t_vec	cor;
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
	t_vec	cor;
	t_vec	v_o;
	double	rad;
	double	hght;
	int		r;
	int		g;
	int		b;
}	t_obj;

typedef enum e_bool{FALSE, TRUE}	t_bool;

#endif
