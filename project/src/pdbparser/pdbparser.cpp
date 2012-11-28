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

PdbFile::PdbFile(const char *fileName)
{
	Init(fileName);
}

void PdbFile::Init(const char *fileName)
{
	atomIndex_.clear();
	atomList_.clear();
	numAtoms_ = 0;
	useUnitedRadius_ = true;
	pdbArithmeticCenter_.init();
	pdbMassCenter_.init();
//	centerAtomsByMass();
	models_.clear();

	fileName_ = fileName;

	pdbArithmeticCenter_.init();
	pdbMassCenter_.init();

	atomRadii_.init();
	centerAtomsArithmetically_ = false;
	centerAtomsByMass_ = true;
	boundsMin_.x = 0.0f;	boundsMin_.y = 0.0f;	boundsMin_.z = 0.0f;
	boundsMax_.x = 0.0f;	boundsMax_.x = 0.0f;	boundsMax_.z = 0.0f;

	models_.clear();

	elementNames_.clear();
	elementMass_.clear();

	pdbName_ = "";
}

void PdbFile::clear()
{
	atomIndex_.clear();
	atomList_.clear();
	numAtoms_ = 0;
	pdbArithmeticCenter_.init();
	pdbMassCenter_.init();
	models_.clear();

	pdbArithmeticCenter_.init();
	pdbMassCenter_.init();

	models_.clear();
	elementNames_.clear();
}

PdbFile::~PdbFile()
{
	clear();
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

	if (line.size() == 0)
		return line;

	trimmed = false;
	for (i=0; i<line.length(); i++)
	{
		if (line.c_str()[i]!=' ' && line.c_str()[i]!='\t')	trimmed = true;
		if (trimmed == true)	temp_ret = temp_ret + ((char)tolower(line.c_str()[i]));
	}

	if (temp_ret.size() == 0)
		return temp_ret;

	for (i=(temp_ret.length()-1); i>=0; i--)
		if (temp_ret.c_str()[i]!=' ' && temp_ret.c_str()[i]!='\t')	break;

	ret = temp_ret.substr(0, (i+1));

	return ret;
}

bool PdbFile::Import(bool centerAtoms)
{
	char tempChar[2];
	double totalMass=0.0f;
	string line, keyWord;
	string x, y, z;
	AtomPdb tempAtom;
	Model currentModel;

	ifstream input((char *) fileName_.c_str());

	if (input == NULL)
	{
		fprintf(stderr, "Can't find pdb file.");
//		exit(1);
		return false;
	}

	clear();

	if (getName() == "")
		setName(fileName_);

	pdbArithmeticCenter_.x = 0.0f;
	pdbArithmeticCenter_.y = 0.0f;
	pdbArithmeticCenter_.z = 0.0f;

	pdbMassCenter_.x = 0.0f;
	pdbMassCenter_.y = 0.0f;
	pdbMassCenter_.z = 0.0f;



	while (getline(input, line))
	{
		if (line.size() < 55)
			continue;

		if (line.size()>=55 && line.size()<80);
		{
			unsigned int i=0, lineSize=0;
			lineSize = line.size();
			for (i=lineSize; i<81; i++)
				line += " ";
		}

		keyWord = line.substr(0, 6);
		keyWord = trimAndLower(keyWord);

		if (strncmp(keyWord.c_str(), "model", 5)==0 || strncmp(keyWord.c_str(), "endmdl", 6)==0)
		{
			if (currentModel.getAtomIndex().size() > 0)
			{
				currentModel.setAtomList(&atomList_);
				models_.push_back(currentModel);
			}

			currentModel.Clear();

			if (strncmp(keyWord.c_str(), "model", 5) == 0)
				currentModel.setName((std::string) line.substr(10, 4));
		}
		else if (strncmp(keyWord.c_str(), "atom", 4)==0 || strncmp(keyWord.c_str(), "hetatm", 6)==0)
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

			tempAtom.trim();
			tempAtom.mass = findMass((char *) tempAtom.atomName.c_str());

			totalMass += tempAtom.mass;

			MoleculeColors::getInstance()->getAtomColor(tempAtom.atomName, &(tempAtom.atomColorPointer));
			MoleculeColors::getInstance()->getAminoColor(tempAtom.resName, &(tempAtom.aminoColorPointer));
			MoleculeColors::getInstance()->getChainColor(tempAtom.chainId, &(tempAtom.chainColorPointer));

//			printf ("atomName = %s\n", tempAtom.atomName.c_str());
//			printf ("total_mass = %lf\n", tempAtom.mass);
//			char asd;
//			scanf("%c", &asd);




			pdbArithmeticCenter_.x += tempAtom.x;
			pdbArithmeticCenter_.y += tempAtom.y;
			pdbArithmeticCenter_.z += tempAtom.z;

			pdbMassCenter_.x += tempAtom.x * tempAtom.mass;
			pdbMassCenter_.y += tempAtom.y * tempAtom.mass;
			pdbMassCenter_.z += tempAtom.z * tempAtom.mass;

			tempAtom.originalLine = line;

//			atoms_.push_back(tempAtom);
//			currentModel.AddAtom(tempAtom);

			atomList_.push_back(tempAtom);
			atomIndex_.push_back((atomList_.size()-1));
//			currentModel.getAtoms().push_back(atomList_[atomList_.size()-1]);
			currentModel.getAtomIndex().push_back((atomList_.size()-1));

			numAtoms_ += 1;
		}
	}

	if (currentModel.getAtomIndex().size() > 0)
	{
		currentModel.setAtomList(&atomList_);
		models_.push_back(currentModel);
	}

	currentModel.Clear();

	pdbArithmeticCenter_.x /= numAtoms_;
	pdbArithmeticCenter_.y /= numAtoms_;
	pdbArithmeticCenter_.z /= numAtoms_;

	pdbMassCenter_.x /= totalMass;
	pdbMassCenter_.y /= totalMass;
	pdbMassCenter_.z /= totalMass;

