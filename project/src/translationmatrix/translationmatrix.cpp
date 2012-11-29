/*
 * translationMatrix.cpp
 *
 *  Created on: Sep 25, 2009
 *      Author: canadi
 */

#include "translationmatrix.h"
#include "translationmatrixmathengine.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

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

int TranslationMatrix::getOrder() const
{
	return order_;
}

int TranslationMatrix::importFromFile(const string& inputFile)
{
	FILE *fp = fopen(inputFile.c_str(), "rb");

	if (fp == 0)
	{
		fprintf(stderr, "Cannot access translation file '%s'!\n", inputFile.c_str());
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
		ret += fread(&matrix_[i], sizeof(matrix_[i]), 1, fp);
	}

	fclose(fp);

	return ret;
}

int TranslationMatrix::exportToFile(const string& outputFile)
{
	FILE *fp = fopen(outputFile.c_str(), "wb");

	if (fp == 0)
	{
		fprintf(stderr, "Cannot open translation file '%s' for writing!\n", outputFile.c_str());
		exit(1);
	}

	int ret = 0;

	ret += fwrite (&order_, sizeof(order_), 1, fp);
	ret += fwrite (&R_, sizeof(R_), 1, fp);

/*	for (int _n = 1;    _n <= order_;  _n++)
	for (int _l = 0;    _l <= _n-1;    _l++)
	for (int m  = -_l;  m  <= _l;      m ++)
	for (int n  = 1;    n  <= order_;  n ++)
	for (int l  = 0;    l  <= n-1;     l ++)*/

	for (unsigned int i = 0; i < matrix_.size(); ++i)
	{
		ret += fwrite(&matrix_[i], sizeof(matrix_[i]), 1, fp);
	}

	fclose(fp);

	return ret;
}

void TranslationMatrix::dumpToFile(const string& outputFile)
{
	FILE *fp = fopen(outputFile.c_str(), "wt");

	if (fp == 0)
	{
		fprintf(stderr, "Cannot open file '%s' for writing!\n", outputFile.c_str());
		exit(1);
	}

	fprintf(fp, "%d, %lf\n", order_, R_);

/*	for (int _n = 1;    _n <= order_;  _n++)
	for (int _l = 0;    _l <= _n-1;    _l++)
	for (int m  = -_l;  m  <= _l;      m ++)
	for (int n  = 1;    n  <= order_;  n ++)
	for (int l  = 0;    l  <= n-1;     l ++)*/

	for (unsigned int i = 0; i < matrix_.size(); ++i)
	{
		fprintf(fp, "%.20lf\n", matrix_[i]);
	}

	fclose(fp);
}

void TranslationMatrix::calculateMatrix(int order, double R)
{
	TranslationMatrixMathEngine& mathEngine = TranslationMatrixMathEngine::getInstance();

	order_ = order;
	R_ = R;

	matrix_.resize((order_ * order_ * (order_+1) * (order_+1) * (2*order_+1)) / 12);
	int iMatrix = 0;

	for (int _n = 1;    _n <= order_;  _n++)
	{
//		printf("evo me na %d...\n", _n);
		for (int _l = 0;    _l <= _n-1;    _l++)
		for (int m  = -_l;  m  <= _l;      m ++)
		for (int n  = 1;    n  <= order_;  n ++)
		for (int l  = 0;    l  <= n-1;     l ++) // ovdje je gadni zajeb. l bi trebalo kretati od abs(m). TODO
		{
			if (m > l || -m > l)  // privremeno rjesenje
			{
				matrix_[iMatrix++] = 0.0;
				continue;
			}
			matrix_[iMatrix++] = mathEngine.matrixElement(R_, _n, _l, n, l, m);
		}
	}
}


