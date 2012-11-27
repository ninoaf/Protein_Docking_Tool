#include <cstdio>
#include "translationmatrixmathengine.h"
#include "translationmatrix.h"

int main()
{
	/*TranslationMatrixMathEngine& tm = TranslationMatrixMathEngine::getInstance();

	tm.setInnerLoopCaching(false);

	printf("%.20lf\n", tm.matrixElement(0.5, 8, 6, 5, 3, 2));
	printf("%.20lf\n", tm.matrixElement(5.5, 7, 6, 7, 4, 3));
	printf("%.20lf\n", tm.matrixElement(3.5, 4, 2, 5, 3, 2));
	printf("%.20lf\n", tm.matrixElement(3.5, 6, 1, 7, 4, 1));
	printf("%.20lf\n\n", tm.matrixElement(3.5, 9, 3, 2, 1, 1));
	tm.setInnerLoopCaching(true);
	printf("%.20lf\n", tm.matrixElement(3.5, 5, 3, 3, 1, 1)); 
	printf("%.20lf\n", tm.matrixElement(0.5, 5, 4, 8, 6, 4));
	printf("%.20lf\n", tm.matrixElement(1.5, 8, 6, 7, 3, 2)); 
	printf("%.20lf\n", tm.matrixElement(0.5, 5, 1, 8, 2, 1)); 
	printf("%.20lf\n", tm.matrixElement(2.0, 4, 2, 6, 5, 2)); 
	tm.setInnerLoopCaching(true);
	printf("%.20lf\n\n", tm.matrixElement(1.3, 4, 2, 6, 5, 2)); 
	printf("%.20lf\n", tm.matrixElement(1.3, 3, 2, 6, 5, 2)); 
	printf("%.20lf\n", tm.matrixElement(1.3, 3, 2, 7, 5, 2));*/

	TranslationMatrix tmm;

	tmm.calculateMatrix(35, 3.5);

	//tmm.dumpToFile("dumpedTranslationMatrix.txt");

	return 0;
}
