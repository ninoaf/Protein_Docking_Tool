/*
 * rmsd_test.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: ivan
 */

#include "rmsd_test.h"

using namespace std;



RMSDTestDrive::RMSDTestDrive()
{

}

void RMSDTestDrive::rmsdRun(std::string configPath)
{
	int tempInt=0;
	char centerAtoms=0;
	int startingScore=0, maxNumScores=0;
	PdbWriter pdbWriter;
	PdbFile receptor, ligand, complex;
	std::string scorePath, receptorPath, ligandPath, radiiPath, outputPath, outputPdbPath, outputComplexPath, complexPath;
	vector<int> complexIndex, receptorIndex, ligandIndex;

	Configuration configuration;

	configuration.init(configPath);

	configuration.getParameter("scores_output_file", scorePath);
	configuration.getParameter("complex", complexPath);
	configuration.getParameter("ligand", ligandPath);
	configuration.getParameter("receptor", receptorPath);
	configuration.getParameter("radii_path", radiiPath);
	configuration.getParameter("center", tempInt);	centerAtoms = (char) tempInt;
	configuration.getParameter("rmsd_output", outputPath);
	configuration.getParameter("rmsd_output_pdb", outputPdbPath);
	configuration.getParameter("rmsd_output_complex", outputComplexPath);
	configuration.getParameter("starting_score", startingScore);
	configuration.getParameter("num_scores", maxNumScores);

	printf ("ligand:\t\t\t%s\n", ligandPath.c_str());
	printf ("receptor:\t\t%s\n", receptorPath.c_str());
	printf ("complex:\t\t%s\n", complexPath.c_str());
	printf ("radii_file:\t\t%s\n", radiiPath.c_str());
	printf ("center_atoms:\t\t%d\n", centerAtoms);
	printf ("\n");
	printf ("scores_file:\t\t%s\n", scorePath.c_str());
	printf ("starting_score:\t\t%d\n", startingScore);
	printf ("num_scores:\t\t%d\n", maxNumScores);
	printf ("\n");
	printf ("rmsd_output:\t\t%s\n", outputPath.c_str());
	printf ("rmsd_output_pdb:\t%s\n", outputPdbPath.c_str());
	printf ("rmsd_output_complex:\t%s\n", outputComplexPath.c_str());
	printf ("\n");

	printf ("Starting RMSD evaluation...\n");
	pdbWriter.evaluateScores(scorePath, complexPath, receptorPath, ligandPath, radiiPath, outputPath, outputPdbPath, outputComplexPath,
							 startingScore, maxNumScores, centerAtoms);

	printf ("...RMSD evaluation completed.\n\n");

}


