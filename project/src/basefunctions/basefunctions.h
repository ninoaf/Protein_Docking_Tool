/*
 * basefunctions.h
 *
 *  Created on: Dec 8, 2009
 *      Author: canadi
 */

#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include <gsl/gsl_sf_legendre.h> // privremeno treba zbog legendre-a
#include "../structures/structures.h"

using namespace std;

#ifndef BASEFUNCTIONS_H_
#define BASEFUNCTIONS_H_

#define NORM_FACTOR 2.506628274631002
#define LAMBDA 20.0
#define PI 3.1415926535898

/*class TripletIID
{
public:
	int first, second;
	double third;

	TripletIID() {};
	TripletIID(int _first, int _second, double _third) : first(_first), second (_second), third(_third) {};

	bool operator < (const TripletIID& a) const;
};

class DipletID
{
public:
	int first;
	double second;

	DipletID() {};
	DipletID(int _first, double _second) : first(_first), second (_second) {};

	bool operator < (const DipletID& a) const;
};*/

class BaseFunctions
{
public:
	double baseFunction(const CoeffCoordinates& coeffCoordinates, const SphericalCoordinates& sphericalCoordinates);

	static BaseFunctions* instance();


	double laguerrePolynomial(double alpha, double x, int k);
	double radialFunction(int n, int l, double radius); // GTO radial function
	double ETOradialFunction(int n, int l, double radius);
	double legendrePolynomialSpherical(int l, int m, double elevation);
	double phi(int m, double azimuth);

	double gamma(int xDouble);

	static BaseFunctions* instance_;
	static int gammaCacheSize_;

/*
	map <TripletIID, double> radialFunctionCache_;
	map <TripletIID, double> legendreCache_;
	map <DipletID, double> phiCache_;*/
private:
	vector <double> gammaCache_;
protected:
	BaseFunctions();
};

#endif /* BASEFUNCTIONS_H_ */