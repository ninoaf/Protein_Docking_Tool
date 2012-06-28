/*
 * translationMatrix.cpp
 *
 *  Created on: Sep 25, 2009
 *      Author: canadi
 */

#include "translationmatrix.h"

TranslationMatrix::TranslationMatrix()
{
	order_ = -1;
}

TranslationMatrix::TranslationMatrix(int order, double R)
{
	order_ = order;
	R_ = R;
}


TranslationMatrix::~TranslationMatrix()
{
}

TranslationMatrix::TranslationMatrix(const string& inputFile)
{
	importFromFile(inputFile);
}

int TranslationMatrix::importFromFile(const string& inputFile)
{
	FILE *fp = fopen(inputFile.c_str(), "rb");

	if (fp == 0)
	{
		fprintf(stderr, "Ne mogu ucitati translation file %s\n", inputFile.c_str());
		exit(1);
	}

	int ret = 0;

	ret += fread (&order_, sizeof(order_), 1, fp);
	ret += fread (&R_, sizeof(R_), 1, fp);

	matrix_.resize((order_ * order_ * (order_+1) * (order_+1) * (2*order_+1)) / 12);

/*	for (int _n = 1;    _n <= order_;  _n++)
	for (int _l = 0;    _l <= _n-1;    _l++)
	for (int m  = -_l;  m  <= _l;      m ++)
	for (int n  = 1;    n  <= order_;  n ++)
	for (int l  = 0;    l  <= n-1;     l ++)*/

	for (unsigned int i = 0; i < matrix_.size(); ++i)
	{
		ret += fread (&matrix_[i], sizeof(matrix_[i]), 1, fp);
	}

	fclose(fp);

	return ret;
}

int TranslationMatrix::getOrder() const
{
	return order_;
}


