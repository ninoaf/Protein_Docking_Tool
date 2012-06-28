/*
 * laguerre.cpp
 *
 *  Created on: Sep 14, 2009
 *      Author: nino
 */
#include "math_pdt.h"


/** Returns the value of generalised Laguerre polynomial. */
/*double Laguerre_Polynomial(double a, double x, int k)
{
	int i;
	double rezultat=0, l1=1+a-x, l2=a*a/2+1.5*a+1-(a+2)*x+x*x/2, c2, c1;

	if (k==0) return 1;
	if (k==1) return l1;
	if (k==2) return l2;
	if (k>=3)

		for (i=3; i<=k; i++)
	{
		c2=(2*i+a-1-x)/i;
		c1=(i+a-1)/i;
		rezultat=c2*l2-c1*l1;
		l1=l2;
		l2=rezultat;
	}



	return rezultat;

}*/

/** Returns the value of the normalized GTO radial functions. */
/*double Radial_Function(int n, int l, double r)
{
	double rezultat=0, ro=r*r/LAMBDA;
	int i;

	rezultat=2/sqrt(pow(LAMBDA, 3)*PI);

	for (i=1; i<=n-l-1; i++)
		rezultat=rezultat*i*2/(2*i-1);

	for (i=n-l; i<=n; i++)
		rezultat=rezultat*2/(2*i-1);

	rezultat=sqrt(rezultat)*exp(-ro*0.5)*pow(sqrt(ro),l) * Laguerre_Polynomial(l+0.5,ro,n-l-1);

	return rezultat;
}*/



/** Calculates the spherical coordinates out of Carthesian coordinates. */
/*
void Spherical_Coordinates(double x, double y, double z, double *r, double *azimut, double *zenit)
{
	*r=sqrt (x*x+y*y+z*z);
	if (x>0)
		if (y>0) *azimut=atan(y/(1.0*x));
	else if (y<0) *azimut=2*PI+atan(y/(1.0*x));
	else *azimut=0;
	else if (x<0)
		if ((y<0) || (y>0)) *azimut=PI+atan(y/(1.0*x));
	else if (y=0) *azimut=atan(y/(1.0*x));
	else *azimut=-PI;
	else
		if (y>0) *azimut=PI/2;
	else if (y<0) *azimut=3*PI/2;
	else *azimut=0;

	if (*r==0) *zenit=PI/2;
	else *zenit = -asin(z/(1.0*(*r)))+PI/2;
}
*/

/** Returns the value of the phi function for calculating of spherical coefficients. */
/*double Phi (int m, double zenit)
{
	if (m>0) return cos(m*zenit)/sqrt(PI);
	else if (m==0) return 1/sqrt(2*PI);
	else return sin(-m*zenit)/sqrt(PI);
}*/