//	printf ("total_mass = %lf\n", totalMass);
//	printf ("x = %lf\ty = %lf\tz = %lf\n", pdbMassCenter_.x, pdbMassCenter_.y, pdbMassCenter_.z);

	if (centerAtoms==true && centerAtomsArithmetically_==true)
	{
//		printf ("aritmetika!\n");
		centerAtomsArithmetically();
	}
	else if (centerAtoms==true && centerAtomsByMass_==true)
	{
//		printf ("masa!\n");
//		printf ("%f\t%f\t%f\n", pdbMassCenter_.x, pdbMassCenter_.y, pdbMassCenter_.z);
		centerAtomsByMass();
	}

	for (unsigned int i=0; i<models_.size(); i++)
		models_[i].MakeBonds();

	return true;
}

int PdbFile::LoadAtmtypenumbers(const char *fileName)
{
	radiusPath_ = fileName;
	return atomRadii_.loadRadii(fileName);
}

bool PdbFile::SaveCoords(const char *fileName)
{
    FILE *fp;

    fp = fopen (fileName, "w");
    if (fp == NULL)
    	return false;

    for (int i=0; i<numAtoms_; i++)
        fprintf (fp, "%lf %lf %lf %lf\n", atomList_[i].x, atomList_[i].y, atomList_[i].z, atomList_[i].r);

    fclose(fp);

	return true;
}

void PdbFile::makeTransformMatrix(double *transformMatrix, double r, double alpha, double beta, double gamma)
{
	double sinAlpha = sin(alpha), cosAlpha = cos(alpha);
	double sinBeta = sin(beta), cosBeta = cos(beta);
	double sinGamma = sin(gamma), cosGamma = cos(gamma);

/*
	transformMatrix[0]  = cosGamma*cosAlpha - cosBeta*sinGamma*sinAlpha;
	transformMatrix[1]  = cosAlpha*sinGamma + cosGamma*cosBeta*sinAlpha;
	transformMatrix[2]  = sinBeta*sinAlpha;
	transformMatrix[3] = 0.0;
	transformMatrix[4]  = -cosBeta*cosAlpha*sinGamma - cosGamma*sinAlpha;
	transformMatrix[5]  = cosGamma*cosBeta*cosAlpha - sinGamma*sinAlpha;
	transformMatrix[6]  = cosAlpha*sinBeta;
	transformMatrix[7] = sinGamma*sinBeta;
	transformMatrix[8]  = -cosGamma*sinBeta;
	transformMatrix[9]  = cosBeta;
	transformMatrix[10] = r;
	transformMatrix[11] = 0.0;
	transformMatrix[12]  = 0.0;
	transformMatrix[13]  = 0.0;
	transformMatrix[14]  = 0.0;
	transformMatrix[15] = 1.0;
*/

	transformMatrix[0] = cosAlpha*cosBeta*cosGamma - sinAlpha*sinGamma;
	transformMatrix[1] = cosAlpha*cosBeta*sinGamma + sinAlpha*cosGamma;
	transformMatrix[2] = -cosAlpha*sinBeta;
	transformMatrix[3] = 0.0f;

	transformMatrix[4] = -sinAlpha*cosBeta*cosGamma - cosAlpha*sinGamma;
	transformMatrix[5] = -sinAlpha*cosBeta*sinGamma + cosAlpha*cosGamma;
	transformMatrix[6] = sinAlpha*sinBeta;
	transformMatrix[7] = 0.0f;

/*
	transformMatrix[8] = r*sinBeta*cosGamma;
	transformMatrix[9] = r*sinBeta*sinGamma;
	transformMatrix[10] = r*cosBeta;
	transformMatrix[11] = 0.0f;
*/

	transformMatrix[8] = sinBeta*cosGamma;
	transformMatrix[9] = sinBeta*sinGamma;
	transformMatrix[10] = cosBeta;
	transformMatrix[11] = 0.0f;

	transformMatrix[12] = 0.0f;
	transformMatrix[13] = 0.0f;
	transformMatrix[14] = 0.0f;
	transformMatrix[15] = 1.0f;



/*
	for (int i=0; i<16; i++)
	{
		transformMatrix[i] = 0.0f;
		if ((i%5) == 0)
			transformMatrix[i] = 1.0f;
	}

/*
	transformMatrix[0] = cosAlpha;
	transformMatrix[1] = sinAlpha;
	transformMatrix[2] = 0.0f;
	transformMatrix[3] = 0.0f;

	transformMatrix[4] = -sinAlpha;
	transformMatrix[5] = cosAlpha;
	transformMatrix[6] = 0.0f;
	transformMatrix[7] = 0.0f;

	transformMatrix[8] = 0.0f;
	transformMatrix[9] = 0.0f;
	transformMatrix[10] = r;
	transformMatrix[11] = 0.0f;

	transformMatrix[12] = 0.0f;
	transformMatrix[13] = 0.0f;
	transformMatrix[14] = 0.0f;
	transformMatrix[15] = 1.0f;
*/

/*
	transformMatrix[14] = r;
	printf ("%lf\n", r);
*/


}

