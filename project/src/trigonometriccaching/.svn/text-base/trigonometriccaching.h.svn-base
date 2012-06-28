/*
 * trigonometriccaching.h
 *
 *  Created on: Sep 29, 2009
 *      Author: canadi
 */

#ifndef TRIGONOMETRICCACHING_H_
#define TRIGONOMETRICCACHING_H_

#include <math.h>
#include <map>
#include <vector>
#include <cstdio>

using namespace std;

class double_cmp
{
public:
	bool operator () (const double &a, const double &b);
};

class TrigonometricCaching
{
public:
	double sinm(int m, double alpha);
	double cosm(int m, double alpha);
	void setOrder(int order);
	static TrigonometricCaching* instance();

protected:
	TrigonometricCaching();

private:
	static TrigonometricCaching* instance_;

	int order_;
	map <double, vector <double>, double_cmp> sinCache_;
	map <double, vector <double>, double_cmp> cosCache_;

	vector <double>& cacheFind(double alpha, map <double, vector <double>, double_cmp> &cache);
	double sinm(int m, double alpha, double cosalpha, vector <double>& cache);
	double cosm(int m, double alpha, vector <double>& cache);
};

#endif /* TRIGONOMETRICCACHING_H_ */
