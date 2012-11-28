/*
 * evaluatescores.cpp
 *
 *  Created on: Jun 1, 2010
 *      Author: ivan
 */

#include "evaluatescores.h"

using namespace std;



void printMatrix(double *matrix, char *matrixName)
{
	int i=0, j=0;

	printf ("%s\n", matrixName);
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
			printf ("%.2lf\t", matrix[i*4+j]);
		printf ("\n");
	}
}

void getRotationMatrix(double angle, double x, double y, double z, double *retMatrix)
{
	int i=0;
	GLdouble matrix[16];

	glLoadIdentity();
//	printf ("getRotationMatrix(%.2lf, %.2lf, %.2lf, %.2lf)\n", angle, x, y, z);
    glRotated(angle, x, y, z);
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	for (i=0; i<16; i++)
	{
		retMatrix[i] = (double) matrix[i];
//		printf ("%.2f\t", ((float) matrix[i]));
	}

	glLoadIdentity();
}

void getTranslationMatrix(double x, double y, double z, double *retMatrix)
{
	int i=0;
	GLdouble matrix[16];

	glLoadIdentity();
	glTranslatef(x, y, z);
//	printf ("x = %.2lf\ty = %.2lf\tz = %.2lf\n", x, y, z);

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	for (i=0; i<16; i++)
		retMatrix[i] = (double) matrix[i];

	glLoadIdentity();
}

void multiplyMatrix(double *firstMatrix, double *secondMatrix, double *retMatrix)
{
	int i=0, j=0, k=0;
	double tempRetMatrix[16];

	for (i=0; i<16; i++)
		tempRetMatrix[i] = 0.0f;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0; k<4; k++)
			{
				tempRetMatrix[i*4+j] += firstMatrix[i*4+k] * secondMatrix[k*4+j];
			}
		}
	}

	for (i=0; i<16; i++)
		retMatrix[i] = tempRetMatrix[i];
}

void transformVectors(Coordinates point1, Coordinates point2, Coordinates point3, double *retMatrix)
{
	double vectorAngle=0.0f;
	double tempDouble=0.0f;
	Coordinates vector1, vector2;
	Coordinates rotationVector;

	vector1 = point2 - point1;
	vector2 = point3 - point1;

	tempDouble = (vector1.dotProduct(vector2)) / (vector1.magnitude() * vector2.magnitude());
	vectorAngle = acos(tempDouble) * 180.0l / 3.141592654l;
//	vectorAngle = 0.0f;
//    printf ("vectorAngle = %lf\n", vectorAngle);

    rotationVector = vector1.crossProduct(vector2);
    rotationVector.Normalize();

    getRotationMatrix(vectorAngle, rotationVector.x, rotationVector.y, rotationVector.z, retMatrix);
}

double getVectorAngle(Coordinates vector1, Coordinates vector2)
{
	double vectorAngle=0.0f;
	double tempDouble=0.0f;

	tempDouble = (vector1.dotProduct(vector2)) / (vector1.magnitude() * vector2.magnitude());
	vectorAngle = acos(tempDouble) * 180.0l / 3.141592654l;

	return vectorAngle;
}