bool PdbFile::writeTransformedAtoms(FILE *fpOutput, char chainDesignation, double r, double alpha, double beta, double gamma)
{
	double transformMatrix[16];
	AtomPdb transformedAtom;

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

	makeTransformMatrix(transformMatrix, r, -gamma, -beta, alpha);
//	printf ("Tu sam 1!\n");
//	printf ("\tatoms_.size() = %d\n", atoms_.size());

	for (unsigned int i=0; i<atomList_.size(); i++)
	{
//		printf ("%lf\t%lf\t%lf\n", atoms_[i].x, atoms_[i].y, atoms_[i].z);
//		char asd;
//		scanf("%c", &asd);

//		printf ("i = %d\n", i);

//		printf ("original_line = %s\n", transformedAtom.originalLine.c_str());
		transformedAtom = atomList_[i].transformCoordinates(transformMatrix, chainDesignation);
		transformedAtom.z += r;
		transformedAtom.originalLine = transformedAtom.updateLineCoordinates();

		fprintf (fpOutput, "%s\n", transformedAtom.originalLine.c_str());
//		printf ("\toriginal_line = %s\n", transformedAtom.originalLine.c_str());

//		printf ("\ti = %d\n", i);
	}

//	fclose(fp);

	return true;
}

bool PdbFile::writeAtoms(FILE *fpOutput)
{
	for (unsigned int i=0; i<atomList_.size(); i++)
		fprintf (fpOutput, "%s\n", atomList_[i].originalLine.c_str());

	return true;
}

bool PdbFile::createTransformedPdbFile(PdbFile &newPdbFile, double r, double alpha, double beta, double gamma)
{
	double transformMatrix[16];
	AtomPdb transformedAtom;

//	newPdbFile = *this;

	newPdbFile.clear();
	newPdbFile = *this;
//	newPdbFile.getAtomList().clear();

	makeTransformMatrix(transformMatrix, r, -gamma, -beta, alpha);

	for (unsigned int i=0; i<atomList_.size(); i++)
	{
		transformedAtom = atomList_[i].transformCoordinates(transformMatrix, ' ');
		transformedAtom.z += r;
		transformedAtom.originalLine = transformedAtom.updateLineCoordinates();

		newPdbFile.getAtomList()[i] = transformedAtom;
//		newPdbFile.setAtom(i, transformedAtom);
//		newPdbFile.getAtomList().push_back(transformedAtom);
	}

//	newPdbFile.getModels().resize(models_.size());

/*
	for (unsigned int i=0; i<models_.size(); i++)
	{
		for (unsigned int j=0; j<models_[i].getAtoms().size(); j++)
		{
			transformedAtom = atoms_[i].transformCoordinates(transformMatrix, ' ');
			transformedAtom.z -= r;
			transformedAtom.originalLine = transformedAtom.updateLineCoordinates();

			newPdbFile.getModels()[i].getAtoms().push_back(transformedAtom);
//			newPdbFile.getModels()[i].setNumAtoms(newPdbFile.getModels()[i].getNumAtoms() + 1);
		}
	}
*/

	return true;
}

void PdbFile::centerAtomsArithmetically()
{
	centerAtomsArithmetically_ = true;
	centerAtomsByMass_ = false;

	center();
}

void PdbFile::centerAtomsByMass()
{
	centerAtomsArithmetically_ = false;
	centerAtomsByMass_ = true;

	center();
}

