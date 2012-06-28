/*
 * scr2pdb.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: ivan
 */

#include "pdbwriter/pdbwriter.h"



int main(int argc, char **argv)
{
	int startingScore=0, maxNumScores=0;
	PdbWriter pdbWriter;
	std::string scorePath, receptorPath, ligandPath, radiiPath, outputPath;

	if (argc < 8)
	{
		printf ("Too few arguments! Syntax:\n\t./scr2pdb scorePath receptorPath ligandPath radiiPath outputPath startingScore maxNumScores");
		return 1;
	}

	scorePath = argv[1];
	receptorPath = argv[2];
	ligandPath = argv[3];
	radiiPath = argv[4];
	outputPath = argv[5];
	sscanf(argv[6], "%d", &startingScore);
	sscanf(argv[7], "%d", &maxNumScores);

	pdbWriter.write(scorePath, receptorPath, ligandPath, radiiPath, outputPath, startingScore, maxNumScores);

	return 0;
}
