/*
 * coeff_movement.cpp
 *
 *  Created on: Dec 27, 2009
 *      Author: ivan
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "docking/docking.h"
#include "configuration/configuration.h"
#include "predocking/predocking.h"



int main(int argc, char **argv)
{
	Predocking predock;

	if (argc < 5)
	{
		printf ("Not enough arguments!");
		return 1;
	}

	int order=0;
	double microDelta=0.0f, delta=0.0f, radius=0.0f;
	double gridSize=0.0f, gridCellSize=0.0f;
	string pdbPath, outputFolder, radiiPath;
	string parsedPdbPath, skinPath, inflatedSkinPath, coeffPath, proteinPath;
	MSMSWrapper wrapper;
	PdbFile pdbFile;
	Coefficients coeff;

	pdbPath = argv[1];
	outputFolder = argv[2];
	radiiPath = argv[3];
	sscanf(argv[4], "%lf", &microDelta);
	sscanf(argv[5], "%lf", &delta);
	sscanf(argv[6], "%lf", &radius);
	sscanf(argv[7], "%lf", &gridSize);
	sscanf(argv[8], "%lf", &gridCellSize);
	sscanf(argv[9], "%d", &order);

	proteinPath = outputFolder + "protein.pdb";
	parsedPdbPath = outputFolder + "protein.adb";
	skinPath = outputFolder + "protein.skin";
	inflatedSkinPath = outputFolder + "protein.iskin";
	inflatedSkinPath = outputFolder + "protein.coeff";

	Grid skin(gridSize, gridCellSize), inflatedSkin(gridSize, gridCellSize);



	string copyCommand;
	copyCommand = "cp ";
	copyCommand += pdbPath + " " + proteinPath;
	system(copyCommand.c_str());

	printf ("Loading PDB %s...", pdbPath.c_str());
	if ((predock.parsePDB(&pdbFile, (char *) pdbPath.c_str(), (char *) parsedPdbPath.c_str(), (char *) radiiPath.c_str())))
		printf ("success!\n");
	else
		printf ("FAILED!\n");

	printf ("Molecular surface...\n");
	predock.getMolecularSurface(&wrapper, parsedPdbPath);
	printf ("...OK.\n");

	printf ("Generating skin...\n");
	predock.getSurfaceSkin(&skin, &wrapper, microDelta, delta, radius, skinPath);
	inflatedSkin = skin;
	inflatedSkin.inflateGrid();
	inflatedSkin.exportToFile(inflatedSkinPath);
	printf ("...OK.\n");

	printf ("Calculating coefficients...\n");
	predock.getCoefficients(&coeff, &skin, order, coeffPath);
	printf ("...OK.\n");




	printf ("Finished!\n");

	return 0;
}