void PdbFile::findCenters()
{
	double totalMass=0.0f;

	pdbArithmeticCenter_.x = 0.0f;
	pdbArithmeticCenter_.y = 0.0f;
	pdbArithmeticCenter_.z = 0.0f;

	pdbMassCenter_.x = 0.0f;
	pdbMassCenter_.y = 0.0f;
	pdbMassCenter_.z = 0.0f;

	for (unsigned int i=0; i<atomList_.size(); i++)
	{
		pdbArithmeticCenter_.x += atomList_[i].x;
		pdbArithmeticCenter_.y += atomList_[i].y;
		pdbArithmeticCenter_.z += atomList_[i].z;

		pdbMassCenter_.x += atomList_[i].x * atomList_[i].mass;
		pdbMassCenter_.y += atomList_[i].y * atomList_[i].mass;
		pdbMassCenter_.z += atomList_[i].z * atomList_[i].mass;


		if (i == 0)
		{
			boundsMin_.x = atomList_[i].x;	boundsMin_.y = atomList_[i].y;	boundsMin_.z = atomList_[i].z;
			boundsMax_.x = atomList_[i].x;	boundsMax_.y = atomList_[i].y;	boundsMax_.z = atomList_[i].z;
		}

		if (atomList_[i].x < boundsMin_.x)
			boundsMin_.x = atomList_[i].x;
		if (atomList_[i].y < boundsMin_.y)
			boundsMin_.y = atomList_[i].y;
		if (atomList_[i].z < boundsMin_.z)
			boundsMin_.z = atomList_[i].z;

		if (atomList_[i].x > boundsMax_.x)
			boundsMax_.x = atomList_[i].x;
		if (atomList_[i].y > boundsMax_.y)
			boundsMax_.y = atomList_[i].y;
		if (atomList_[i].z > boundsMax_.z)
			boundsMax_.z = atomList_[i].z;

//		printf ("mass[%d] = %lf\n", i, atomList_[i].mass);
		totalMass += atomList_[i].mass;
	}

	if (atomList_.size() > 0)
	{
//		printf ("3\n");

		pdbArithmeticCenter_.x /= atomList_.size();
		pdbArithmeticCenter_.y /= atomList_.size();
		pdbArithmeticCenter_.z /= atomList_.size();
	}

//	printf ("name = %s\ntotalMass = %lf\n\n", pdbName_.c_str(), totalMass);

	if (totalMass > 0.0f)
	{
		pdbMassCenter_.x /= totalMass;
		pdbMassCenter_.y /= totalMass;
		pdbMassCenter_.z /= totalMass;
	}
}

void PdbFile::center()
{
	double totalMass=0.0f;

// 	printf ("1 ");

	if (centerAtomsArithmetically_==false && centerAtomsByMass_==false)
		return;

//	printf ("2 %s\n", this->getName().c_str());

	findCenters();

	centered_ = true;

//	printf ("%f\t%f\t%f\t%f\n", pdbMassCenter_.x, pdbMassCenter_.y, pdbMassCenter_.z, totalMass);

	if (centerAtomsArithmetically_ == true)
	{
		for (unsigned int i=0; i<atomList_.size(); i++)
		{
			atomList_[i].x -= pdbArithmeticCenter_.x;
			atomList_[i].y -= pdbArithmeticCenter_.y;
			atomList_[i].z -= pdbArithmeticCenter_.z;

			atomList_[i].originalLine = atomList_[i].updateLineCoordinates();
		}

/*
		for (unsigned int i=0; i<models_.size(); i++)
		{
			for (unsigned int j=0; j<models_[i].getAtoms().size(); j++)
			{
				models_[i].getAtoms()[j].x -= pdbArithmeticCenter_.x;
				models_[i].getAtoms()[j].y -= pdbArithmeticCenter_.y;
				models_[i].getAtoms()[j].z -= pdbArithmeticCenter_.z;

				models_[i].getAtoms()[j].originalLine = models_[i].getAtoms()[j].updateLineCoordinates();
			}
		}
*/
	}
	else if (centerAtomsByMass_ == true)
	{
		for (unsigned int i=0; i<atomList_.size(); i++)
		{
			atomList_[i].x -= pdbMassCenter_.x;
			atomList_[i].y -= pdbMassCenter_.y;
			atomList_[i].z -= pdbMassCenter_.z;

			atomList_[i].originalLine = atomList_[i].updateLineCoordinates();
		}

/*
		for (unsigned int i=0; i<models_.size(); i++)
		{
			for (unsigned int j=0; j<models_[i].getAtoms().size(); j++)
			{
				models_[i].getAtoms()[j].x -= pdbMassCenter_.x;
				models_[i].getAtoms()[j].y -= pdbMassCenter_.y;
				models_[i].getAtoms()[j].z -= pdbMassCenter_.z;

				models_[i].getAtoms()[j].originalLine = models_[i].getAtoms()[j].updateLineCoordinates();
			}
		}
*/
	}
}

double PdbFile::findMass(char *atomName)
{
	unsigned int i=0, maxLength=0;
	int maxIndex=-1;
	string patternString;

	if (elementNames_.size()==0 || elementMass_.size()==0)
		loadMass();

//	printf ("elementNames.size() = %d\n", elementNames_.size());
//	printf ("strlen = %d\n", strlen(atomName));
//	printf ("atomName = %s\n", atomName);

	for (i=0; i<elementNames_.size(); i++)
	{
		patternString = elementNames_[i].c_str();
		patternString += ".*";
		boost::regex regexPattern(patternString.c_str());

		if (boost::regex_match(atomName, regexPattern))
		{
			if (elementNames_[i].size() > maxLength)
			{
				maxLength = elementNames_[i].size();
				maxIndex = i;
			}
		}
	}

	if (maxIndex != -1)
		return elementMass_[maxIndex];

	return 0.0f;
}


