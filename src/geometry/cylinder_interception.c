#include "../../inc/miniRT.h"

double	c_intrcpt(t_mrt *mrt, double *ray, double *cyl)
{
	//calculate tube first, no bottom/top tho
	double	diag[3];

	//calculate vertical axis of cylinder
	double	vert[3];

	vert = calc_vert(mrt, cyl);
	diag = cross-product(vert, mrt, ray);
	// check if point is on vector
	if (pnt_on_vec(vert, diag))
		return (1);
	return (0);
}
