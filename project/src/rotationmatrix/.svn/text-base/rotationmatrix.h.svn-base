/*
 * rotationmatrix.h
 *
 *  Created on: Nov 3, 2009
 *      Author: canadi
 */

#ifndef ROTATIONMATRIX_H_
#define ROTATIONMATRIX_H_

#include "../coefficients/coefficients.h"
#include "../structures/structures.h"
#include "../math/math_pdt.h"
#include "../trigonometriccaching/trigonometriccaching.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class RotationMatrixCache
{
public:
	double binomialCoefficients(int n, int k);
	double factoriels(int n);
	static RotationMatrixCache* instance();

protected:
	RotationMatrixCache();

private:
	static RotationMatrixCache* instance_;

	static int maxSize_;

	vector < vector <double> > binomialCoefficientsCache_;
	vector <double> factorielsCache_;
};

class RotationMatrix
{
	friend class Coefficients;
public:
	RotationMatrix();
	RotationMatrix(int order, const RotationAngle& rotationAngle); //
	~RotationMatrix(); //

	void calculateMatrix(int order, const RotationAngle& rotationAngle);

	int getOrder() const;

private:
	int order_;

	double* cacheBuffer_;

	vector<double*> matrix_;

	double power(double x, int p);
	double minusOnePow(int k);
	double matrixDGetElement(int l, int m_crt, int m, double beta);
	double matrixRGetElement(int l, int m_crt, int m, const RotationAngle& rotationAngle);
};


#endif /* ROTATIONMATRIX_H_ */
