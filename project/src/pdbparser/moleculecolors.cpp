/*
 * MoleculeColors.cpp
 *
 *  Created on: Apr 11, 2010
 *      Author: ivan
 */

#include "moleculecolors.h"

using namespace std;

MoleculeColors* MoleculeColors::singleInstance_=NULL;




MoleculeColors::MoleculeColors()
{
	load((string) "");
}

MoleculeColors::MoleculeColors(string colorsPath)
{
	load(colorsPath);
}

MoleculeColors::~MoleculeColors()
{
	if (singleInstance_)
	{
		delete singleInstance_;
		singleInstance_ = NULL;
	}
}

void MoleculeColors::load(string colorsPath)
{
	if (colorsPath == "")
	{
		loadDefault();
	}
	else
	{

	}
}

void MoleculeColors::loadDefault()
{
	Color color;

	atomNames_.clear();
	atomColors_.clear();
	aminoNames_.clear();
	aminoColors_.clear();
	chainNames_.clear();
	chainColors_.clear();

// colouring by atom names
/*
	atomNames_.push_back("c");	color.r = 0.1f*255;	color.g = 0.3f*255;	color.b = 0.1f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("h");	color.r = 0.3f*255;	color.g = 0.3f*255;	color.b = 0.3f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("n");	color.r = 0.1f*255;	color.g = 0.1f*255;	color.b = 0.6f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("o");	color.r = 0.6f*255;	color.g = 0.1f*255;	color.b = 0.1f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("s");	color.r = 0.6f*255;	color.g = 0.6f*255;	color.b = 0.0f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("default");	color.r = 0.6f*255;	color.g = 0.6f*255;	color.b = 0.6f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
*/

	atomNames_.push_back("c");	color.r = 0.6f*255;	color.g = 0.8f*255;	color.b = 0.6f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("h");	color.r = 0.8f*255;	color.g = 0.8f*255;	color.b = 0.8f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("n");	color.r = 0.6f*255;	color.g = 0.6f*255;	color.b = 1.0f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("o");	color.r = 1.0f*255;	color.g = 0.6f*255;	color.b = 0.6f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("s");	color.r = 1.0f*255;	color.g = 1.0f*255;	color.b = 0.0f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);
	atomNames_.push_back("default");	color.r = 0.9f*255;	color.g = 0.9f*255;	color.b = 0.9f*255;	color.a = 1.0f*255;	atomColors_.push_back(color);

// colouring by aminoacid
	aminoNames_.push_back("ala");	color.r = 0.78f*255;	color.g = 0.78f*255;	color.b = 0.78f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("arg");	color.r = 0.08f*255;	color.g = 0.35f*255;	color.b = 1.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("asn");	color.r = 0.00f*255;	color.g = 0.86f*255;	color.b = 0.86f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("asp");	color.r = 0.90f*255;	color.g = 0.04f*255;	color.b = 0.04f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("cys");	color.r = 0.90f*255;	color.g = 0.90f*255;	color.b = 0.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("gln");	color.r = 0.00f*255;	color.g = 0.86f*255;	color.b = 0.86f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("glu");	color.r = 0.90f*255;	color.g = 0.04f*255;	color.b = 0.04f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("gly");	color.r = 0.92f*255;	color.g = 0.92f*255;	color.b = 0.92f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("his");	color.r = 0.51f*255;	color.g = 0.51f*255;	color.b = 0.82f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("ile");	color.r = 0.06f*255;	color.g = 0.51f*255;	color.b = 0.06f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("leu");	color.r = 0.06f*255;	color.g = 0.51f*255;	color.b = 0.06f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("lys");	color.r = 0.08f*255;	color.g = 0.35f*255;	color.b = 1.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("met");	color.r = 0.90f*255;	color.g = 0.90f*255;	color.b = 0.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("phe");	color.r = 0.20f*255;	color.g = 0.20f*255;	color.b = 0.66f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("pro");	color.r = 0.86f*255;	color.g = 0.59f*255;	color.b = 0.51f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("ser");	color.r = 0.98f*255;	color.g = 0.59f*255;	color.b = 0.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("thr");	color.r = 0.98f*255;	color.g = 0.59f*255;	color.b = 0.00f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("trp");	color.r = 0.70f*255;	color.g = 0.35f*255;	color.b = 0.70f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("tyr");	color.r = 0.20f*255;	color.g = 0.20f*255;	color.b = 0.66f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("val");	color.r = 0.06f*255;	color.g = 0.51f*255;	color.b = 0.06f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("asx");	color.r = 1.00f*255;	color.g = 0.41f*255;	color.b = 0.70f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("glx");	color.r = 1.00f*255;	color.g = 0.41f*255;	color.b = 0.70f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
