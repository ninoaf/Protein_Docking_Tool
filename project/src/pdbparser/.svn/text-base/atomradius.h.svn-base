/*
 * atomradius.h
 *
 *  Created on: Nov 3, 2009
 *      Author: ivan
 */

#ifndef ATOMRADIUS_H
#define ATOMRADIUS_H

#include "../structures/structures.h"
#include <vector>
#include <string>
#include <fstream>
#include<boost/regex.hpp>



class AtomRadii
{
public:
	AtomRadii();
	~AtomRadii();

	void init();
	bool loadRadii(std::string path);
	double findRadius(Atom *atom, bool useUnitedRadius);

private:
	std::vector <std::string> residuePatterns_;
	std::vector <std::string> atomPatterns_;
	double explicitRadius_[100];
	double unitedRadius_[100];
	std::vector <int> atomNumber_;
	bool atmTypeNumbersLoaded_;
	int numPatterns_;

	int comparePattern(std::string pattern, std::string name);
	std::string clearMultipleVoids(std::string line);
	int getNumParam(std::string line);
};

#endif
