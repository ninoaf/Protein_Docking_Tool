/*
 * models.h
 *
 *  Created on: Mar 11, 2010
 *      Author: ivan
 */

#ifndef MODELS_H_
#define MODELS_H_

#include <vector>
#include <string>
#include "atomradius.h"
#include "../structures/structures.h"
// #include "pdbparser.h"



class Model
{
public:
	Model();
	~Model();

	void Clear();
//	void AddAtom(AtomPdb &atom);
//	std::vector<AtomPdb *>& getAtoms();
	std::vector<unsigned long int>& getAtomIndex();
	std::vector<AtomPdb>* getAtomList();
	void setAtomList(std::vector<AtomPdb> *atomList_);
	AtomPdb &getAtom(unsigned long int atomIndex);
	void setName(std::string name);
	std::string getName();
	void centerAtomsArithmetically();
	void centerAtomsByMass();
	Coordinates getArithmeticCenter();
	Coordinates getMassCenter();
	bool getCenterAtomsByMass();
	bool getCenterAtomsArithmetically();
//	void calculateArithmeticCenter();
//	void calculateMassCenter();
	void findCenters();
	void MakeBonds();
	std::vector<Bond>& getBonds();

private:
//	std::vector <AtomPdb *> atoms_;
	std::vector <unsigned long int> atomIndex_;
	std::string name_;
	std::vector <Bond> bonds_;
	bool centerAtomsByMass_;
	bool centerAtomsArithmetically_;
	Coordinates modelArithmeticCenter_;
	Coordinates modelMassCenter_;
	Coordinates boundsMin_;
	Coordinates boundsMax_;
	std::vector<AtomPdb> *atomList_;
};

#endif /* MODELS_H_ */
