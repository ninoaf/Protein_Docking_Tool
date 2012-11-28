/*
 * pdbparser.h
 *
 *  Created on: Nov 3, 2009
 *      Author: ivan
 */

#ifndef PDBPARSER_H
#define PDBPARSER_H

#include "../structures/structures.h"
#include "moleculecolors.h"
#include <vector>
#include <string>
#include <fstream>
#include <boost/regex.hpp>
#include "atomradius.h"
#include "models.h"



class PdbFile
{
public:
	PdbFile();
	PdbFile(const char *fileName);
	void Init(const char *fileName);
	~PdbFile();

	bool Import(bool centerAtoms=true);
	int LoadAtmtypenumbers(const char *fileName);
	void UseExplicitRadius();
	void UseUnitedRadius();
	bool SaveCoords(const char *fileName);

	void clear();
	int importModel(long int modelIndex, bool centerAtoms=true);
	bool writeTransformedAtoms(FILE *fpOutput, char chainDesignation, double r, double alpha, double beta, double gamma);
	bool writeAtoms(FILE *fpOutput);
	bool createTransformedPdbFile(PdbFile &newPdbFile, double r, double alpha, double beta, double gamma);
	void center();
	void centerAtomsArithmetically();
	void centerAtomsByMass();
	double findMass(char *atomName);
	bool loadMass(char *massPath);
	bool loadMass();

	unsigned int getNumAtoms();
	AtomPdb* getAtom(unsigned int index);
	void setAtom(unsigned int index, AtomPdb &newAtom);
    PdbFile& operator= (PdbFile &op1);
    void setName(std::string pdbName);
    void setRadiusPath(std::string path);

    std::vector<unsigned long int>& getAtomIndex();
    std::vector<AtomPdb>& getAtomList();
    bool getUseUnitedRadius();
    Coordinates getPdbArithmeticCenter();
    Coordinates getPdbMassCenter();
    std::string getFileName();
    AtomRadii& getAtomRadii();
    bool getCentered();
    bool getCenterAtomsArithmetically();
    bool getCenterAtomsByMass();
    std::vector<Model>& getModels();
    std::string getName();
    std::string getRadiusPath();

	std::vector<std::string>& getElementNames();
	std::vector<double>& getElementMass();

    void pushAtom(AtomPdb &newAtom);

	void makeTransformMatrix(double *transformMatrix, double r, double alpha, double beta, double gamma);

	void findCenters();

private:
	std::vector <unsigned long int> atomIndex_;
	std::vector <AtomPdb> atomList_;
	int numAtoms_;
	bool useUnitedRadius_;
	Coordinates pdbArithmeticCenter_;
	Coordinates pdbMassCenter_;
	Coordinates boundsMin_;
	Coordinates boundsMax_;
	std::string fileName_;
	AtomRadii atomRadii_;
	bool centered_;
	bool centerAtomsArithmetically_;
	bool centerAtomsByMass_;

	std::vector <Model> models_;

	std::vector<std::string> elementNames_;
	std::vector<double> elementMass_;

	std::vector<PdbModelLocations> modelLocations_;

	std::string pdbName_;
	std::string radiusPath_;

	std::vector<std::string> pdbCache_;

	std::string trimAndLower(std::string line);
};

#endif
