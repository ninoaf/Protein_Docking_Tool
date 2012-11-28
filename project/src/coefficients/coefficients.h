/*
 * coeffs.h
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#ifndef COEFFS_H_
#define COEFFS_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

#include "../structures/structures.h"
#include "../translationmatrix/translationmatrix.h"
#include "../rotationmatrix/rotationmatrix.h"
#include "../grid/grid.h"
#include "../trigonometriccaching/trigonometriccaching.h"
#include "../basefunctions/basefunctions.h"

using namespace std;

class Grid;
class TranslationMatrix;
class RotationMatrix;

class Coefficients
{
	friend class Grid;
	friend class Docking;
	friend class Protein;
public:
	Coefficients(); //
	~Coefficients(); //
	Coefficients(int order); //
	Coefficients(int order, const Grid& grid);
	Coefficients(const string& fname);
	Coefficients(const Coefficients& source);

	void init(int order);
	bool calculateFromGrid(const Grid& grid); //
	int getNumberOfCoefficients() const; //
	int exportToFile(const string& fname) const; //
	void dump(const string& fname) const;
	int importFromFile(const string& fname);//
	int importFromOldFile(const string& fname);

	void rotate(const RotationMatrix& rotationMatrix);
	void rotateTo(Coefficients& destination, const RotationMatrix& rotationMatrix) const;
	
	void qRotateTo(Coefficients& destination, const Coefficients& inner, double Q, const RotationMatrix& rotationMatrix) const;
	void qTransition(const Coefficients& inner,double Q);

	void rotate(const double alpha);
	void rotateTo(Coefficients& destination, const double alpha) const;

	bool merge(const Coefficients& with);

	int getOrder() const;
	void setOrder(int _order);
	int getIndex(int n, int l, int m) const;
	void testGetIndex() const;
	double getValue(int n, int l, int m) const;
	double getValue(int index) const;

	double compareCoefficientsTo(Coefficients& coefficients);

	void translate(const TranslationMatrix& translationmatrix);
	void translate(const TranslationMatrix& translationmatrix, vector<int>& translationIndexes);
	void translateTo(Coefficients& destination, const TranslationMatrix& translationmatrix) const;
	void translateTo(Coefficients& destination, const TranslationMatrix& translationmatrix, vector<int>& translationIndexes) const;
	void calulateTranslationIndexes( vector<int>& translationIndexes ) const;

	bool calculateChargeCoeffsFromGrid(const Grid& grid);

private:

	vector<CoeffValue> coefficients_;
	int order_;
	int coeffSize_;
	static const double cutoffValue_ = 0.95; // nino upozorava
};


#endif /* COEFFS_H_ */