bool PdbFile::loadMass(char *massPath)
{
	int tempIndex=0;
	double tempMass=0.0f;
	char tempFullName[100], tempShortName[100];
	string buffer;
	ifstream input(massPath);

	elementNames_.clear();
	elementMass_.clear();

	if (input == NULL)
	{
		printf ("Path to the mass file does not exist!");
		return false;
	}

	while (getline(input, buffer))
	{
		sscanf(buffer.c_str(), "%lf %s %s %d", &tempMass, tempFullName, tempShortName, &tempIndex);

		elementNames_.push_back(tempShortName);
		elementMass_.push_back(tempMass);

//		printf ("%s\t%lf\n", tempShortName, tempMass);
//		printf ("elementNames_.push_back(\"%s\");\telementMass_.push_back(%lff);\n", tempShortName, tempMass);
	}

	return true;
}

bool PdbFile::loadMass()
{
	elementNames_.clear();
	elementMass_.clear();

	elementNames_.push_back("H");	elementMass_.push_back(1.007940f);
	elementNames_.push_back("He");	elementMass_.push_back(4.002602f);
	elementNames_.push_back("Li");	elementMass_.push_back(6.941000f);
	elementNames_.push_back("Be");	elementMass_.push_back(9.012182f);
	elementNames_.push_back("B");	elementMass_.push_back(10.811000f);
	elementNames_.push_back("C");	elementMass_.push_back(12.011000f);
	elementNames_.push_back("N");	elementMass_.push_back(14.006740f);
	elementNames_.push_back("O");	elementMass_.push_back(15.999400f);
	elementNames_.push_back("F");	elementMass_.push_back(18.998400f);
	elementNames_.push_back("Ne");	elementMass_.push_back(20.179700f);
	elementNames_.push_back("Na");	elementMass_.push_back(22.989770f);
	elementNames_.push_back("Mg");	elementMass_.push_back(24.305000f);
	elementNames_.push_back("Al");	elementMass_.push_back(26.981540f);
	elementNames_.push_back("Si");	elementMass_.push_back(28.085500f);
	elementNames_.push_back("P");	elementMass_.push_back(30.973760f);
	elementNames_.push_back("S");	elementMass_.push_back(32.066000f);
	elementNames_.push_back("Cl");	elementMass_.push_back(35.452700f);
	elementNames_.push_back("K");	elementMass_.push_back(39.098300f);
	elementNames_.push_back("Ar");	elementMass_.push_back(39.948000f);
	elementNames_.push_back("Ca");	elementMass_.push_back(40.078000f);
	elementNames_.push_back("Sc");	elementMass_.push_back(44.955910f);
	elementNames_.push_back("Ti");	elementMass_.push_back(47.880000f);
	elementNames_.push_back("V");	elementMass_.push_back(50.941500f);
	elementNames_.push_back("Cr");	elementMass_.push_back(51.996100f);
	elementNames_.push_back("Mn");	elementMass_.push_back(54.938050f);
	elementNames_.push_back("Fe");	elementMass_.push_back(55.847000f);
	elementNames_.push_back("Ni");	elementMass_.push_back(58.693400f);
	elementNames_.push_back("Co");	elementMass_.push_back(58.933200f);
	elementNames_.push_back("Cu");	elementMass_.push_back(63.546000f);
	elementNames_.push_back("Zn");	elementMass_.push_back(65.390000f);
	elementNames_.push_back("Ga");	elementMass_.push_back(69.723000f);
	elementNames_.push_back("Ge");	elementMass_.push_back(72.610000f);
	elementNames_.push_back("As");	elementMass_.push_back(74.921590f);
	elementNames_.push_back("Se");	elementMass_.push_back(78.960000f);
	elementNames_.push_back("Br");	elementMass_.push_back(79.904000f);
	elementNames_.push_back("Kr");	elementMass_.push_back(83.800000f);
	elementNames_.push_back("Rb");	elementMass_.push_back(85.467800f);
	elementNames_.push_back("Sr");	elementMass_.push_back(87.620000f);
	elementNames_.push_back("Y");	elementMass_.push_back(88.905850f);
	elementNames_.push_back("Zr");	elementMass_.push_back(91.224000f);
	elementNames_.push_back("Nb");	elementMass_.push_back(92.906380f);
	elementNames_.push_back("Mo");	elementMass_.push_back(95.940000f);
	elementNames_.push_back("Tc");	elementMass_.push_back(98.000000f);
	elementNames_.push_back("Ru");	elementMass_.push_back(101.070000f);
	elementNames_.push_back("Rh");	elementMass_.push_back(102.905500f);
	elementNames_.push_back("Pd");	elementMass_.push_back(106.420000f);
	elementNames_.push_back("Ag");	elementMass_.push_back(107.868200f);
	elementNames_.push_back("Cd");	elementMass_.push_back(112.411000f);
	elementNames_.push_back("In");	elementMass_.push_back(114.818000f);
	elementNames_.push_back("Sn");	elementMass_.push_back(118.710000f);
	elementNames_.push_back("Sb");	elementMass_.push_back(121.757000f);
	elementNames_.push_back("I");	elementMass_.push_back(126.904500f);
	elementNames_.push_back("Te");	elementMass_.push_back(127.600000f);
	elementNames_.push_back("Xe");	elementMass_.push_back(131.290000f);
	elementNames_.push_back("Cs");	elementMass_.push_back(132.905400f);
	elementNames_.push_back("Ba");	elementMass_.push_back(137.327000f);
	elementNames_.push_back("La");	elementMass_.push_back(138.905500f);
	elementNames_.push_back("Ce");	elementMass_.push_back(140.115000f);
	elementNames_.push_back("Pr");	elementMass_.push_back(140.907700f);
	elementNames_.push_back("Nd");	elementMass_.push_back(144.240000f);
	elementNames_.push_back("Pm");	elementMass_.push_back(145.000000f);
	elementNames_.push_back("Sm");	elementMass_.push_back(150.360000f);
	elementNames_.push_back("Eu");	elementMass_.push_back(151.965000f);
	elementNames_.push_back("Gd");	elementMass_.push_back(157.250000f);
	elementNames_.push_back("Tb");	elementMass_.push_back(158.925300f);
	elementNames_.push_back("Dy");	elementMass_.push_back(162.500000f);
	elementNames_.push_back("Ho");	elementMass_.push_back(164.930300f);
	elementNames_.push_back("Er");	elementMass_.push_back(167.260000f);
	elementNames_.push_back("Tm");	elementMass_.push_back(168.934200f);
	elementNames_.push_back("Yb");	elementMass_.push_back(173.040000f);
	elementNames_.push_back("Lu");	elementMass_.push_back(174.967000f);
	elementNames_.push_back("Hf");	elementMass_.push_back(178.490000f);
	elementNames_.push_back("Ta");	elementMass_.push_back(180.947900f);
	elementNames_.push_back("W");	elementMass_.push_back(183.850000f);
	elementNames_.push_back("Re");	elementMass_.push_back(186.207000f);
	elementNames_.push_back("Os");	elementMass_.push_back(190.200000f);
	elementNames_.push_back("Ir");	elementMass_.push_back(192.220000f);
	elementNames_.push_back("Pt");	elementMass_.push_back(195.080000f);
	elementNames_.push_back("Au");	elementMass_.push_back(196.966500f);
	elementNames_.push_back("Hg");	elementMass_.push_back(200.590000f);
	elementNames_.push_back("Tl");	elementMass_.push_back(204.383300f);
	elementNames_.push_back("Pb");	elementMass_.push_back(207.200000f);
	elementNames_.push_back("Bi");	elementMass_.push_back(208.980400f);
	elementNames_.push_back("Po");	elementMass_.push_back(208.982400f);
	elementNames_.push_back("At");	elementMass_.push_back(209.987100f);
	elementNames_.push_back("Pa");	elementMass_.push_back(213.035900f);
	elementNames_.push_back("Rn");	elementMass_.push_back(222.000000f);
	elementNames_.push_back("Fr");	elementMass_.push_back(223.000000f);
	elementNames_.push_back("Ra");	elementMass_.push_back(226.025400f);
	elementNames_.push_back("Ac");	elementMass_.push_back(227.072800f);
	elementNames_.push_back("Th");	elementMass_.push_back(232.038100f);
	elementNames_.push_back("Np");	elementMass_.push_back(237.048200f);
	elementNames_.push_back("U");	elementMass_.push_back(238.028900f);
	elementNames_.push_back("Am");	elementMass_.push_back(243.061400f);
	elementNames_.push_back("Pu");	elementMass_.push_back(244.064200f);
	elementNames_.push_back("Cm");	elementMass_.push_back(247.000000f);
	elementNames_.push_back("Bk");	elementMass_.push_back(247.000000f);
	elementNames_.push_back("Cf");	elementMass_.push_back(251.000000f);
	elementNames_.push_back("Es");	elementMass_.push_back(252.000000f);
	elementNames_.push_back("Fm");	elementMass_.push_back(257.000000f);
	elementNames_.push_back("Md");	elementMass_.push_back(258.000000f);
	elementNames_.push_back("No");	elementMass_.push_back(259.000000f);
	elementNames_.push_back("Lr");	elementMass_.push_back(260.000000f);
	elementNames_.push_back("Rf");	elementMass_.push_back(261.000000f);
	elementNames_.push_back("Db");	elementMass_.push_back(262.000000f);
	elementNames_.push_back("Bh");	elementMass_.push_back(262.000000f);
	elementNames_.push_back("Sg");	elementMass_.push_back(263.000000f);
	elementNames_.push_back("Hs");	elementMass_.push_back(265.000000f);
	elementNames_.push_back("Mt");	elementMass_.push_back(266.000000f);
	elementNames_.push_back("Ds");	elementMass_.push_back(271.000000f);
	elementNames_.push_back("Rg");	elementMass_.push_back(272.000000f);

	return true;
}

