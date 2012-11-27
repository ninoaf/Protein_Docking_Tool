#include "translationmatrixmathengine.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

double TranslationMatrixMathEngine::lambda_ = 20;
int TranslationMatrixMathEngine::maxFactorialSqrt_ = 200; // mora biti bar tri puta vece od obicnog maksimalnog ordera
int TranslationMatrixMathEngine::maximumOrder_ = 36;
int TranslationMatrixMathEngine::factorialCacheSize_ = 100;
TranslationMatrixMathEngine* TranslationMatrixMathEngine::instance_ = 0;

TranslationMatrixMathEngine& TranslationMatrixMathEngine::getInstance()
{
	if (instance_ == 0)
	{
		instance_ = new TranslationMatrixMathEngine();
	}
	return *instance_;
}

TranslationMatrixMathEngine::~TranslationMatrixMathEngine()
{
	if (innerLCache_ != NULL) delete [] innerLCache_;
	if (xCoefficientsCache_ != NULL) delete [] xCoefficientsCache_;
	if (aCoefficientsCache_ != NULL) delete [] aCoefficientsCache_;
}

TranslationMatrixMathEngine::TranslationMatrixMathEngine()
{
	factoralSqrtCache_.resize(maxFactorialSqrt_);
	fill(factoralSqrtCache_.begin(), factoralSqrtCache_.end(), -1.0);
	initSito();
	innerLCache_ = NULL;

	factorialCache_.resize(factorialCacheSize_);
	fill(factorialCache_.begin(), factorialCache_.end(), -1.0);
	halfFactorialCache_.resize(factorialCacheSize_);
	fill(halfFactorialCache_.begin(), halfFactorialCache_.end(), -1.0);

	setInnerLoopCaching(true);

	xCoefficientsCache_ = new double[maximumOrder_*maximumOrder_*maximumOrder_];

	for (int i = maximumOrder_*maximumOrder_*maximumOrder_-1; i >= 0; --i)
	{
		xCoefficientsCache_[i] = 1e30;
	}

	aCoefficientsCache_ = new double[maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_];

	for (int i = maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_-1; i >= 0; --i)
	{
		aCoefficientsCache_[i] = 1e30;
	}
}

bool TranslationMatrixMathEngine::getInnerLoopCaching()
{
	return innerLCaching_;
}

void TranslationMatrixMathEngine::setInnerLoopCaching(bool value)
{
	innerLCaching_ = value;

	if (innerLCaching_ == false)
	{
		if (innerLCache_ != NULL) 
		{
			delete [] innerLCache_;
			innerLCache_ = NULL;
		}
	}else
	{
		if (innerLCache_ == NULL)
		{
			innerLCache_ = new double[maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_];
			innerLCacheR_ = -1.0;
		}
	}
}

template <typename T>
T TranslationMatrixMathEngine::abs(T x) 
{ 
	return x < 0 ? -x : x; 
}

double TranslationMatrixMathEngine::halfFactorial(int n)
{
	if (halfFactorialCache_[n] > -1.0) return halfFactorialCache_[n];

	double res = 1.0;
	for (int i = 0; i < n; ++i)
		res *= (.5 + i);

	return halfFactorialCache_[n] = res;
}

double TranslationMatrixMathEngine::factorial(int n)
{
	if (factorialCache_[n] > -1.0) return factorialCache_[n];

	double res = 1.0;
	for (int i = 0; i < n; ++i)
		res *= (1.0 + i);

	return factorialCache_[n] = res;
}

double TranslationMatrixMathEngine::minusOnePow(int k)
{
	if (k < 0) k = -k;

	return (k%2 == 0)? 1.0 : -1.0;
}

// ne radi !?
double TranslationMatrixMathEngine::fSqrt(double y) 
{
	return sqrt(y); 

    double x, z, tempf;
    unsigned long *tfptr = ((unsigned long *)&tempf) + 1;

    tempf = y;
    *tfptr = (0xbfcdd90a - *tfptr)>>1;
    x =  tempf;
    z =  y*0.5;
    x = (1.5*x) - (x*x)*(x*z);
    x = (1.5*x) - (x*x)*(x*z);
    x = (1.5*x) - (x*x)*(x*z);
    x = (1.5*x) - (x*x)*(x*z);
    x = (1.5*x) - (x*x)*(x*z);
    return x*y;
}

// kasnije probaj hardkodirat
void TranslationMatrixMathEngine::initSito() 
{
    // RESIZE!!
    // minDiv[ prime[ 0 ] = 1 ] = 1;
    prime_.push_back(1);
    minDiv_.resize(maxFactorialSqrt_);

    for (int i = 2; i < maxFactorialSqrt_; i++)
	{
        if(!minDiv_[i]) 
		{
            for (int j = i; j < maxFactorialSqrt_; j += i)
			{
                minDiv_[j] = prime_.size();
			}
            prime_.push_back(i);
        }
	}
}

