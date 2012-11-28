/*
 * moleculecolors.h
 *
 *  Created on: Apr 11, 2010
 *      Author: ivan
 */

#ifndef MOLECULECOLORS_H_
#define MOLECULECOLORS_H_

#include <string>
#include <vector>
#include <ctype.h>
#include <boost/regex.hpp>
#include "../structures/structures.h"



class MoleculeColors
{
public:
	void load(std::string colorsPath);
	void loadDefault();
	void saveColors(std::string colorsPath);
	bool getAtomColor(std::string atomName, Color **colorPointer);
	bool getAminoColor(std::string aminoName, Color **colorPointer);
	bool getChainColor(std::string chainName, Color **colorPointer);
	bool setAtomColor(std::string atomName, Color color);
	bool setAminoColor(std::string aminoName, Color color);
	bool setChainColor(std::string chainName, Color color);

	static MoleculeColors* getInstance(std::string colorsPath="");

private:
	static MoleculeColors* singleInstance_;
	std::string MoleculeColorsPath_;

	std::vector<std::string> atomNames_;
	std::vector<Color> atomColors_;

	std::vector<std::string> aminoNames_;
	std::vector<Color> aminoColors_;

	std::vector<std::string> chainNames_;
	std::vector<Color> chainColors_;

	std::vector<std::string> secondaryNames_;
	std::vector<Color> secondaryColors_;

	float energyMaximum_, energyMinimum_;
	Color energyPositiveColor_, energyNegativeColor_;

	MoleculeColors();
	MoleculeColors(std::string colorsPath);
	~MoleculeColors();

};

#endif /* MoleculeColors_H_ */
