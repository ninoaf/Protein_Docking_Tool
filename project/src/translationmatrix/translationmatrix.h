/*
 * translationMatrix.h
 *
 *  Created on: Sep 25, 2009
 *      Author: canadi
 */

#ifndef TRANSLATIONMATRIX_H_
#define TRANSLATIONMATRIX_H_

#include <vector>
#include <string>

#include "../coefficients/coefficients.h"

using namespace std;

class TranslationMatrix
{
	friend class Coefficients;
public:
	TranslationMatrix(); //
	TranslationMatrix(int order, double R); //
	~TranslationMatrix(); //
	TranslationMatrix(const string& inputFile); //

	int importFromFile(const string& inputFile);//
	int getOrder() const;

private:
	int order_;
	double R_;
	vector<double> matrix_;
};

#endif /* TRANSLATIONMATRIX_H_ */