unsigned int PdbFile::getNumAtoms()
{
	return atomList_.size();
}

AtomPdb* PdbFile::getAtom(unsigned int index)
{
	return &(atomList_[index]);
}

void PdbFile::setAtom(unsigned int index, AtomPdb &newAtom)
{
	atomList_[index] = newAtom;
}

PdbFile& PdbFile::operator= (PdbFile &op1)
{
/*
	std::vector <Atom> atoms_;
	int numAtoms_;
	bool useUnitedRadius_;
	Coordinates pdbArithmeticCenter_;
	Coordinates pdbMassCenter_;
	std::string fileName_;
	AtomRadii atomRadii_;
	bool centerAtomsArithmetically_;
	bool centerAtomsByMass_;

	std::vector <Model> models_;

	std::vector<std::string> elementNames_;
	std::vector<double> elementMass_;
*/

/*
	atoms_ = op1.getAtoms();
	numAtoms_ = op1.getNumAtoms();
	useUnitedRadius_ = op1.getUseUnitedRadius();
	pdbArithmeticCenter_ = op1.getPdbArithmeticCenter();
	pdbMassCenter_ = op1.getPdbMassCenter();
	fileName_ = op1.getFileName();
	atomRadii_ = op1.getAtomRadii();
	centerAtomsArithmetically_ = op1.getCenterAtomsArithmetically();
	centerAtomsByMass_ = op1.getCenterAtomsByMass();
	models_ = op1.getModels();
	loadMass();
*/

	atomIndex_ = op1.getAtomIndex();
	atomList_ = op1.getAtomList();
	numAtoms_ = op1.getNumAtoms();
	useUnitedRadius_ = op1.getUseUnitedRadius();
	pdbArithmeticCenter_ = op1.getPdbArithmeticCenter();
	pdbMassCenter_ = op1.getPdbMassCenter();
	fileName_ = op1.getFileName();
	atomRadii_ = op1.getAtomRadii();
	centered_ = op1.getCentered();
	centerAtomsArithmetically_ = op1.getCenterAtomsArithmetically();
	centerAtomsByMass_ = op1.getCenterAtomsByMass();
	models_ = op1.getModels();
	elementNames_ = op1.getElementNames();
	elementMass_ = op1.getElementMass();
	pdbName_ = op1.getName();

	return *this;
}

