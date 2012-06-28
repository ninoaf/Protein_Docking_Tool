/*
 * trigonometriccaching.cpp
 *
 *  Created on: Sep 29, 2009
 *      Author: canadi
 */

#include "trigonometriccaching.h"

TrigonometricCaching* TrigonometricCaching::instance_ = 0;

TrigonometricCaching::TrigonometricCaching()
{
	order_ = 30; // hard coded, za svaki slucaj
}


TrigonometricCaching* TrigonometricCaching::instance()
{
	if (instance_ == 0)
	{
		instance_ = new TrigonometricCaching;
	}

	return instance_;
}


void TrigonometricCaching::setOrder(int order)
{
	order_ = order;
}


double TrigonometricCaching::sinm(int m, double alpha, double cosalpha, vector <double>& cache)
{
	if(cache[m] > -4.0) return cache[m];
	if (m == 0 || m == 1) return cache[m] = sin(m*alpha);

	return cache[m] = 2.0 * cosalpha * sinm(m-1, alpha, cosalpha, cache) - sinm(m-2, alpha, cosalpha, cache);
}


double TrigonometricCaching::cosm(int m, double alpha, vector <double>& cache)
{
	if (cache[m] > -4.0) return cache[m];
	if (m == 0 || m == 1) return cache[m] = cos(m*alpha);

	return cache[m] = 2.0 * cosm(1, alpha, cache) * cosm(m-1, alpha, cache) - cosm(m-2, alpha, cache);
}


double TrigonometricCaching::sinm(int m, double alpha)
{
	return ((m<0)?-1:1) * sinm(((m<0)?-m:m), alpha, cos(alpha), cacheFind(alpha, sinCache_));
}

double TrigonometricCaching::cosm(int m, double alpha)
{
	return cosm(((m<0)?-m:m), alpha, cacheFind(alpha, cosCache_));
}


vector <double>& TrigonometricCaching::cacheFind(double alpha, map <double, vector <double>, double_cmp> &cache)
{
	map <double, vector <double>, double_cmp>::iterator cacheIterator = cache.find(alpha);

	if (cacheIterator == cache.end())
	{
		cacheIterator = cache.insert(make_pair(alpha, vector<double>(order_+1, -5.0))).first;
	}

	return cacheIterator->second;
}


bool double_cmp::operator () (const double &a, const double &b)
{
	if (((a-b < 0)?b-a:a-b) < 1e-9) return false;
	return a < b;
}