void calculateAlignmentMatrix(Coordinates *referencePoints, double *retMatrix)
{
	Coordinates newReferencePoints[3];
	double matrixT1[16], matrixR1[16], matrixR2[16], matrixR3[16], tempMatrix0[16], tempMatrix1[16], tempMatrix2[16];
	Coordinates pointProjection1, pointProjection2, pointProjection3, pointProjection4, pointProjection5;
	Coordinates unitVector1, unitVector2, unitVector3;

/*
	newReferencePoints[0] = referencePoints[0] - referencePoints[0];
	newReferencePoints[1] = referencePoints[1] - referencePoints[0];
	newReferencePoints[2] = referencePoints[2] - referencePoints[0];
	getTranslationMatrix(-referencePoints[0].x, -referencePoints[0].y, -referencePoints[0].z, matrixT1);

	pointProjection1 = newReferencePoints[1];			pointProjection1.y = 0.0f;
	pointProjection2 = pointProjection1;				pointProjection2.z = 0.0f;
	transformVectors(pointProjection2, newReferencePoints[1], pointProjection1, matrixR1);

	printf ("pointProjection1: %lf\t%lf\t%lf\n", pointProjection1.x, pointProjection1.y, pointProjection1.z);

	pointProjection3 = pointProjection2;				pointProjection3.z = 0.0l;
	unitVector1.x = 1.0f;	unitVector1.y = 0.0f;	unitVector1.z = 0.0f;
	transformVectors(newReferencePoints[0], pointProjection1, unitVector1, matrixR2);

	multiplyMatrix(matrixT1, matrixR1, tempMatrix0);
	multiplyMatrix(tempMatrix0, matrixR2, tempMatrix1);
	multiplyMatrix(tempMatrix0, matrixR2, retMatrix);

	pointProjection3 = referencePoints[2];
	pointProjection3.multiplyMatrix(tempMatrix1);
	pointProjection4 = pointProjection3;				pointProjection4.y = 0.0f;
	pointProjection5 = pointProjection4;				pointProjection5.z = 0.0f;
	transformVectors(pointProjection5, pointProjection3, pointProjection4, matrixR3);

//	multiplyMatrix(tempMatrix1, matrixR3, retMatrix);
*/



	newReferencePoints[0] = referencePoints[0] - referencePoints[0];
	newReferencePoints[1] = referencePoints[1] - referencePoints[0];
	newReferencePoints[2] = referencePoints[2] - referencePoints[0];

//	newReferencePoints[1].Normalize();
//	newReferencePoints[2].Normalize();

	newReferencePoints[0].x = 0.0l;
	newReferencePoints[0].y = 0.0l;
	newReferencePoints[0].z = 0.0l;

//	printf ("dist1 = %lf\ndist2 = %lf\ndist3 = %lf\n\n", newReferencePoints[0].magnitude(), newReferencePoints[1].magnitude(), newReferencePoints[2].magnitude());

/*
	printf("newReferencePoints[0] = %lf\t%lf\t%lf\n", newReferencePoints[0].x, newReferencePoints[0].y, newReferencePoints[0].z);
	printf("newReferencePoints[1] = %lf\t%lf\t%lf\n", newReferencePoints[1].x, newReferencePoints[1].y, newReferencePoints[1].z);
	printf("newReferencePoints[2] = %lf\t%lf\t%lf\n\n", newReferencePoints[2].x, newReferencePoints[2].y, newReferencePoints[2].z);
*/

	getTranslationMatrix(-referencePoints[0].x, -referencePoints[0].y, -referencePoints[0].z, matrixT1);

//	printMatrix(matrixT1, "matrixT1");

/*
// ovako je to bilo prije
	pointProjection1 = newReferencePoints[1];
	pointProjection1.y = 0.0l;
//	pointProjection1.x = -pointProjection1.x;	pointProjection1.y = -pointProjection1.y;
//	unitVector1.x = 1.0f;	unitVector1.y = 0.0f;	unitVector1.z = 0.0f;
	transformVectors(newReferencePoints[0], newReferencePoints[1], pointProjection1, matrixR1);

//	printMatrix(matrixR1, "matrixR1");

	pointProjection2 = pointProjection1;
	pointProjection2.z = 0.0l;
	unitVector2.x = 1.0f;	unitVector2.y = 0.0f;	unitVector2.z = 0.0f;
	transformVectors(newReferencePoints[0], pointProjection1, unitVector2, matrixR2);
*/

	unitVector1.x = 1.0f;	unitVector1.y = 0.0f;	unitVector1.z = 0.0f;
	transformVectors(newReferencePoints[0], newReferencePoints[1], unitVector1, matrixR1);

//	printMatrix(matrixR1, "matrixR2");

	multiplyMatrix(matrixT1, matrixR1, tempMatrix1);
//	multiplyMatrix(tempMatrix0, matrixR2, tempMatrix1);
//	multiplyMatrix(matrixR1, matrixR2, tempMatrix1);

//	printMatrix(tempMatrix1, "tempMatrix1");

	pointProjection3 = referencePoints[2];
	pointProjection3.multiplyMatrix(tempMatrix1);
//	pointProjection3.Normalize();
//	pointProjection3.multiplyMatrix(matrixR1);
//	pointProjection3.multiplyMatrix(matrixR2);
	pointProjection4 = pointProjection3;
	pointProjection4.y = 0.0l;
//	pointProjection4.Normalize();
	pointProjection5 = pointProjection4;
	pointProjection5.z = 0.0l;
//	pointProjection5.Normalize();
//	transformVectors(newReferencePoints[0], pointProjection3, pointProjection4, matrixR3);

/*
	printf ("prva:  %lf\t%lf\t%lf\n", pointProjection5.x, pointProjection5.y, pointProjection5.z);
	printf ("druga: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
	printf ("treca: %lf\t%lf\t%lf\n\n", pointProjection4.x, pointProjection4.y, pointProjection4.z);
*/

//	transformVectors(pointProjection5, pointProjection3, pointProjection4, matrixR3);
	double vectorAngle=0.0f;
	Coordinates vector1, vector2, rotationVector;
	vector1 = (pointProjection3-pointProjection5);
	vector2 = (pointProjection4-pointProjection5);
	vectorAngle = getVectorAngle(vector1, vector2);
    rotationVector = vector1.crossProduct(vector2);
    rotationVector.Normalize();
    if (pointProjection3.z < 0)
    	vectorAngle += 180.0f;
    getRotationMatrix(vectorAngle, rotationVector.x, rotationVector.y, rotationVector.z, matrixR3);

//	getRotationMatrix(getVectorAngle((pointProjection3-pointProjection5), (pointProjection4-pointProjection5)), 1.0f, 0.0f, 0.0f, matrixR3);

	multiplyMatrix(tempMatrix1, matrixR3, retMatrix);

/*
	pointProjection3 = referencePoints[0];
	pointProjection3.multiplyMatrix(retMatrix);
	printf ("label1: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
	pointProjection3 = referencePoints[1];
	pointProjection3.multiplyMatrix(retMatrix);
	printf ("label2: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
	pointProjection3 = referencePoints[2];
	pointProjection3.multiplyMatrix(retMatrix);
	printf ("label3: %lf\t%lf\t%lf\n\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);


	pointProjection3 = referencePoints[0];
	pointProjection3.multiplyMatrix(tempMatrix1);
	printf ("tempM: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
	pointProjection3 = referencePoints[1];
	pointProjection3.multiplyMatrix(tempMatrix1);
	printf ("tempM: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
	pointProjection3 = referencePoints[2];
	pointProjection3.multiplyMatrix(tempMatrix1);
	printf ("tempM: %lf\t%lf\t%lf\n", pointProjection3.x, pointProjection3.y, pointProjection3.z);
*/

//	printMatrix(matrixR3, "matrixR3");

/////
//	multiplyMatrix(tempMatrix1, matrixR3, tempMatrix2);
//	multiplyMatrix(matrixT1, tempMatrix2, retMatrix);
/////

//	multiplyMatrix(matrixR3, tempMatrix1, tempMatrix2);
//	multiplyMatrix(tempMatrix2, matrixT1, retMatrix);

//	multiplyMatrix(tempMatrix1, matrixR3, retMatrix);
//	multiplyMatrix(matrixT1, tempMatrix1, retMatrix);

//	multiplyMatrix(matrixT1, tempMatrix1, retMatrix);
//	multiplyMatrix(matrixT1, matrixR1, retMatrix);

//	printf ("----------------------------------------\n\n");
}