/*
vector<AtomPdb>& PdbFile::getAtoms()
{
	return atomList_;
}
*/

bool PdbFile::getUseUnitedRadius()
{
	return useUnitedRadius_;
}

Coordinates PdbFile::getPdbArithmeticCenter()
{
	return pdbArithmeticCenter_;
}

Coordinates PdbFile::getPdbMassCenter()
{
	return pdbMassCenter_;
}

string PdbFile::getFileName()
{
	return fileName_;
}

AtomRadii& PdbFile::getAtomRadii()
{
	return atomRadii_;
}

bool PdbFile::getCentered()
{
	return centered_;
}

bool PdbFile::getCenterAtomsArithmetically()
{
	return centerAtomsArithmetically_;
}

bool PdbFile::getCenterAtomsByMass()
{
	return centerAtomsByMass_;
}

vector<Model>& PdbFile::getModels()
{
	return models_;
}

void PdbFile::pushAtom(AtomPdb &newAtom)
{
	atomList_.push_back(newAtom);
	numAtoms_ += 1;
}

// void PdbFile::clear()
// {
// 	Init("");
// }

void PdbFile::setName(std::string pdbName)
{
	pdbName_ = pdbName;
}

std::string PdbFile::getName()
{
	return pdbName_;
}

std::vector<AtomPdb>& PdbFile::getAtomList()
{
	return atomList_;
}

std::vector<std::string>& PdbFile::getElementNames()
{
	return elementNames_;
}

std::vector<double>& PdbFile::getElementMass()
{
	return elementMass_;
}

std::vector<unsigned long int>& PdbFile::getAtomIndex()
{
	return atomIndex_;
}

std::string PdbFile::getRadiusPath()
{
	return radiusPath_;
}

void PdbFile::setRadiusPath(std::string path)
{
	radiusPath_ = path;
}



/**
 * \param modelIndex If greater or equal to zero, specifies the model that needs to be loaded from a PDB file. If equal to -1, all models are loaded. In case if this parameter is -2, then no models are loaded.
 * \param centerAtoms If true, the atoms will be centered, otherwise coordinates won't change.
 */