double TranslationMatrixMathEngine::power(int b, int p) 
{
    if (!p) return 1;
    int org, i;
    for (org = p, i = 1; org; org>>=1, i<<=1);
    double sol = 1;
    while (i) 
	{
        sol = sol * ((p&i) ? sol * b : sol);
        i >>= 1;
    }
    return sol;
}

double TranslationMatrixMathEngine::factorialSqrt(int x) 
{
    if (x < 0 || x > maxFactorialSqrt_-1) 
	{
		fprintf(stderr, "krivo pozivas factorialSqrt: %d\n", x);
		exit(1);
	}
    if (!x) return 1;
	if (factoralSqrtCache_[x] > -1.0) return factoralSqrtCache_[x];

    int* alpha = new int[maxFactorialSqrt_]; // prime[0] ^ alpha[0] + prime[1] ^ alpha[1]
    memset(alpha, 0, sizeof(int) * maxFactorialSqrt_);

    for (int i = 2; i <= x; i++)
	{
        for (int j = i; j > 1; j /= prime_[minDiv_[j]])
		{
            alpha[minDiv_[j]]++;
		}
	}

    double unutra = 1, ispred = 1; // sqrt(x!) = ispred * Sqrt[ unutra ]

    for (unsigned int i = 0; i <= prime_.size(); i++) // vadim iz korjena sve kvadrate koje mogu
	{ 
        if (alpha[i]) 
		{
            if (alpha[i] & 1) unutra *= (alpha[i] & 1) * prime_[i];
            if (alpha[i] / 2) ispred *= power(prime_[i], (alpha[i]/2));
        }
    }

	delete [] alpha;

    // sad je ispod korjena ostao samo umnozag nekih prostih brojeva < x
    // printf("%E\n%E\n", ispred, unutra );
    return factoralSqrtCache_[x] = ispred * fSqrt(unutra);
}

double TranslationMatrixMathEngine::evalSuma(int *J, int *M, int k) 
{
    double ovotu = factorial(k)*
        factorial(J[0] + J[1] - J[2] - k)*
        factorial(J[0] - k - M[0])*
        factorial(J[1] - k + M[1])*
        factorial(-J[1] + J[2] + k + M[0])*
        factorial(-J[0] + J[2] + k - M[1]);

    return k % 2 ? -ovotu : ovotu;
}

int TranslationMatrixMathEngine::mozeFakt(int *J, int *M, int k) 
{
    return
        !((J[0] + J[1] - J[2] - k < 0) ||
        (J[0] - k - M[0] < 0) ||
        (J[1] - k + M[1] < 0) ||
        (-J[1] + J[2] + k + M[0] < 0) ||
        (-J[0] + J[2] + k - M[1] < 0));
}

double TranslationMatrixMathEngine::calculate3j(int *J, int *M) 
{
    double korjeni = 1, suma = 0;

    for (int i = 0; i < 3; i++) 
	{
        int s = 0;
        for(int j = 0; j < 3; j++)
		{
            s += ((i==(2-j))?-1:1) * J[j];
		}
        korjeni *= factorialSqrt(s);
    }

    for( int i = 0; i < 3; i++ )
	{
        korjeni *= factorialSqrt(J[i]-M[i]) * factorialSqrt(J[i]+M[i]);
	}

    int lBound = max(0, max(J[1]-J[2]-M[0], J[0]-J[2]+M[1]));
    int rBound = min(J[0]-M[0], J[1]+M[1]);

    for (int k = lBound; k <= rBound; k++)
	{
        if(mozeFakt(J, M, k))
		{
            suma += (1 / evalSuma(J, M, k));
		}
	}

    int tmp = (-J[0] + J[1] + M[2]) % 2 ? -1 : 1;

    return suma * tmp * korjeni/factorialSqrt(1 + J[0] + J[1] + J[2]);
}

int TranslationMatrixMathEngine::test3j(int j1, int j2, int j3, int m1, int m2, int m3) 
{
    if (m1 + m2 + m3 != 0) return 0;
    if (abs(m1) > j1 || abs(m2) > j2 || abs(m3) > j3) return 0;
    if (!( abs(j1-j2) <= j3 && j3 <= j1 + j2)) return 0;
    return 1;
}

double TranslationMatrixMathEngine::wigner3j(int j1, int j2, int j3, int m1, int m2, int m3) 
{
	if (!test3j(j1, j2, j3, m1, m2, m3))
	{
		fprintf(stderr, "krivo pozivas wigner3j: {%d, %d} {%d, %d} {%d, %d}\n", j1, m1, j2, m2, j3, m3);
		exit(1);
	}

    int j[3] = {j1,j2,j3};
    int m[3] = {m1,m2,m3};
    return calculate3j(j, m);
}

