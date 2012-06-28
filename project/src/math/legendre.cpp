/*
 * legendre.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: nino
 */

#include "math_pdt.h"



/** Calculates Legendre polynomials. This is a wrapper of a GSL function. */
/*double Legendre_Polynomial(unsigned int l, double x)
{
	return gsl_sf_legendre_Pl (l, x);
}*/

/** Calculates spherical harmonics using Legendre polynomials. This is a wrapper of a GSL function, and it's patched with UPE ('Ugliest Patch Ever'), which makes it a preferable solution. */
/*double Legendre_Polynomial_Spherical (int l, int m, double x)
{
	return gsl_sf_legendre_sphPlm (l, m, x) * NORM_FACTOR;
}
*/