int PdbFile::importModel(long int modelIndex, bool centerAtoms)
{
	bool pdbCacheEmpty=true;
	char tempChar[2];
	unsigned long int lineIndex=0;
	unsigned long int cacheLineNumber=0, cacheEndLineNumber=0;
	long int currentModelIndex=0;
	double totalMass=0.0f;
	string line, keyWord;
	string x, y, z;
	AtomPdb tempAtom;
	Model newModel;
	PdbModelLocations modelLocation;

	ifstream input((char *) fileName_.c_str());

	if (input == NULL)
	{
		fprintf(stderr, "Can't find pdb file.");
		return 1;
	}

	clear();

	if (getName() == "")
		setName(fileName_);



	lineIndex = 0;
	currentModelIndex = 0;

	if (modelIndex == -2)
		return 0;

	if (pdbCache_.size() == 0)
		pdbCacheEmpty = true;
	else
		pdbCacheEmpty = false;

	if (pdbCacheEmpty==false && modelIndex>=0)
	{
		currentModelIndex = modelIndex;
		cacheLineNumber = modelLocations_[modelIndex].startLine;
		cacheEndLineNumber = modelLocations_[modelIndex].endLine;
	}
	else
	{
		cacheLineNumber = 0;
		cacheEndLineNumber = pdbCache_.size();
	}

//	printf ("cacheLineNumber = %d\n", cacheLineNumber);
//	printf ("cacheEndLineNumber = %d\n", cacheEndLineNumber);

	while ((pdbCacheEmpty==true && getline(input, line)) || (pdbCacheEmpty==false && cacheLineNumber<pdbCache_.size()))
	{
//		if (line.size() < 55)
//			continue;

//		if (line.size()>=55 && line.size()<80);

		if (pdbCacheEmpty == false)
		{
			if (cacheLineNumber >= cacheEndLineNumber)
				break;

			line = pdbCache_[cacheLineNumber];
			cacheLineNumber += 1;

//			printf ("Cache!\n");
		}
		else
		{
			pdbCache_.push_back(line);
//			printf ("Not Cache!\n");
		}

		if (line.size() < 80)
		{
			unsigned int i=0, lineSize=0;
			lineSize = line.size();
			for (i=lineSize; i<81; i++)
				line += " ";
		}

		keyWord = line.substr(0, 6);
		keyWord = trimAndLower(keyWord);

//		printf ("keyWord = '%s'\n", keyWord.c_str());
//		char asd;
//		scanf("%c", &asd);

		if (strncmp(keyWord.c_str(), "model", 5)==0 || strncmp(keyWord.c_str(), "endmdl", 6)==0)
		{
//			printf ("keyWord = '%s'\n", keyWord.c_str());

			if (keyWord == "model")
			{
				modelLocation.startLine = lineIndex;
				modelLocation.fpModel = NULL;
				newModel.setName((std::string) line.substr(10, 4));

//				printf ("begin -> currentModelIndex = %d\n", currentModelIndex);

				if ((currentModelIndex) == modelIndex)
				{
//					printf ("Nasao sam!\n");
				}

			}
			else if (keyWord == "endmdl")
			{
				modelLocation.endLine = lineIndex;
				modelLocations_.push_back(modelLocation);

//				printf ("end -> currentModelIndex = %d\n", currentModelIndex);

				currentModelIndex += 1;
			}

			if (newModel.getAtomIndex().size() > 0)
			{
				newModel.setAtomList(&atomList_);			// in a model, atoms are referenced by index. Since this index has to reference to some data, we give all models a pointer to the (indexed) atom list.
				models_.push_back(newModel);
			}

			newModel.Clear();
		}
		else if (strncmp(keyWord.c_str(), "atom", 4)==0 || strncmp(keyWord.c_str(), "hetatm", 6)==0)
		{
			if ((currentModelIndex)==modelIndex || modelIndex==-1)
			{
//				printf ("Nasao sam!\n");

				tempAtom.parseLine(line);

				tempChar[0] = tempAtom.atomName.c_str()[0];
				tempChar[1] = tempAtom.atomName.c_str()[1];

				if (isdigit(tempChar[0]) && (tempChar[1]=='H' || tempChar[1]=='h' || tempChar[1]=='G' || tempChar[1]=='g'))
					tempAtom.atomName = "H";
				if (tempChar[0]=='H' || tempChar[0]=='h' || tempChar[0]=='G' || tempChar[0]=='g')
					tempAtom.atomName = "H";

				tempAtom.r = atomRadii_.findRadius(&tempAtom, useUnitedRadius_);

				tempAtom.trim();
				tempAtom.mass = findMass((char *) tempAtom.atomName.c_str());

				MoleculeColors::getInstance()->getAtomColor(tempAtom.atomName, &(tempAtom.atomColorPointer));
				MoleculeColors::getInstance()->getAminoColor(tempAtom.resName, &(tempAtom.aminoColorPointer));
				MoleculeColors::getInstance()->getChainColor(tempAtom.chainId, &(tempAtom.chainColorPointer));

				atomList_.push_back(tempAtom);
				atomIndex_.push_back((atomList_.size()-1));
				newModel.getAtomIndex().push_back((atomList_.size()-1));

				numAtoms_ += 1;
			}
		}

		lineIndex += 1;
	}

	if (newModel.getAtomIndex().size() > 0)
	{
		newModel.setAtomList(&atomList_);
		models_.push_back(newModel);
	}

	newModel.Clear();

	if (centerAtoms==true && centerAtomsArithmetically_==true)
	{
		findCenters();
		centerAtomsArithmetically();
	}
	else if (centerAtoms==true && centerAtomsByMass_==true)
	{
		findCenters();
		centerAtomsByMass();
	}

	for (unsigned int i=0; i<models_.size(); i++)
		models_[i].MakeBonds();

	return 0;
}