double TranslationMatrixMathEngine::xCoefficients(int n, int l, int j)
{
	int iCache = n*maximumOrder_*maximumOrder_ + l*maximumOrder_ + j;
	if (xCoefficientsCache_[iCache] < 1e30) return xCoefficientsCache_[iCache];

	double res = factorialSqrt(n-l-1)*fSqrt(halfFactorial(n) / 2.0); // ovo bi moglo biti dosta neprecizno
	
	res *= minusOnePow(n-l-j-1) / (factorial(j) * factorial(n-l-j-1) * halfFactorial(l+j+1));

	return xCoefficientsCache_[iCache] = res;
}

double TranslationMatrixMathEngine::cCoefficients(int k, int n, int l, int nc, int lc)
{
	double res = 0.0;

	for (int j = 0; j <= n-l-1; ++j)
	{
		if (k-j < 0 || k-j > nc-lc-1) continue;
		res += xCoefficients(n, l, j)*xCoefficients(nc, lc, k-j);
	}

	return res;
}

double TranslationMatrixMathEngine::aCoefficients(int k, int kCache, int l, int lc, int m)
{
	int iCache = kCache * maximumOrder_ * maximumOrder_ * maximumOrder_
		+ l * maximumOrder_ * maximumOrder_
		+ lc * maximumOrder_
		+ m;

	if (aCoefficientsCache_[iCache] < 1e30) return aCoefficientsCache_[iCache];

	return aCoefficientsCache_[iCache] = minusOnePow((k+lc-l)/2 + m) * (2*k + 1) * fSqrt((2*l+1)*(2*lc+1)) * wigner3j(l, lc, k, 0, 0, 0) * wigner3j(l, lc, k, m, -m, 0);
}

double TranslationMatrixMathEngine::matrixElementInnerLoop(double R, int nc, int lc, int n, int l, int k, int kCache)
{
	if (innerLCaching_ && abs(R-innerLCacheR_) > 1e-7)
	{
		for (int i = maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_*maximumOrder_ - 1; i >= 0; --i)
		{
			innerLCache_[i] = 1e30;
		}

		innerLCacheR_ = R;
	}

	int iInnerLCache = 0;

	if (innerLCaching_)
	{
		iInnerLCache = nc * maximumOrder_ * maximumOrder_ * maximumOrder_ * maximumOrder_ 
			+ lc * maximumOrder_ * maximumOrder_ * maximumOrder_
			+ n * maximumOrder_ * maximumOrder_
			+ l * maximumOrder_ 
			+ kCache;

		if (innerLCache_[iInnerLCache] < 1e30) return innerLCache_[iInnerLCache];
	}

	double sum = 0.0;
	for (int j = 0; j <= n-l+nc-lc-2; ++j)
	{
		sum += cCoefficients(j, n, l, nc, lc) * factorial(j + (l+lc-k)/2) * laguerreL(j + (l+lc-k)/2, k + 0.5, R*R / (4*lambda_));
	}

	if (innerLCaching_)
	{
		return innerLCache_[iInnerLCache] = sum * pow(R*R/(4*lambda_), k/2.0) * exp(-R*R / (4*lambda_));
	}else
	{
		return sum * pow(R*R/(4*lambda_), k/2.0) * exp(-R*R / (4*lambda_));
	}
}

double TranslationMatrixMathEngine::matrixElement(double R, int nc, int lc, int n, int l, int m)
{
	double res = 0.0;
	int kCache = 0;

	for (int k = ((l-lc < 0)?(lc-l):(l-lc)); k <= l+lc; k += 2)
	{
		res += aCoefficients(k, kCache, l, lc, m) * matrixElementInnerLoop(R, nc, lc, n, l, k, kCache);
		++kCache;
	}

	return res;
}

double TranslationMatrixMathEngine::laguerreL(int k, double alpha, double x)
{
	if (k == 0) return 1.0;
	if (k == 1) return alpha + 1.0 - x;

	//return (1.0/k)*((2.0*(k-1.0)+alpha+1.0-x) * laguerreL(k-1, alpha, x) - ((k-1.0) + alpha) * laguerreL(k-2, alpha, x));

	double last = alpha + 1.0 - x, beforeLast = 1.0;

	for (int i = 2; i <= k; ++i)
	{
		double t = ((2*i + alpha - 1.0 - x)*last - (i - 1.0 + alpha)*beforeLast)/i;
		beforeLast = last;
		last = t;
	}

	return last;
}
