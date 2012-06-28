/*
 * predocking.h
 *
 *  Created on: Nov 4, 2009
 *      Author: ivan
 */

#ifndef PREDOCKING_H_
#define PREDOCKING_H_

#include <cstdio>
#include <string>
#include "../pdbparser/pdbparser.h"
#include "../msmswrapper/msmswrapper.h"
#include "../configuration/configuration.h"
#include "../grid/grid.h"


/**
 * Class used for loading and processing of PDB files. Main function for the process of predocking is runPredocking. All other functions are called by runPredocking, but are made public for the user to use.
 */
class Predocking
{
public:
	/** Constructor for Predocking class. */
	Predocking();
	/** Destructor for Predocking class. */
	~Predocking();

	/** Initialization function for Predocking class, called by the constructor. */
	void Init();
	/**
		Parses a PDB file given with its path, and saves atom coordinates (together with their radii) to the destination path.
		 \param pdbFile Pointer to object of class PdbFile, whose purpose is to parse PDB files. This pointer is used so that you can get the parsed PDB after the function returns, and not only on the hard drive.
		 \param sourcePath Specifies the path to the PDB that should be parsed.
		 \param destinationPath Path of the file where parsing output should be saved. The output contains a set of atom coordinates, and its coresponding radii, and is written in a textual format.
		 \param radiiPath Path to the file that contains information about atom radii.
	*/
	bool parsePDB(PdbFile *pdbFile, char *sourcePath, char *destinationPath, char *radiiPath);
	/** 
	*/
	bool getMolecularSurface(MSMSWrapper *wrapper, string path);
	bool getSurfaceSkin(Grid *skin, MSMSWrapper *wrapper, double microDelta, double delta, double radius, string skinPath);
	bool getCoefficients(Coefficients *coeff, Grid *skin, int order, string path);
	void runPredocking(Configuration &config);
};

#endif /* PREDOCKING_H_ */
