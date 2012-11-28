/*
 * pdbwriter.cpp
 *
 *  Created on: Mar 19, 2010
 *      Author: ivan
 */

#include "pdbwriter.h"

using namespace std;



PdbWriter::PdbWriter()
{
	init();
}

PdbWriter::~PdbWriter()
{
	init();
}

/*
void PdbWriter::Write(string scrPath, string outPdbPath)
{

}
*/

void PdbWriter::init()
{

}

// int PdbWriter::write(vector <pair<double, ScoreConfiguration> > scores, string receptorPath, string ligandPath, string radiiPath, string outPdbPath)

int PdbWriter::write(string scorePath, string receptorPath, string ligandPath, string radiiPath, string outPdbPath, int startingScore, int maxNumScores, int centerAtoms)
{
	PdbFile ligandPDB, receptorPDB;
	FILE *fpPDB=NULL;
	ScoreLoader scoresData;

	if (ligandPath=="" || receptorPath=="" || radiiPath=="")
	{
		printf ("Invalid path.\n");
		return 0;
	}

	if (scoresData.loadScoresFromFile(scorePath) == false)
	{
		printf ("Could not open file %s!\n", scorePath.c_str());
		return 0;
	}

	fpPDB = fopen(outPdbPath.c_str(), "w");
	if (fpPDB == NULL)
	{
		printf ("Could not open file %s!\n", outPdbPath.c_str());
		return 0;
	}

	ligandPDB.Init((char *) ligandPath.c_str());
	if (!ligandPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open file %s!\n", radiiPath.c_str());
		return 0;
	}
	ligandPDB.UseUnitedRadius();
	if (centerAtoms == 1)	ligandPDB.centerAtomsByMass();
	else if (centerAtoms == 2)	ligandPDB.centerAtomsArithmetically();
	ligandPDB.Import((bool) centerAtoms);

	receptorPDB.Init((char *) receptorPath.c_str());
	if (!receptorPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open file %s!\n", radiiPath.c_str());
		return 0;
	}
	receptorPDB.UseUnitedRadius();
	if (centerAtoms == 1)	receptorPDB.centerAtomsByMass();
	else if (centerAtoms == 2)	receptorPDB.centerAtomsArithmetically();
	receptorPDB.Import(centerAtoms);

//	sort(scores.begin(), scores.end(), greater<pair<double, ScoreConfiguration> > ());


//	fprintf(fp, "# rank score R betaReceptor gammaReceptor alphaLigand betaLigand gammaLigand\n");
/*
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
//		fprintf(fp, "%d %lf %lf %lf %lf %lf %lf %lf\n", i + 1, scores[i].first, scores[i].second.R,
//				rotationAngles_[scores[i].second.receptorRA].beta, rotationAngles_[scores[i].second.receptorRA].gamma,
//				scores[i].second.alphaLigand, rotationAngles_[scores[i].second.ligandRA].beta, rotationAngles_[scores[i].second.ligandRA].gamma);

		if (ligandPath_!="" && receptorPath_!="" && radiiPath_!="")
		{
			fprintf (fpPDB, "MODEL %d\n", i);
			receptorPDB.WriteTransformedAtoms(fpPDB, 'R', scores[i].second.R, 0.0f, scores[i].second.beta1, scores[i].second.gamma1);
			fprintf (fpPDB, "TER\n");
			ligandPDB.WriteTransformedAtoms(fpPDB, 'L', 0.0f, scores[i].second.alpha, scores[i].second.beta2, scores[i].second.gamma2);
			fprintf (fpPDB, "TER\n");
			fprintf (fpPDB, "ENDMDL\n");
		}
	}
*/

//	printf ("%s\n%s\n", receptorPath.c_str(), ligandPath.c_str());
//	printf ("receotor i ligand: %d\t%d\n", receptorPDB.getNumAtoms(), ligandPDB.getNumAtoms());

	for (unsigned int i=startingScore; (i<scoresData.scores.size() && ((i-startingScore)<maxNumScores || maxNumScores<0)); i++)
	{
		fprintf (fpPDB, "MODEL %d\n", i);
		receptorPDB.writeTransformedAtoms(fpPDB, 'R', 0.0, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
		fprintf (fpPDB, "TER\n");
		ligandPDB.writeTransformedAtoms(fpPDB, 'L', scoresData.scores[i].radius, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);
		fprintf (fpPDB, "TER\n");
		fprintf (fpPDB, "ENDMDL\n");
	}

	fclose(fpPDB);

	return 1;
}

int PdbWriter::write(PdbFile &receptor, PdbFile &ligand, ScoreLoader &scoresData, string outPdbPath, int startingScore, int maxNumScores, bool changeChains)
{
	char receptorChain='R', ligandChain='L';
	FILE *fpPDB=NULL;

	fpPDB = fopen(outPdbPath.c_str(), "w");
	if (fpPDB == NULL)
	{
		printf ("Could not open file %s!\n", outPdbPath.c_str());
		return 1;
	}

	if (changeChains == true)
	{
		receptorChain = ' ';
		ligandChain = ' ';
	}

	for (unsigned int i=startingScore; (i<scoresData.scores.size() && ((i-startingScore)<maxNumScores || maxNumScores<0)); i++)
	{
		fprintf (fpPDB, "MODEL %d\n", i);
		receptor.writeTransformedAtoms(fpPDB, receptorChain, 0.0f, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
		fprintf (fpPDB, "TER\n");
		ligand.writeTransformedAtoms(fpPDB, ligandChain, scoresData.scores[i].radius, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);
		fprintf (fpPDB, "TER\n");
		fprintf (fpPDB, "ENDMDL\n");
	}

	fclose(fpPDB);

	return 0;
}

void PdbWriter::mojGetch()
{
	char tempChar;
	scanf("%c", &tempChar);
}

double PdbWriter::evaluateRMSD(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, vector<int> &complexIndex, vector<int> &receptorIndex, vector<int> &ligandIndex)
{
	unsigned int i=0;
	double distance_2=0.0f, ret=0.0f;
	AtomPdb *complexAtom;
	AtomPdb *receptorAtom;
	AtomPdb *ligandAtom;

	for (i=0; i<receptor.getNumAtoms(); i++)
	{
		receptorAtom = receptor.getAtom(i);
		complexAtom = complex.getAtom(receptorIndex[i]);

		distance_2 = (complexAtom->x-receptorAtom->x)*(complexAtom->x-receptorAtom->x) +
					 (complexAtom->y-receptorAtom->y)*(complexAtom->y-receptorAtom->y) +
					 (complexAtom->z-receptorAtom->z)*(complexAtom->z-receptorAtom->z);

		ret += distance_2;
	}

	for (i=0; i<ligand.getNumAtoms(); i++)
	{
		ligandAtom = ligand.getAtom(i);
		complexAtom = complex.getAtom(ligandIndex[i]);

		distance_2 = (complexAtom->x-ligandAtom->x)*(complexAtom->x-ligandAtom->x) +
					 (complexAtom->y-ligandAtom->y)*(complexAtom->y-ligandAtom->y) +
					 (complexAtom->z-ligandAtom->z)*(complexAtom->z-ligandAtom->z);

		ret += distance_2;
	}

	ret /= (receptor.getNumAtoms() + ligand.getNumAtoms());

	ret = sqrt(ret);

	return ret;
}

bool PdbWriter::compareAtomLines(AtomPdb *firstAtom, AtomPdb *secondAtom)
{
	if (firstAtom->originalLine.substr(0, 29)==secondAtom->originalLine.substr(0, 29) &&
		firstAtom->originalLine.substr(54, 25)==secondAtom->originalLine.substr(54, 25))
		return true;

	return false;
}

void PdbWriter::indexAtoms(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, vector<int> &complexIndex, vector<int> &receptorIndex, vector<int> &ligandIndex)
{
	unsigned int i=0, j=0;
	bool indexFound=false;
	AtomPdb *complexAtom;
	AtomPdb *receptorAtom;
	AtomPdb *ligandAtom;
	unsigned int tempc=0, tempr=0, templ=0;

	complexIndex.clear();
	ligandIndex.clear();
	receptorIndex.clear();

	for (i=0; i<complex.getNumAtoms(); i++)
		complexIndex.push_back(-1);
	for (i=0; i<receptor.getNumAtoms(); i++)
		receptorIndex.push_back(-1);
	for (i=0; i<ligand.getNumAtoms(); i++)
		ligandIndex.push_back(-1);

	for (i=0; i<complex.getNumAtoms(); i++)
	{
		complexAtom = complex.getAtom(i);

		indexFound = false;

		for (j=0; j<receptor.getNumAtoms(); j++)
		{
			receptorAtom = receptor.getAtom(j);

			if (compareAtomLines(receptorAtom, complexAtom) == true)
//			if (receptorAtom->originalLine == complexAtom->originalLine)
			{
				complexIndex[i] = j;
				receptorIndex[j] = i;
				indexFound = true;

				tempr += 1;
				tempc += 1;

/*
				if (complexAtom->x!=receptorAtom->x || complexAtom->y!=receptorAtom->y || complexAtom->z!=receptorAtom->z)
				{
					printf ("Receptor:\n");
					printf ("%s\n%s\n\n", complexAtom->originalLine.c_str(), receptorAtom->originalLine.c_str());
					mojGetch();
				}
*/

				break;
			}
		}

		for (j=0; (j<ligand.getNumAtoms() && indexFound==false); j++)
		{
			ligandAtom = ligand.getAtom(j);

			if (compareAtomLines(ligandAtom, complexAtom) == true)
			{
				complexIndex[i] = j;
				ligandIndex[j] = i;
				indexFound = true;

				templ += 1;
				tempc += 1;

/*
				if (complexAtom->x!=ligandAtom->x || complexAtom->y!=ligandAtom->y || complexAtom->z!=ligandAtom->z)
				{
					printf ("Ligand:\n");
					printf ("%s\n%s\n\n", complexAtom->originalLine.c_str(), ligandAtom->originalLine.c_str());
					mojGetch();
				}
*/

				break;
			}
		}

/*
		if (indexFound == false)
		{
			printf ("Nekaj gadno ne stima!\n");
			printf ("-------------------------------------\n");
			printf ("%d\n", i);
			printf ("%s\n", complexAtom->originalLine.c_str());
 			return;
		}
*/
	}

//	printf ("Found:\n\tcomplex = %d (%d)\n\treceptor = %d (%d)\n\tligand = %d (%d)\n", tempc, complex.getNumAtoms(), tempr, receptor.getNumAtoms(), templ, ligand.getNumAtoms());
}

int PdbWriter::evaluateScores(string scorePath, string complexPath, string receptorPath, string ligandPath, string radiiPath, string outEvaluationPath, string outPdbPath, string outComplexPath, int startingScore, int maxNumScores, int centerAtoms)
{
	double evaluationResult=0.0f;
	Coordinates referencePoints[3];
	PdbFile complexPDB, ligandPDB, receptorPDB, transformedLigand, transformedReceptor;
	FILE *fpEvaluation=NULL;
	FILE *fpPDB=NULL;
	FILE *fpComplex=NULL;
	ScoreLoader scoresData;
	vector<int> complexIndex, receptorIndex, ligandIndex;

	if (ligandPath=="" || receptorPath=="" || radiiPath=="")
	{
		printf ("Invalid path.\n");
		return 0;
	}

	if (scoresData.loadScoresFromFile(scorePath) == false)
	{
		printf ("Could not open scores file %s!\n", scorePath.c_str());
		return 0;
	}

	fpEvaluation = fopen(outEvaluationPath.c_str(), "w");
	if (fpEvaluation == NULL)
	{
		printf ("Could not open output file %s!\n", outEvaluationPath.c_str());
		return 0;
	}

	fpPDB = fopen(outPdbPath.c_str(), "w");
	if (fpPDB == NULL)
	{
		printf ("Could not open output file %s!\n", outPdbPath.c_str());
		return 0;
	}

	fpComplex = fopen(outComplexPath.c_str(), "w");
	if (fpComplex == NULL)
	{
		printf ("Could not open output file %s!\n", outComplexPath.c_str());
		return 0;
	}

	complexPDB.Init((char *) complexPath.c_str());
	if (!complexPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open complex file %s!\n", radiiPath.c_str());
		return 0;
	}
	complexPDB.UseUnitedRadius();
	if (centerAtoms == 1)	complexPDB.centerAtomsByMass();
	else if (centerAtoms == 2)	complexPDB.centerAtomsArithmetically();
	complexPDB.Import((bool) centerAtoms);

	ligandPDB.Init((char *) ligandPath.c_str());
	if (!ligandPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open ligand file %s!\n", radiiPath.c_str());
		return 0;
	}
	ligandPDB.UseUnitedRadius();
	if (centerAtoms == 1)	ligandPDB.centerAtomsByMass();
	else if (centerAtoms == 2)	ligandPDB.centerAtomsArithmetically();
	ligandPDB.Import((bool) centerAtoms);

	receptorPDB.Init((char *) receptorPath.c_str());
	if (!receptorPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open receptor file %s!\n", radiiPath.c_str());
		return 0;
	}
	receptorPDB.UseUnitedRadius();
	if (centerAtoms == 1)	receptorPDB.centerAtomsByMass();
	else if (centerAtoms == 2)	receptorPDB.centerAtomsArithmetically();
	receptorPDB.Import((bool) centerAtoms);

	indexAtoms(complexPDB, receptorPDB, ligandPDB, complexIndex, receptorIndex, ligandIndex);
	printf ("\n");

//	alignPdbByReceptor(complexPDB, receptorPDB, ligandPDB, complexIndex, receptorIndex, ligandIndex);
	referencePoints[0].x = complexPDB.getAtom(receptorIndex[0])->x;	referencePoints[0].y = complexPDB.getAtom(receptorIndex[0])->y;	referencePoints[0].z = complexPDB.getAtom(receptorIndex[0])->z;
	referencePoints[1].x = complexPDB.getAtom(receptorIndex[1])->x;	referencePoints[1].y = complexPDB.getAtom(receptorIndex[1])->y;	referencePoints[1].z = complexPDB.getAtom(receptorIndex[1])->z;
	referencePoints[2].x = complexPDB.getAtom(receptorIndex[2])->x;	referencePoints[2].y = complexPDB.getAtom(receptorIndex[2])->y;	referencePoints[2].z = complexPDB.getAtom(receptorIndex[2])->z;
	alignPDB(complexPDB, referencePoints);

	complexPDB.writeAtoms(fpComplex);
	fclose(fpComplex);

/** Ovo je bilo upaljeno po defaultu.
* Datum 28.11.2012.
	printf ("\tConformation TEST: RMSD = %lf\n", evaluateRMSD(complexPDB, receptorPDB, ligandPDB, complexIndex, receptorIndex, ligandIndex));
*/


	fprintf (fpEvaluation, "# RMSD Evaluation of PDT score results.\n");
	fprintf (fpEvaluation, "# complexPath: %s\n", complexPath.c_str());
	fprintf (fpEvaluation, "# receptorPath: %s\n", receptorPath.c_str());
	fprintf (fpEvaluation, "# ligandPath: %s\n", ligandPath.c_str());
	fprintf (fpEvaluation, "# scorePath: %s\n", scorePath.c_str());
	fprintf (fpEvaluation, "# outEvaluationPath: %s\n", scorePath.c_str());
	fprintf (fpEvaluation, "# radiiPath: %s\n", radiiPath.c_str());
	fprintf (fpEvaluation, "# startingScore: %d\n", startingScore);
	fprintf (fpEvaluation, "# maxNumScores: %d\n", maxNumScores);
	fprintf (fpEvaluation, "# centerAtoms: %d\n", (int) centerAtoms);
	fprintf (fpEvaluation, "#\n");
	fprintf (fpEvaluation, "# Line description:\n");
	fprintf (fpEvaluation, "# RMSD\t\t# rank score R betaR gammaR alphaL betaL gammaL\n");

	for (unsigned int i=startingScore; (i<scoresData.scores.size() && ((i-startingScore)<maxNumScores || maxNumScores<0)); i++)
	{
/** Ovo je bilo upaljeno po defaultu.
* Datum 28.11.2012.
		printf ("Beginning score #%d!\n", i);
*/

		receptorPDB.createTransformedPdbFile(transformedReceptor, scoresData.scores[i].radius, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
		ligandPDB.createTransformedPdbFile(transformedLigand, 0.0f, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);

		referencePoints[0].x = transformedReceptor.getAtom(0)->x;	referencePoints[0].y = transformedReceptor.getAtom(0)->y;	referencePoints[0].z = transformedReceptor.getAtom(0)->z;
		referencePoints[1].x = transformedReceptor.getAtom(1)->x;	referencePoints[1].y = transformedReceptor.getAtom(1)->y;	referencePoints[1].z = transformedReceptor.getAtom(1)->z;
		referencePoints[2].x = transformedReceptor.getAtom(2)->x;	referencePoints[2].y = transformedReceptor.getAtom(2)->y;	referencePoints[2].z = transformedReceptor.getAtom(2)->z;
		alignPDB(transformedReceptor, referencePoints);

		referencePoints[0].x = transformedReceptor.getAtom(0)->x;	referencePoints[0].y = transformedReceptor.getAtom(0)->y;	referencePoints[0].z = transformedReceptor.getAtom(0)->z;
		referencePoints[1].x = transformedReceptor.getAtom(1)->x;	referencePoints[1].y = transformedReceptor.getAtom(1)->y;	referencePoints[1].z = transformedReceptor.getAtom(1)->z;
		referencePoints[2].x = transformedReceptor.getAtom(2)->x;	referencePoints[2].y = transformedReceptor.getAtom(2)->y;	referencePoints[2].z = transformedReceptor.getAtom(2)->z;
		alignPDB(transformedLigand, referencePoints);

//		printf ("%f\t%f\t%f\t%f\n", scoresData.scores[i].radius, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
//		printf ("%f\t%f\t%f\t%f\n", 0.0f, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);

//		evaluateRMSD(complexPDB, receptorPDB, ligandPDB, complexIndex, receptorIndex, ligandIndex);
//		indexAtoms(complexPDB, transformedReceptor, transformedLigand, complexIndex, receptorIndex, ligandIndex);
		evaluationResult = evaluateRMSD(complexPDB, transformedReceptor, transformedLigand, complexIndex, receptorIndex, ligandIndex);

		printf ("\r\tConformation #%d: RMSD = %lf", i, evaluationResult);
		fflush(stdout);

		fprintf (fpEvaluation, "%lf\t\t# %d %f\t%f\t%f\t%f\t%f\t%f\t%f\n", evaluationResult, i, scoresData.scores[i].score, scoresData.scores[i].radius, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);

		fprintf (fpPDB, "MODEL %d\n", i);
		transformedReceptor.writeAtoms(fpPDB);
		fprintf (fpPDB, "TER\n");
		transformedLigand.writeAtoms(fpPDB);
		fprintf (fpPDB, "TER\n");
		fprintf (fpPDB, "ENDMDL\n");
	}

	fclose(fpEvaluation);
	fclose(fpPDB);

	printf ("\n");
	fflush(stdout);

	return 1;
}

/*
// void PdbWriter::alignComplexByReceptor(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, vector<int> complexIndex, vector<int> receptorIndex, vector<int> ligandIndex)
void PdbWriter::alignComplexByReceptor(PdbFile &complex, vector<int> receptorIndex)
{
	unsigned int i=0;
	double alphaC=0.0f, betaC=0.0f, gammaC=0.0f;
	double alphaR=0.0f, betaR=0.0f, gammaR=0.0f;
	double transformMatrix[16];
	Atom transformedAtom;
	Coordinates vectorC[2], vectorR[2];
	Coordinates translationC, translationR;

/////
	vectorC[0].x = complex.getAtom(receptorIndex[0])->x - complex.getAtom(receptorIndex[1])->x;
	vectorC[0].y = complex.getAtom(receptorIndex[0])->y - complex.getAtom(receptorIndex[1])->y;
	vectorC[0].z = complex.getAtom(receptorIndex[0])->z - complex.getAtom(receptorIndex[1])->z;
	vectorC[0].Normalize();

	vectorC[1].x = complex.getAtom(receptorIndex[0])->x - complex.getAtom(receptorIndex[2])->x;
	vectorC[1].y = complex.getAtom(receptorIndex[0])->y - complex.getAtom(receptorIndex[2])->y;
	vectorC[1].z = complex.getAtom(receptorIndex[0])->z - complex.getAtom(receptorIndex[2])->z;
	vectorC[1].Normalize();
/////
	vectorR[0].x = receptor.getAtom(0)->x - receptor.getAtom(1)->x;
	vectorR[0].y = receptor.getAtom(0)->y - receptor.getAtom(1)->y;
	vectorR[0].z = receptor.getAtom(0)->z - receptor.getAtom(1)->z;
	vectorR[0].Normalize();

	vectorR[1].x = receptor.getAtom(0)->x - receptor.getAtom(2)->x;
	vectorR[1].y = receptor.getAtom(0)->y - receptor.getAtom(2)->y;
	vectorR[1].z = receptor.getAtom(0)->z - receptor.getAtom(2)->z;
	vectorR[1].Normalize();
/////

	translationC.x = complex.getAtom(receptorIndex[0])->x;
	translationC.y = complex.getAtom(receptorIndex[0])->y;
	translationC.z = complex.getAtom(receptorIndex[0])->z;

	translationR.x = complex.getAtom(0)->x;
	translationR.y = complex.getAtom(0)->y;
	translationR.z = complex.getAtom(0)->z;
/////

	complex.makeTransformMatrix(transformMatrix, 0, gammaC, betaC, alphaC);
	for (i=0; i<complex.getNumAtoms(); i++)
	{
		complex.getAtom(i)->x -= translationC.x;	complex.getAtom(i)->y -= translationC.y;	complex.getAtom(i)->z -= translationC.z;

		transformedAtom = complex.getAtom(i)->transformCoordinates(transformMatrix, ' ');
		transformedAtom.originalLine = transformedAtom.updateLineCoordinates();
		*(complex.getAtom(i)) = transformedAtom;
	}

}
*/

double angleBetweenVectors(Coordinates &vector1, Coordinates &vector2)
{
	double dot=0.0f, retAngle=0.0;
	double sinAngle=0.0f, cosAngle=0.0f;
	double multipliedMagnitude=0.0f;
	Coordinates cross;

	multipliedMagnitude = vector1.magnitude()*vector2.magnitude();

	dot = vector1.dotProduct(vector2);
	cross = vector1.crossProduct(vector2);

	sinAngle = cross.magnitude() / multipliedMagnitude;
	cosAngle = dot / multipliedMagnitude;

	retAngle = acos(cosAngle);

	if (sinAngle < 0.0f)
	{
		retAngle = 360.0f - retAngle;
		printf ("--> retAngle = %f\n", retAngle);
	}

	return retAngle;
}

void updateReferencePoints(Coordinates **referencePoints, double alpha, double beta, double gamma)
{
	unsigned int i=0;
	AtomPdb tempAtoms[3];
	double transformMatrix[16];
	AtomPdb transformedAtom;
	PdbFile tempPdbFile;

	tempPdbFile.makeTransformMatrix(transformMatrix, 0, alpha, beta, gamma);

//	printf ("Update: alpha = %f\tbeta = %f\t\tgamma = %f\n", alpha, beta, gamma);
	for (i=0; i<3; i++)
	{
//		tempAtoms[i] = *(pdbFile.getAtom(0));
		tempAtoms[i].x = (*referencePoints)[i].x - (*referencePoints)[0].x;
		tempAtoms[i].y = (*referencePoints)[i].y - (*referencePoints)[0].y;
		tempAtoms[i].z = (*referencePoints)[i].z - (*referencePoints)[0].z;

//		printf ("Atom %d: %lf\t%lf\t%lf\n", i, tempAtoms[i].x, tempAtoms[i].y, tempAtoms[i].z);

		transformedAtom = tempAtoms[i].transformCoordinates(transformMatrix, ' ');
//		printf ("transformedAtom: %lf\t%lf\t%lf\n", transformedAtom.x, transformedAtom.y, transformedAtom.z);

		(*referencePoints)[i].x = transformedAtom.x;
		(*referencePoints)[i].y = transformedAtom.y;
		(*referencePoints)[i].z = transformedAtom.z;

/*
		transformedAtom = transformedAtom.transformCoordinates(transformMatrix, ' ');
		printf ("transformedAtom: %lf\t%lf\t%lf\n", transformedAtom.x, transformedAtom.y, transformedAtom.z);
//		transformedAtom = transformedAtom.transformCoordinates(transformMatrix2, ' ');
*/

//		printf ("\n");
	}

//	printf ("-----------------------------------------\n");
}

// void PdbWriter::alignPDB(PdbFile &complex, unsigned int atomIndex1, unsigned int atomIndex2, unsigned int atomIndex3)
void PdbWriter::alignPDB(PdbFile &pdbFile, Coordinates *referencePoints)
{
	unsigned int i=0;
	double alpha=0.0f, beta=0.0f, gamma=0.0f;
	double transformMatrix[16];
	double transformMatrix1[16];
	double transformMatrix2[16];
	AtomPdb transformedAtom;
	AtomPdb tempAtom;
	Coordinates referenceVector[2], referenceTranslation;
	Coordinates vector1, vector2;
	Coordinates tempReferencePoints[3];

	for (i=0; i<3; i++)
		tempReferencePoints[i] = referencePoints[i];
/*
	referencePoints[0].x = 0.0f;	referencePoints[0].y = 0.0f;	referencePoints[0].z = 0.0f;
	referencePoints[1].x = 1.0f;	referencePoints[1].y = 1.0f;	referencePoints[1].z = 1.0f;
	referencePoints[2].x = 0.8f;	referencePoints[2].y = 1.2f;	referencePoints[2].z = 0.8f;
*/

	referenceVector[0].x = referencePoints[0].x - referencePoints[1].x;
	referenceVector[0].y = referencePoints[0].y - referencePoints[1].y;
	referenceVector[0].z = referencePoints[0].z - referencePoints[1].z;
	referenceVector[0].Normalize();

	referenceVector[1].x = referencePoints[0].x - referencePoints[2].x;
	referenceVector[1].y = referencePoints[0].y - referencePoints[2].y;
	referenceVector[1].z = referencePoints[0].z - referencePoints[2].z;
	referenceVector[1].Normalize();

	referenceTranslation.x = referencePoints[0].x;
	referenceTranslation.y = referencePoints[0].y;
	referenceTranslation.z = referencePoints[0].z;

// za kut izmedju vektora oko z-osi treba uzeti vektore:
// vektor1 je vektor izmedju projekcije tocke 1 na X-Z ravninu, i projekcije te projicirane tocke na Z-os (znaci, samo po x-u se razlikuju)
//	vector1.x = referencePoints[1].x - 0.0f;	vector1.y = 0.0f;	vector1.z = 0.0f;
//	vector1.Normalize();
	vector1.x = 1.0f;	vector1.y = 0.0f;	vector1.z = 0.0f;
// vector2 je vektor izmedju tocke 1 i njene projekcije na z-os (znaci samo po z-osi su iste tocke)
	vector2.x = referencePoints[1].x - 0.0f;	vector2.y = referencePoints[1].y - 0.0f;	vector2.z = 0.0f;
	vector2.Normalize();
	alpha = angleBetweenVectors(vector1, vector2);
//	printf ("reference = %f\n", referencePoints[1].y);
	updateReferencePoints(&referencePoints, alpha, 0.0f, 0.0f);
//	printf ("reference = %f\n", referencePoints[1].y);




// za rotaciju oko y-osi treba novu tocku zarotairati izmedju vector1 koji predstavlja z-os i vector2, koji predstavlja vektor izmedju te nove
// tocke, i tocke (0.0, 0.0f, 0.0f)
	vector1.x = 0.0f;	vector1.y = 0.0f;	vector1.z = 1.0f;
	vector2.x = referencePoints[1].x - 0.0;	vector2.y = 0.0f;	vector2.z = referencePoints[1].z -0.0f;
	vector2.Normalize();
	beta = angleBetweenVectors(vector1, vector2);
	updateReferencePoints(&referencePoints, 0.0f, beta, 0.0f);

// za rotaciju oko z-osi, uzmemo u obzir da nam je sada tocka 1 na z-osi, pa jos samo treba spustiti tocku 2 na X-Z ravninu
// na slican nacin kao i u prvom slucaju, samo uzmemo drugu tocku u obzir
	vector1.x = 1.0f;	vector1.y = 0.0f;	vector1.z = 0.0f;
	vector2.x = referencePoints[2].x - 0.0f;	vector2.y = referencePoints[2].y - 0.0f;	vector2.z = 0.0f;
	vector2.Normalize();
	gamma = angleBetweenVectors(vector1, vector2);

//	printf ("Nakon zadnjeg kuta: \n");
	updateReferencePoints(&referencePoints, 0.0f, 0.0f, gamma);



//	pdbFile.makeTransformMatrix(transformMatrix, 0, -alpha, -beta, -gamma);
//	pdbFile.makeTransformMatrix(transformMatrix, 0, -gamma, -beta, -alpha);
//	pdbFile.makeTransformMatrix(transformMatrix, 0, -alpha, 0.0f, 0.0f);
//	pdbFile.makeTransformMatrix(transformMatrix1, 0, 0.0f, -beta, 0.0f);
//	pdbFile.makeTransformMatrix(transformMatrix2, 0, -gamma, 0.0f, 0.0f);

/** Ovo je bilo upaljeno po defaultu.
 * Datum 28.11.2012.
	printf ("alpha = %lf\nbeta = %lf\ngamma = %lf\n\n", alpha*180.0f/3.14159f, beta*180.0f/3.14159f, gamma*180.0f/3.14159f);

//	updateReferencePoints(referencePoints, alpha, beta, gamma);

/*
	for (i=0; i<pdbFile.getNumAtoms(); i++)
	{
		pdbFile.getAtom(i)->x -= referenceTranslation.x;	pdbFile.getAtom(i)->y -= referenceTranslation.y;	pdbFile.getAtom(i)->z -= referenceTranslation.z;

		transformedAtom = pdbFile.getAtom(i)->transformCoordinates(transformMatrix, ' ');
		transformedAtom.originalLine = transformedAtom.updateLineCoordinates();
		*(pdbFile.getAtom(i)) = transformedAtom;
	}
*

//	printf ("referencePoints[0] = %f\n", referencePoints[0].x, referencePoints[0].y, referencePoints[0].z);
//	printf ("referencePoints[1] = %f\n", referencePoints[1].x, referencePoints[1].y, referencePoints[1].z);
//	printf ("referencePoints[2] = %f\n", referencePoints[2].x, referencePoints[2].y, referencePoints[2].z);

	for (i=0; i<3; i++)
	{
		printf ("referencePoints[%d]:\t%f\t%f\t%f\n", i, referencePoints[i].x, referencePoints[i].y, referencePoints[i].z);
		referencePoints[i] = tempReferencePoints[i];
		printf ("tempReferencePoints[%d]:\t%f\t%f\t%f\n", i, referencePoints[i].x, referencePoints[i].y, referencePoints[i].z);
		printf ("-\n");
	}
	printf ("\n");
 */


}
