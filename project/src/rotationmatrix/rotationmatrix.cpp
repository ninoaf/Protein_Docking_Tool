/*
 * rotationmatrix.cpp
 *
 *  Created on: Nov 3, 2009
 *      Author: canadi
 */

#include "rotationmatrix.h"

RotationMatrixCache* RotationMatrixCache::instance_ = 0;
int RotationMatrixCache::maxSize_ = 60;

RotationMatrixCache::RotationMatrixCache()
{
	binomialCoefficientsCache_.resize(maxSize_);
	fill(binomialCoefficientsCache_.begin(), binomialCoefficientsCache_.end(), vector <double>(maxSize_, -1.0));

	factorielsCache_.resize(maxSize_);
	fill(factorielsCache_.begin(), factorielsCache_.end(), -1.0);
}

RotationMatrixCache* RotationMatrixCache::instance()
{
	if (instance_ == 0)
	{
		instance_ = new RotationMatrixCache;
	}

	return instance_;
}

double RotationMatrixCache::binomialCoefficients(int n, int k)
{
	if (n == k || k == 0) return 1.0;
	if (n < k) return 0.0;
	if (binomialCoefficientsCache_[n][k] > -1.0) return binomialCoefficientsCache_[n][k];

	return binomialCoefficientsCache_[n][k] = binomialCoefficients(n-1, k) + binomialCoefficients(n-1, k-1);
}

double RotationMatrixCache::factoriels(int n)
{
	if (n == 0) return 1.0;
	if (factorielsCache_[n] > -1.0) return factorielsCache_[n];

	return factorielsCache_[n] = n*factoriels(n-1);
}

RotationMatrix::RotationMatrix()
{
	matrix_.clear();
}

RotationMatrix::RotationMatrix(int order, const RotationAngle& rotationAngle)
{
	calculateMatrix(order, rotationAngle);
}

RotationMatrix::~RotationMatrix()
{
	for (unsigned int i = 0; i < matrix_.size(); ++i)
	{
		delete [] matrix_[i];
	}
}

int RotationMatrix::getOrder() const
{
	return order_;
}

void RotationMatrix::calculateMatrix(int order, const RotationAngle& rotationAngle)
{
	for (unsigned int i = 0; i < matrix_.size(); ++i)
	{
		delete [] matrix_[i];
	}

	order_ = order;

	matrix_.resize(order_);

	for (int l = 0; l <= (order_-1); l++)
	{
		matrix_[l] = new double[(2*l+1)*(2*l+1)];
		cacheBuffer_ = new double[(2*l+1)*(2*l+1)];
		for (int i = 0; i < (2*l+1)*(2*l+1); ++i)
		{
			cacheBuffer_[i] = -100000.0;
		}

		// calculation of rotation matrix R for given l, alpha, beta and gamma
		//calculateMatrixR(l, 0, rotationAngle.beta, rotationAngle.gamma, matrix_[l]);

		for (int i = 0; i < 2*l+1; ++i)
		for (int j = 0; j < 2*l+1; ++j)
		{
			matrix_[l][i*(2*l+1) + j] = matrixRGetElement(l, i-l, j-l, rotationAngle);
		}

		delete [] cacheBuffer_;
	}
}

double RotationMatrix::power(double x, int p)
{
	if (p < 0)
	{
		x = 1.0/x;
		p = -p;
	}

	double retVal = 1.0, tmp = x;

	for ( ; p; p >>= 1)
	{
		if ((p&1) == 1) retVal *= tmp;
		tmp *= tmp;
	}

	return retVal;
}

double RotationMatrix::minusOnePow(int k)
{
	if (k < 0) k = -k;

	return (k%2 == 0)? 1.0 : -1.0;
}

double RotationMatrix::matrixDGetElement(int l, int m_crt, int m, double beta)
{
	if (cacheBuffer_[(m_crt+l)*(2*l+1) + m+l] > -1000.0)
	{
		return cacheBuffer_[(m_crt+l)*(2*l+1) + m+l];
	}

	double retVal = 0.0;

	double cosBetaHalf = cos(beta/2.0);
	double sinBetaHalf = sin(beta/2.0);

	RotationMatrixCache* rmi = RotationMatrixCache::instance();

	for (int k = max(0, m-m_crt); k <= l-m_crt && k <= l+m; ++k)
	{
		retVal += minusOnePow(k+m_crt-m) *
				rmi->binomialCoefficients(l+m, k) * rmi->binomialCoefficients(l-m, l - m_crt - k) *
				power(cosBetaHalf, 2*l + m - m_crt - 2*k) * power(sinBetaHalf, 2*k + m_crt - m);
	}

	retVal *= sqrt( (rmi->factoriels(l+m_crt) / rmi->factoriels(l+m)) *
			(rmi->factoriels(l-m_crt) / rmi->factoriels(l-m)) );

	cacheBuffer_[(m_crt+l)*(2*l+1) + m+l] = retVal;
	cacheBuffer_[(m+l)*(2*l+1) + m_crt+l] = minusOnePow(m_crt-m) * retVal;
	cacheBuffer_[(-m_crt+l)*(2*l+1) - m+l] = minusOnePow(m_crt-m) * retVal;

	return retVal;
}

double RotationMatrix::matrixRGetElement(int l, int m_crt, int m, const RotationAngle& rotationAngle)
{
	TrigonometricCaching* tci = TrigonometricCaching::instance();

	double d1 = matrixDGetElement(l, m_crt, m, rotationAngle.beta);

	if (m_crt == 0 && m > 0)  return d1 * sqrt(2) * tci->cosm(m, rotationAngle.gamma);
	if (m_crt > 0 && m == 0)  return d1 * sqrt(2);
	if (m_crt == 0 && m == 0) return d1;
	if (m_crt < 0 && m == 0)  return 0;
	if (m_crt == 0 && m < 0)  return minusOnePow(m) * d1 * sqrt(2) * tci->sinm(m, rotationAngle.gamma);

	double d2 = matrixDGetElement(l, -m_crt, m, rotationAngle.beta);

	if (m_crt < 0 && m > 0)
	{
		return tci->sinm(m, rotationAngle.gamma) * (minusOnePow(m_crt+1) * d1 + d2);
	}

	if (m_crt > 0 && m > 0)
	{
		return  tci->cosm(m, rotationAngle.gamma) * (d1 + minusOnePow(m_crt) * d2);
	}

	if (m_crt > 0 && m < 0)
	{
		return tci->sinm(m, rotationAngle.gamma) * (minusOnePow(m) * d1 + minusOnePow(m+m_crt) * d2);
	}

	if (m_crt < 0 && m < 0)
	{
		return tci->cosm(m, rotationAngle.gamma) * (minusOnePow(m+m_crt) * d1 + minusOnePow(m+1) * d2);
	}

	return -1.0;
}




