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
#include <cstdlib>
#include "../pdbparser/pdbparser.h"
#include "../msmswrapper/msmswrapper.h"
#include "../configuration/configuration.h"
#include "../grid/grid.h"
#include "../protein/protein.h"

enum LoadFrom
{
	FILE_LIGAND,
	FILE_RECEPTOR,
	CALCULATE
};

class Predocking
{
public:
	friend class Protein;

	/** Constructor for Predocking class. */
	Predocking(Configuration &config, LoadFrom source);
	Predocking();
	~Predocking();

	/** loadConfiguration function reads config.txt file for parameters concerning the predocking process.
	    If source is FILE_LIGAND or FILE_RECEPTOR, then the coefficients are loaded from precalculated stored files, defined by parameters in config.txt file: ligand_inner_skin_coeffs and ligand_outer_skin_coeffs, or receptor_inner_skin_coeffs and receptor_outer_skin_coeffs.
	    If source is CALCULATE, then spherical coefficients are calculated, in which case configuration all parameters are loaded from config.txt.
	*/
	void loadConfig(Configuration &config, LoadFrom source);
	void parsePDB(const char *sourcePath, const char *destinationPath);
	void calculateSkins(const string& PDBFilePath);
	void getProtein(int order, Protein& protein);

	void calculateSkinsWithouthParsing();
	void calculateSurface(const string& PDBFilePath, const char *parsedPdbPath);

	PdbFile& getPdbFile();

private:
	int centerAtoms_;
	int gridSize_, gridCellSize_;
	double microDelta_, delta_;
	double innerRadius_, outerRadius_;
	string radiiPath_;

	Protein *protein_;

	Grid inner_, outer_;

	PdbFile pdbFile_;
	MSMSWrapper msms_;
};

#endif /* PREDOCKING_H_ */