//	aminoNames_.push_back("default");	color.r = 0.74f*255;	color.g = 0.63f*255;	color.b = 0.43f*255;	color.a = 1.0f*255;	aminoColors_.push_back(color);
	aminoNames_.push_back("default");	color.r = 255;	color.g = 0;	color.b = 0;	color.a = 255;	aminoColors_.push_back(color);

// colouring by chain name
	chainNames_.push_back("a");	color.r = 192;	color.g = 208;	color.b = 255;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("b");	color.r = 176;	color.g = 255;	color.b = 176;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("c");	color.r = 255;	color.g = 192;	color.b = 200;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("d");	color.r = 255;	color.g = 255;	color.b = 128;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("e");	color.r = 255;	color.g = 192;	color.b = 255;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("f");	color.r = 176;	color.g = 240;	color.b = 240;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("g");	color.r = 255;	color.g = 208;	color.b = 112;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("h");	color.r = 240;	color.g = 128;	color.b = 128;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("i");	color.r = 245;	color.g = 222;	color.b = 179;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("j");	color.r = 0;	color.g = 191;	color.b = 255;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("k");	color.r = 205;	color.g = 92;	color.b = 92;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("l");	color.r = 102;	color.g = 205;	color.b = 170;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("m");	color.r = 154;	color.g = 205;	color.b = 50;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("n");	color.r = 238;	color.g = 130;	color.b = 238;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("o");	color.r = 0;	color.g = 206;	color.b = 209;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("p");	color.r = 0;	color.g = 255;	color.b = 127;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("q");	color.r = 60;	color.g = 179;	color.b = 113;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("r");	color.r = 0;	color.g = 0;	color.b = 139;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("s");	color.r = 189;	color.g = 183;	color.b = 107;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("t");	color.r = 0;	color.g = 100;	color.b = 0;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("u");	color.r = 128;	color.g = 0;	color.b = 0;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("v");	color.r = 128;	color.g = 128;	color.b = 0;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("w");	color.r = 128;	color.g = 0;	color.b = 128;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("x");	color.r = 0;	color.g = 128;	color.b = 128;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("y");	color.r = 184;	color.g = 134;	color.b = 11;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("z");	color.r = 178;	color.g = 34;	color.b = 34;	color.a = 255;	chainColors_.push_back(color);
	chainNames_.push_back("default");	color.r = 255;	color.g = 255;	color.b = 255;	color.a = 255;	chainColors_.push_back(color);
//	chainNames_.push_back("default");	color.r = 0;	color.g = 255;	color.b = 0;	color.a = 255;	chainColors_.push_back(color);




/*
    else if (color_type == 2)
    {
        if (strlen(atom_pointer->res_name) == 0)
            return false;

        r = my_abs(((float) (atom_pointer->res_name[0] - 'A')) / 'z');
        g = my_abs(((float) (atom_pointer->res_name[1] - 'A')) / 'z');
        b = my_abs(((float) (atom_pointer->res_name[2] - 'A')) / 'z');

        glColor3f(r, g, b);

        return true;
    }
    else if (color_type == 3)
    {
        int index=0, base=7;
        float step=1.0f/12.0f;

        index = (atom_pointer->chain_id); // % 216;

        r = step * (index % base);
        index /= base;
        g = step * (index % base);
        index /= base;
        b = step * (index % base);
        index /=base;

        glColor3f(r, g, b);
*/
}

void MoleculeColors::saveColors(string colorsPath)
{
	unsigned int i=0;
	FILE *fp;

	if (atomNames_.size() != atomColors_.size())
	{
		printf ("Defect color information: different number of atom names and colors!\n");
		return;
	}

	fp = fopen(colorsPath.c_str(), "w");
	if (fp == NULL)
	{
		printf ("Could not open file %s for writing!\n", colorsPath.c_str());
		return;
	}

	fprintf (fp, "%d\n", atomNames_.size());
	for (i=0; i<atomNames_.size(); i++)
	{
		fprintf (fp, "%s\t%u\t%u\t%u\t%u\n", atomNames_[i].c_str(), atomColors_[i].r, atomColors_[i].g, atomColors_[i].b, atomColors_[i].a);
	}

	fclose(fp);
}

