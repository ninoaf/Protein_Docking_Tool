/*
 * scr2pdb.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: ivan
 */

#include "pdbwriter/pdbwriter.h"



int main(int argc, char **argv)
{
	int centerAtoms=0;
	int startingScore=0, maxNumScores=0;
	PdbWriter pdbWriter;
	std::string scorePath, receptorPath, ligandPath, radiiPath, outputPath;

	if (argc < 9)
	{
		printf ("Too few arguments! Syntax:\n\t./scr2pdb scorePath receptorPath ligandPath radiiPath outputPath startingScore maxNumScores centerAtoms");

		printf ("\n\n\t - scorePath\t- path to the file containing docking scores.\n");
		printf ("\t - receptorPath\t - path to the PDB file used as the receptor in the docking process.\n");
		printf ("\t - ligandPath\t - path to the PDB file used as the ligand in the docking process.\n");
		printf ("\t - radiiPath\t - path to the file containing atom radii.\n");
		printf ("\t - outputPath\t - path for the output PDB file.\n");
		printf ("\t - startingScore\t - index of the starting configuration from the scores file.\n");
		printf ("\t - maxNumScores\t - number of scores to convert to PDB (starting from startingScore, ending with (startingScore+maxNumScores-1)\n");
		printf ("\t - centerAtoms\t - if centerAtoms==0, then proteins won't be centered; if centerAtoms==1 proteins will be centered by mass; if centerAtoms==2 proteins will be centered arithmetically; if centerAtoms==3 proteins will be aligned to the global Z-axis and centered by mass. (default value = 1).\n\n");

		return 1;
	}

	scorePath = argv[1];
	receptorPath = argv[2];
	ligandPath = argv[3];
	radiiPath = argv[4];
	outputPath = argv[5];
	sscanf(argv[6], "%d", &startingScore);
	sscanf(argv[7], "%d", &maxNumScores);
	sscanf(argv[8], "%d", &centerAtoms);

	pdbWriter.write(scorePath, receptorPath, ligandPath, radiiPath, outputPath, startingScore, maxNumScores, centerAtoms);

	return 0;
}
