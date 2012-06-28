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

int PdbWriter::write(string scorePath, string receptorPath, string ligandPath, string radiiPath, string outPdbPath, int startingScore, int maxNumScores)
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
	ligandPDB.Import();

	receptorPDB.Init((char *) receptorPath.c_str());
	if (!receptorPDB.LoadAtmtypenumbers((char *) radiiPath.c_str()))
	{
		printf ("Could not open file %s!\n", radiiPath.c_str());
		return 0;
	}
	receptorPDB.UseUnitedRadius();
	receptorPDB.Import();

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
		receptorPDB.writeTransformedAtoms(fpPDB, 'R', scoresData.scores[i].radius, 0.0f, scoresData.scores[i].betaReceptor, scoresData.scores[i].gammaReceptor);
		fprintf (fpPDB, "TER\n");
		ligandPDB.writeTransformedAtoms(fpPDB, 'L', 0.0f, scoresData.scores[i].alphaLigand, scoresData.scores[i].betaLigand, scoresData.scores[i].gammaLigand);
		fprintf (fpPDB, "TER\n");
		fprintf (fpPDB, "ENDMDL\n");
	}

	fclose(fpPDB);

	return 1;
}
