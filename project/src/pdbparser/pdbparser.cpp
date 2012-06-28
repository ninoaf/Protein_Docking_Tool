/*
 * pdbparser.cpp
 *
 *  Created on: Nov 3, 2009
 *      Author: ivan
 */

#include "pdbparser.h"

using namespace std;



PdbFile::PdbFile()
{
	Init((char *) "");
}

PdbFile::PdbFile(char *fileName)
{
	Init(fileName);
}

void PdbFile::Init(char *fileName)
{
	atoms_.clear();
	numAtoms_ = 0;
	useUnitedRadius_ = true;
	pdbCenter_.init();

	fileName_ = fileName;
}

PdbFile::~PdbFile()
{
	atoms_.clear();
}

void PdbFile::UseUnitedRadius()
{
	useUnitedRadius_ = true;
}

void PdbFile::UseExplicitRadius()
{
	useUnitedRadius_ = false;
}

string PdbFile::trimAndLower(string line)
{
	unsigned int i=0;
	bool trimmed=false;
	string temp_ret, ret;

	trimmed = false;
	for (i=0; i<line.length(); i++)
	{
		if (line.c_str()[i]!=' ' && line.c_str()[i]!='\t')	trimmed = true;
		if (trimmed == true)	temp_ret = temp_ret + ((char)tolower(line.c_str()[i]));
	}

	for (i=(temp_ret.length()-1); i>=0; i--)
		if (temp_ret.c_str()[i]!=' ' && temp_ret.c_str()[i]!='\t')	break;
	ret = temp_ret.substr(0, (i+1));

	return ret;
}
void PdbFile::PutChargesOnGrid(Grid& grid)
{
	for (int i=0; i<numAtoms_; i++)
	{
		int x = round(atoms_[i].x) / grid.gridCellSize_ ;
		int y = round (atoms_[i].y) / grid.gridCellSize_ ;
		int z =  round(atoms_[i].z) / grid.gridCellSize_ ;
		GridValue tmpGrid(x, y, z, 1);
	}

}

bool PdbFile::Import(bool centerAtoms)
{
	char tempChar[2];
	string line, keyWord;
	string x, y, z;
	Atom tempAtom;
	ifstream input((char *) fileName_.c_str());

	if (input == NULL)
	{
		// can't open file
		return false;
	}

	pdbCenter_.x = 0.0f;
	pdbCenter_.y = 0.0f;
	pdbCenter_.z = 0.0f;

	while (getline(input, line))
	{
		if (line.size() < 80)
			continue;

		keyWord = line.substr(0, 6);
		keyWord = trimAndLower(keyWord);

		if (strncmp(keyWord.c_str(), "atom", 4)==0 || strncmp(keyWord.c_str(), "hetatm", 6)==0)
		{
			tempAtom.atomSerial = line.substr(6, 5);
			tempAtom.atomName = line.substr(12, 4);
			tempAtom.altLoc = line.substr(16, 1);
			tempAtom.resName = line.substr(17, 3);
			tempAtom.chainId = line.substr(21, 1);
			tempAtom.resSeq = line.substr(22, 4);
			tempAtom.insertionCode = line.substr(26, 1);
			tempAtom.xString = line.substr(30, 8);
			tempAtom.yString = line.substr(38, 8);
			tempAtom.zString = line.substr(46, 8);
			tempAtom.occupancy = line.substr(54, 6);
			tempAtom.tempFactor = line.substr(60, 6);
			tempAtom.segmentId = line.substr(72, 4);
			tempAtom.elementSymbol = line.substr(76, 2);
			tempAtom.charge = line.substr(78, 2);

			sscanf(tempAtom.xString.c_str(), "%lf", &(tempAtom.x));
			sscanf(tempAtom.yString.c_str(), "%lf", &(tempAtom.y));
			sscanf(tempAtom.zString.c_str(), "%lf", &(tempAtom.z));

			tempChar[0] = tempAtom.atomName.c_str()[0];
			tempChar[1] = tempAtom.atomName.c_str()[1];
		    if (isdigit(tempChar[0]) && (tempChar[1]=='H' || tempChar[1]=='h' || tempChar[1]=='G' || tempChar[1]=='g'))
		    	tempAtom.atomName = "H";
		    if (tempChar[0]=='H' || tempChar[0]=='h' || tempChar[0]=='G' || tempChar[0]=='g')
		    	tempAtom.atomName = "H";

			tempAtom.r = atomRadii_.findRadius(&tempAtom, useUnitedRadius_);

			pdbCenter_.x += tempAtom.x;
			pdbCenter_.y += tempAtom.y;
			pdbCenter_.z += tempAtom.z;

			tempAtom.originalLine = line;

			atoms_.push_back(tempAtom);
			numAtoms_ += 1;
		}
	}

	pdbCenter_.x /= numAtoms_;
	pdbCenter_.y /= numAtoms_;
	pdbCenter_.z /= numAtoms_;

	if (centerAtoms == true)
	{
		for (int i=0; i<numAtoms_; i++)
		{
			atoms_[i].x -= pdbCenter_.x;
			atoms_[i].y -= pdbCenter_.y;
			atoms_[i].z -= pdbCenter_.z;
		}
	}

	return true;
}

int PdbFile::LoadAtmtypenumbers(char *fileName)
{
	return atomRadii_.loadRadii(fileName);
}

bool PdbFile::SaveCoords(char *fileName)
{
    FILE *fp;

    fp = fopen (fileName, "w");
    if (fp == NULL)
    	return false;

    for (int i=0; i<numAtoms_; i++)
        fprintf (fp, "%lf %lf %lf %lf\n", atoms_[i].x, atoms_[i].y, atoms_[i].z, atoms_[i].r);

    fclose(fp);

	return true;
}

void PdbFile::MakeTransformMatrix(double *transformMatrix, double r, double alpha, double beta, double gamma)
{

}

bool PdbFile::WriteTransformedAtoms(FILE *fpOutput, char chainDesignation, double r, double alpha, double beta, double gamma)
{
	double transformMatrix[16];
	Atom transformedAtom;

/*
	FILE *fp;

	if (openMode != "w" && openMode != "a")
	{
		printf ("Invalid open mode! Use 'w' or 'a'.");
		return false;
	}

	fp = fopen(path.c_str(), openMode.c_str());
	if (fp == NULL)
		return false;
*/

	MakeTransformMatrix(transformMatrix, r, alpha, beta, gamma);

	for (int i=0; i<numAtoms_; i++)
	{
		transformedAtom = atoms_[i].TransformCoordinates(transformMatrix, chainDesignation);

		fprintf (fpOutput, "%s\n", transformedAtom.originalLine.c_str());
	}

//	fclose(fp);

	return true;
}
