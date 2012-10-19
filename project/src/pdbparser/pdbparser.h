/*
 * pdbparser.h
 *
 *  Created on: Nov 3, 2009
 *      Author: ivan
 */

#ifndef PDBPARSER_H
#define PDBPARSER_H

#include "../structures/structures.h"
#include <vector>
#include <string>
#include <fstream>
#include<boost/regex.hpp>
#include "atomradius.h"



class PdbFile
{
public:
	PdbFile();
	PdbFile(char *fileName);
	void Init(char *fileName);
	~PdbFile();

	bool Import(bool centerAtoms=true);
	int LoadAtmtypenumbers(char *fileName);
	void UseExplicitRadius();
	void UseUnitedRadius();
	bool SaveCoords(char *fileName);
	bool WriteTransformedAtoms(FILE *fpOutput, char chainDesignation, double r, double alpha, double beta, double gamma);
//	void PutChargesOnGrid(Grid& grid);

private:
	std::vector <Atom> atoms_;
	int numAtoms_;
	bool useUnitedRadius_;
	Coordinates pdbCenter_;
	std::string fileName_;
	AtomRadii atomRadii_;

	std::string trimAndLower(std::string line);
	void MakeTransformMatrix(double *transformMatrix, double r, double alpha, double beta, double gamma);
};

#endif
