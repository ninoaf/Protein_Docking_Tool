/*
 * math_pdt.h
 *
 *  Created on: Sep 14, 2009
 *      Author: nino
 */

#ifndef MATH_PDT_H_
#define MATH_PDT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_sf_legendre.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>

#include "../structures/structures.h"

// #include "../rot_angles/angles.h"
#ifndef PI
#define PI 3.1415926535898
#endif



////////////////////// LEGENDRE POLYNOMIALS HEADER /////////////////////////////////////
#ifndef NORM_FACTOR
#define NORM_FACTOR 2.506628274631002
#endif

/** Calculates Legendre polynomials. This is a wrapper of a GSL function. */
double Legendre_Polynomial(unsigned int l, double x);
/** Calculates spherical harmonics using Legendre polynomials. This is a wrapper of a GSL function, and it's patched with UPE ('Ugliest Patch Ever'), which makes it a preferable solution. */
double Legendre_Polynomial_Spherical (int l, int m, double x);

////////////////////// END LEGENDRE POLYNOMIALS HEADER /////////////////////////////////



////////////////////// LAGUERRE POLYNOMIALS HEADER /////////////////////////////////////
#ifndef LAMBDA
#define LAMBDA 20.0
#endif

/** Returns the value of generalised Laguerre polynomial */
double Laguerre_Polynomial(double a, double x, int k);
/** Returns the value of the normalized GTO radial functions */
double Radial_Function(int n, int l, double r);
/** Calculates the spherical coordinates out of Carthesian coordinates */
void Spherical_Coordinates (double x, double y, double z, double *r, double *azimut, double *zenit);
/** Returns the value of the phi function for calculating of spherical coefficients */
double Phi (int m, double zenit);
////////////////////// END LAGUERRE POLYNOMIALS HEADER /////////////////////////////////




////////////////////// WIGNER ROTATION HEADER /////////////////////////////////////
/** functions for calculation of factorials - x is limited to x<=12 */
double Fakt(unsigned int x);
/** DELETED: function for calculating mp binomial coefficients */
//double Wigner_Binomial_Coefficient(unsigned int n, unsigned int k);
/** new function for calculating binomial coefficients */
unsigned int binomialCoefficient(unsigned int m, unsigned int n);
/** functions for calculating matrix R */
double elementOfMatrixD(int l, int m_crt, int m, double beta);

/** Wigner rotation, matrix D. */
void matrixD(int l, double beta, double *matrix_d);
/** Wigner rotation, element of matrix d. */
double elementOfMatrixR(int l, int m_crt, int m, double alpha, double gamma, double *matrix_d);
/** Wigner rotation, matrix R. */
void calculateMatrixR(int l, double alpha, double beta, double gamma, double *matrix_r);
/** Wigner rotation, returns an element from the matrix. */
double getElement(int l, int m_crt, int m, double *matrix_r);
/** Wigner rotation, matrix multiplication. */
double* matrixMultiply(int l, double *matrix_r1, double *matrix_r2);
////////////////////// END WIGNER ROTATION HEADER /////////////////////////////////



////////////////////// ROTATION ANGLES HEADER /////////////////////////////////////

void Icosahedron_Coordinates(Coordinates* vertices);
void Edge_Subdivision(const Coordinates& v1, const Coordinates& v2, Coordinates& v3);
void Triangle_Center(Coordinates& v, const Coordinates& v1, const Coordinates& v2, const Coordinates& v3);
void Icosahedron_Subdivision(int k, Coordinates *vertices);
void Euler_Angles(Coordinates &v, double &beta, double &gamma);
void Rotational_Angles(int k, RotationAngle *rotational_angles);

////////////////////// END ROTATION ANGLES HEADER /////////////////////////////////

#endif /* MATH_PDT_H_ */
