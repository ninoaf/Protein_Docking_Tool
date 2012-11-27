#ifndef TRANSLATIONMATRIXMATHENGINE_H_
#define TRANSLATIONMATRIXMATHENGINE_H_

#include <vector>
#include <string>

using namespace std;

class TranslationMatrixMathEngine
{
public:
	static TranslationMatrixMathEngine& getInstance();

	double matrixElement(double R, int nc, int lc, int n, int l, int m);
	void setInnerLoopCaching(bool value);
	bool getInnerLoopCaching();

private:
	double laguerreL(int k, double alpha, double x);
	double cCoefficients(int k, int n, int l, int nc, int lc);
	double xCoefficients(int n, int l, int j);
	double minusOnePow(int k);
	double factorial(int n);
	double halfFactorial(int n);
	double aCoefficients(int k, int kCache, int l, int lc, int m);
	double wigner3j(int j1, int j2, int j3, int m1, int m2, int m3);
	double matrixElementInnerLoop(double R, int nc, int lc, int n, int l, int k, int kCache);

	template <typename T> T abs(T x);
	double fSqrt(double y);
	void initSito();
	double power(int b, int p);
	double factorialSqrt(int x);
	double evalSuma(int *J, int *M, int k);
	int mozeFakt(int *J, int *M, int k);
	double calculate3j(int *J, int *M);
	int test3j(int j1, int j2, int j3, int m1, int m2, int m3);

	static double lambda_;
	static TranslationMatrixMathEngine* instance_;

	static int maximumOrder_;

	static int maxFactorialSqrt_;
	vector <int> minDiv_, prime_;
	vector <double> factoralSqrtCache_;

	bool innerLCaching_;
	double *innerLCache_;
	double innerLCacheR_;

	double *xCoefficientsCache_;
	double *aCoefficientsCache_;

	static int factorialCacheSize_;
	vector <double> factorialCache_;
	vector <double> halfFactorialCache_;

	TranslationMatrixMathEngine(); //
	~TranslationMatrixMathEngine(); //
};

#endif