bool MoleculeColors::getAtomColor(string atomName, Color **colorPointer)
{
	unsigned int i=0, maxLength=0;
	int maxIndex=-1;
	string patternString;
	string tempName;

	if (atomNames_.size()==0 || atomColors_.size()==0 || atomNames_.size()!=atomColors_.size() || atomName=="")
		return false;

	tempName = "";
	for (i=0; i<atomName.size(); i++)
		tempName += tolower(atomName[i]);

	for (i=0; i<atomNames_.size(); i++)
	{
		patternString = atomNames_[i].c_str();
		patternString += ".*";
		boost::regex regexPattern(patternString.c_str());

		if (boost::regex_match(tempName, regexPattern))
		{
			if (atomNames_[i].size() > maxLength)
			{
				maxLength = atomNames_[i].size();
				maxIndex = i;
			}
		}
	}

	if (maxIndex != -1)
	{
		*colorPointer = &(atomColors_[maxIndex]);
		return true;
	}
	else
		*colorPointer = &(atomColors_[atomColors_.size()-1]);			// last index must always be the DEFAULT color

	return false;
}

bool MoleculeColors::getAminoColor(std::string aminoName, Color **colorPointer)
{
	unsigned int i=0;
	string tempName;

	if (aminoNames_.size()==0 || aminoColors_.size()==0 || aminoNames_.size()!=aminoColors_.size() || aminoName=="")
		return false;

	tempName = "";
	for (i=0; i<aminoName.size(); i++)
		tempName += tolower(aminoName[i]);

	for (i=0; i<aminoNames_.size(); i++)
	{
		if (tempName == aminoNames_[i])
		{
			*colorPointer = &(aminoColors_[i]);
			return true;
		}
	}

	*colorPointer = &(aminoColors_[aminoColors_.size()-1]);			// last index must always be the DEFAULT color

	return false;
}

bool MoleculeColors::getChainColor(std::string chainName, Color **colorPointer)
{
	unsigned int i=0;
	string tempName;

	if (chainNames_.size()==0 || chainColors_.size()==0 || chainNames_.size()!=chainColors_.size() || chainName=="")
		return false;

	tempName = "";
	for (i=0; i<chainName.size(); i++)
		tempName += tolower(chainName[i]);

	for (i=0; i<chainNames_.size(); i++)
	{
		if (tempName == chainNames_[i])
		{
			*colorPointer = &(chainColors_[i]);
			return true;
		}
	}

	*colorPointer = &(chainColors_[chainColors_.size()-1]);			// last index must always be the DEFAULT color

	return false;
}

bool MoleculeColors::setAtomColor(string atomName, Color color)
{
	for (unsigned int i=0; i<atomNames_.size(); i++)
	{
		if (atomName == atomNames_[i])
		{
			atomColors_[i] = color;
			return true;
		}
	}

	atomNames_.push_back(atomName);
	atomColors_.push_back(color);

	return false;
}

bool MoleculeColors::setAminoColor(string aminoName, Color color)
{
	for (unsigned int i=0; i<aminoNames_.size(); i++)
	{
		if (aminoName == aminoNames_[i])
		{
			aminoColors_[i] = color;
			return true;
		}
	}

	aminoNames_.push_back(aminoName);
	aminoColors_.push_back(color);

	return false;
}

bool MoleculeColors::setChainColor(string chainName, Color color)
{
	for (unsigned int i=0; i<chainNames_.size(); i++)
	{
		if (chainName == chainNames_[i])
		{
			chainColors_[i] = color;
			return true;
		}
	}

	chainNames_.push_back(chainName);
	chainColors_.push_back(color);

	return false;
}



MoleculeColors* MoleculeColors::getInstance(string colorsPath)
{
	if (singleInstance_ == NULL)
	{
		singleInstance_ = new MoleculeColors(colorsPath);
		return singleInstance_;
	}

	return singleInstance_;
}