void evaluateScores(PdbFile *complex, PdbFile *ligand, PdbFile *receptor, PdbFile &complexCopy, PdbFile &receptorCopy, PdbFile &ligandCopy, ScoreLoader &scoreData)
{
//	PdbFile *complex=NULL, *ligand=NULL, *receptor=NULL;
//	PdbFile complexCopy, ligandCopy, receptorCopy;
//	Coordinates referencePoints[3];

//	alignTwoPdb(*complex, *receptor, receptorIndex);

//	alignTwoPdb(*complex, *ligand, ligandIndex);

//	alignThreePdb(*complex, *receptor, *ligand);

//	evaluateScores(*complex, *receptor, *ligand, complexCopy, receptorCopy, ligandCopy, (string) "data/rmsd/testScores1.rmsd", scoreData, 0, 1000);
	evaluateScores(*complex, *receptor, *ligand, complexCopy, receptorCopy, ligandCopy, (string) "data/rmsd/3hfl_36_alfa_53.rmsd", scoreData, 0, 5000);

//	printf ("Asd 1!\n");
//	evaluateScores(*complex, *receptor, *ligand, complexCopy, receptorCopy, ligandCopy, (string) "data/scr/3hfl_36_alfa_53/outputMPI.scr", (string) "data/rmsd/3hfl_36_alfa_53.rmsd", currentScore, 1);
//	printf ("Asd 2!\n");

/*
	referencePoints[0].x = complex->getAtom(receptorIndex[0])->x;	referencePoints[0].y = complex->getAtom(receptorIndex[0])->y;	referencePoints[0].z = complex->getAtom(receptorIndex[0])->z;
	referencePoints[1].x = complex->getAtom(receptorIndex[1])->x;	referencePoints[1].y = complex->getAtom(receptorIndex[1])->y;	referencePoints[1].z = complex->getAtom(receptorIndex[1])->z;
	referencePoints[2].x = complex->getAtom(receptorIndex[2])->x;	referencePoints[2].y = complex->getAtom(receptorIndex[2])->y;	referencePoints[2].z = complex->getAtom(receptorIndex[2])->z;
	pdbWriter.alignPDB(*complex, referencePoints);

	referencePoints[0].x = receptor->getAtom(0)->x;	referencePoints[0].y = receptor->getAtom(0)->y;	referencePoints[0].z = receptor->getAtom(0)->z;
	referencePoints[1].x = receptor->getAtom(1)->x;	referencePoints[1].y = receptor->getAtom(1)->y;	referencePoints[1].z = receptor->getAtom(1)->z;
	referencePoints[2].x = receptor->getAtom(2)->x;	referencePoints[2].y = receptor->getAtom(2)->y;	referencePoints[2].z = receptor->getAtom(2)->z;
	pdbWriter.alignPDB(*receptor, referencePoints);

	referencePoints[0].x = receptor->getAtom(0)->x;	referencePoints[0].y = receptor->getAtom(0)->y;	referencePoints[0].z = receptor->getAtom(0)->z;
	referencePoints[1].x = receptor->getAtom(1)->x;	referencePoints[1].y = receptor->getAtom(1)->y;	referencePoints[1].z = receptor->getAtom(1)->z;
	referencePoints[2].x = receptor->getAtom(2)->x;	referencePoints[2].y = receptor->getAtom(2)->y;	referencePoints[2].z = receptor->getAtom(2)->z;
	pdbWriter.alignPDB(*ligand, referencePoints);
*/
}

void evaluateScores(PdbFile &complexPdb, PdbFile &receptorPdb, PdbFile &ligandPdb, PdbFile &complexCopy, PdbFile &receptorCopy, PdbFile &ligandCopy, string outRMSDPath, ScoreLoader &scoresData, int startingScore, int maxNumScores)
{
	unsigned int i=0, j=0;
	double matrixComplex[16], matrixReceptor[16];
	PdbWriter pdbWriter;
	vector<int> indexComplex, indexReceptor, indexLigand;
	Coordinates referencePointsComplex[3], referencePointsReceptor[3];
//	PdbFile transformedLigand, transformedReceptor;
	double retError=0.0f;
	double distance=0.0f;
	FILE *fpOutRMSD;

//	printf ("Asd 3!\n");

	fpOutRMSD = fopen(outRMSDPath.c_str(), "w");

	pdbWriter.indexAtoms(complexCopy, receptorCopy, ligandCopy, indexComplex, indexReceptor, indexLigand);

	referencePointsComplex[0].x = complexCopy.getAtom(indexReceptor[0])->x;	referencePointsComplex[0].y = complexCopy.getAtom(indexReceptor[0])->y;	referencePointsComplex[0].z = complexCopy.getAtom(indexReceptor[0])->z;
	referencePointsComplex[1].x = complexCopy.getAtom(indexReceptor[1])->x;	referencePointsComplex[1].y = complexCopy.getAtom(indexReceptor[1])->y;	referencePointsComplex[1].z = complexCopy.getAtom(indexReceptor[1])->z;
	referencePointsComplex[2].x = complexCopy.getAtom(indexReceptor[2])->x;	referencePointsComplex[2].y = complexCopy.getAtom(indexReceptor[2])->y;	referencePointsComplex[2].z = complexCopy.getAtom(indexReceptor[2])->z;

//	printf ("complexLine1: %s\n", complexPdb.getAtom(indexReceptor[0])->originalLine.c_str());
//	printf ("complexLine2: %s\n", complexPdb.getAtom(indexReceptor[1])->originalLine.c_str());
//	printf ("complexLine3: %s\n", complexPdb.getAtom(indexReceptor[2])->originalLine.c_str());

//	printf ("receptorLine1: %s\n", receptorPdb.getAtom(0)->originalLine.c_str());
//	printf ("receptorLine2: %s\n", receptorPdb.getAtom(1)->originalLine.c_str());
//	printf ("receptorLine3: %s\n", receptorPdb.getAtom(2)->originalLine.c_str());

	calculateAlignmentMatrix(referencePointsComplex, matrixComplex);

	for (i=0; i<complexPdb.getAtomList().size(); i++)
	{
		complexPdb.getAtomList()[i] = complexCopy.getAtomList()[i].transformCoordinates(matrixComplex, ' ');
	}

/*
	for (i=0; i<complexPdb.getModels().size(); i++)
	{
		for (j=0; j<complexPdb.getModels()[i].getAtoms().size(); j++)
		{
			complexPdb.getModels()[i].getAtoms()[j] = complexPdb.getModels()[i].getAtoms()[j].transformCoordinates(matrixComplex, ' ');
		}
	}
*/



	fprintf (fpOutRMSD, "# RMSD Evaluation of PDT score results.\n");
//	fprintf (fpOutRMSD, "# scorePath: %s\n", scorePath.c_str());
	fprintf (fpOutRMSD, "# startingScore: %d\n", startingScore);
	fprintf (fpOutRMSD, "# maxNumScores: %d\n", maxNumScores);
	fprintf (fpOutRMSD, "#\n");
	fprintf (fpOutRMSD, "# Line description:\n");
	fprintf (fpOutRMSD, "# RMSD\t\t# rank score R betaR gammaR alphaL betaL gammaL\n");

	for (i=startingScore; (i<scoresData.scores.size() && ((i-startingScore)<maxNumScores || maxNumScores<0)); i++)
	{
//		printf ("Beginning score #%d!\n", i);

		retError = 0.0f;

		receptorCopy.createTransformedPdbFile(receptorPdb, 0.0f, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
		ligandCopy.createTransformedPdbFile(ligandPdb, scoresData.scores[i].radius, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);

		referencePointsReceptor[0].x = receptorPdb.getAtom(0)->x;	referencePointsReceptor[0].y = receptorPdb.getAtom(0)->y;	referencePointsReceptor[0].z = receptorPdb.getAtom(0)->z;
		referencePointsReceptor[1].x = receptorPdb.getAtom(1)->x;	referencePointsReceptor[1].y = receptorPdb.getAtom(1)->y;	referencePointsReceptor[1].z = receptorPdb.getAtom(1)->z;
		referencePointsReceptor[2].x = receptorPdb.getAtom(2)->x;	referencePointsReceptor[2].y = receptorPdb.getAtom(2)->y;	referencePointsReceptor[2].z = receptorPdb.getAtom(2)->z;

		calculateAlignmentMatrix(referencePointsReceptor, matrixReceptor);

/*
		printf ("receptor(0): %lf\t%lf\t%lf\n", receptorPdb.getAtom(0)->x, receptorPdb.getAtom(0)->y, receptorPdb.getAtom(0)->z);
		printf ("receptor(1): %lf\t%lf\t%lf\n", receptorPdb.getAtom(1)->x, receptorPdb.getAtom(1)->y, receptorPdb.getAtom(1)->z);
		printf ("receptor(2): %lf\t%lf\t%lf\n\n", receptorPdb.getAtom(2)->x, receptorPdb.getAtom(2)->y, receptorPdb.getAtom(2)->z);
*/

		for (j=0; j<receptorPdb.getAtomList().size(); j++)
		{
//			receptorPdb.getAtomList()[j] = receptorPdb.getAtomList()[j].transformCoordinates(matrixReceptor, ' ');
//			receptorPdb.getAtom(j)->z -= 100;
//			receptorPdb.getAtom(j)->x -= referencePointsReceptor[0].x;
//			receptorPdb.getAtom(j)->y -= referencePointsReceptor[0].y;
//			receptorPdb.getAtom(j)->z -= referencePointsReceptor[0].z;

			receptorPdb.getAtomList()[j] = receptorPdb.getAtomList()[j].transformCoordinates(matrixReceptor, ' ');

			retError += ((complexPdb.getAtom(indexReceptor[j])->x - receptorPdb.getAtom(j)->x)*(complexPdb.getAtom(indexReceptor[j])->x - receptorPdb.getAtom(j)->x) +
						 (complexPdb.getAtom(indexReceptor[j])->y - receptorPdb.getAtom(j)->y)*(complexPdb.getAtom(indexReceptor[j])->y - receptorPdb.getAtom(j)->y) +
						 (complexPdb.getAtom(indexReceptor[j])->z - receptorPdb.getAtom(j)->z)*(complexPdb.getAtom(indexReceptor[j])->z - receptorPdb.getAtom(j)->z));
		}

/*
		printf ("receptor(0): %lf\t%lf\t%lf\n", receptorPdb.getAtom(0)->x, receptorPdb.getAtom(0)->y, receptorPdb.getAtom(0)->z);
		printf ("complex(0):  %lf\t%lf\t%lf\n\n", complexPdb.getAtom(indexReceptor[0])->x, complexPdb.getAtom(indexReceptor[0])->y, complexPdb.getAtom(indexReceptor[0])->z);

		printf ("receptor(1): %lf\t%lf\t%lf\n", receptorPdb.getAtom(1)->x, receptorPdb.getAtom(1)->y, receptorPdb.getAtom(1)->z);
		printf ("complex(1):  %lf\t%lf\t%lf\n\n", complexPdb.getAtom(indexReceptor[1])->x, complexPdb.getAtom(indexReceptor[1])->y, complexPdb.getAtom(indexReceptor[1])->z);

		printf ("receptor(2): %lf\t%lf\t%lf\n", receptorPdb.getAtom(2)->x, receptorPdb.getAtom(2)->y, receptorPdb.getAtom(2)->z);
		printf ("complex(2):  %lf\t%lf\t%lf\n\n", complexPdb.getAtom(indexReceptor[2])->x, complexPdb.getAtom(indexReceptor[2])->y, complexPdb.getAtom(indexReceptor[2])->z);
*/

		for (j=0; j<ligandPdb.getAtomList().size(); j++)
		{
			ligandPdb.getAtomList()[j] = ligandPdb.getAtomList()[j].transformCoordinates(matrixReceptor, ' ');

			retError += ((complexPdb.getAtom(indexLigand[j])->x - ligandPdb.getAtom(j)->x)*(complexPdb.getAtom(indexLigand[j])->x - ligandPdb.getAtom(j)->x) +
						 (complexPdb.getAtom(indexLigand[j])->y - ligandPdb.getAtom(j)->y)*(complexPdb.getAtom(indexLigand[j])->y - ligandPdb.getAtom(j)->y) +
						 (complexPdb.getAtom(indexLigand[j])->z - ligandPdb.getAtom(j)->z)*(complexPdb.getAtom(indexLigand[j])->z - ligandPdb.getAtom(j)->z));
		}

		retError = sqrt(retError / complexPdb.getAtomList().size());

//		fprintf (fpOutRMSD, "RMSD %d: %lf\n", i, retError);
		fprintf (fpOutRMSD, "%lf\t\t # %d %f\t\t%f\t%f\t%f\t%f\t%f\t%f\n", retError, i, scoresData.scores[i].score, scoresData.scores[i].radius, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);

		printf ("Score #%d: %lf\r", i, retError);
	}

	printf ("\n");

	fclose(fpOutRMSD);
}
