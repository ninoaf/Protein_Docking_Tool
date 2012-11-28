/*
 * models.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: ivan
 */

#include "models.h"

using namespace std;



Model::Model()
{
	Clear();
}

Model::~Model()
{
	Clear();
}

void Model::Clear()
{
	atomIndex_.clear();
	name_ = "";
	bonds_.clear();
	modelArithmeticCenter_.init();
	modelMassCenter_.init();
	boundsMin_.x = 0.0f;	boundsMin_.y = 0.0f;	boundsMin_.z = 0.0f;
	boundsMax_.x = 0.0f;	boundsMax_.y = 0.0f;	boundsMax_.z = 0.0f;
	centerAtomsByMass_ = true;
	centerAtomsArithmetically_ = false;
}

/*
void Model::AddAtom(AtomPdb *atom)
{
	atoms_.push_back(atom);
}
*/

std::vector<unsigned long int>& Model::getAtomIndex()
{
	return (atomIndex_);
}

std::string Model::getName()
{
	return name_;
}

void Model::setName(std::string name)
{
	name_ = name;
}

/*
void Model::calculateArithmeticCenter()
{
	unsigned int i=0;
	Coordinates center;

	if (atomList_ == NULL)
		return;

	center.init();

	for (i=0; i<atomIndex_.size(); i++)
	{
		center.x += getAtom(i).x;
		center.y += getAtom(i).y;
		center.z += getAtom(i).z;
	}

	center.x /= atomIndex_.size();
	center.y /= atomIndex_.size();
	center.z /= atomIndex_.size();

	modelArithmeticCenter_ = center;
}
*/

Coordinates Model::getArithmeticCenter()
{
	return modelArithmeticCenter_;
}

// void Model::calculateMassCenter()
void Model::findCenters()
{
	unsigned int i=0;
	double totalMass=0.0f;
	Coordinates centerArithmetic;
	Coordinates centerMass;

	if (atomList_ == NULL)
		return;

	centerArithmetic.init();
	centerMass.init();

	for (i=0; i<atomIndex_.size(); i++)
	{
		centerMass.x += getAtom(i).x * getAtom(i).mass;
		centerMass.y += getAtom(i).y * getAtom(i).mass;
		centerMass.z += getAtom(i).z * getAtom(i).mass;

		centerArithmetic.x += getAtom(i).x;
		centerArithmetic.y += getAtom(i).y;
		centerArithmetic.z += getAtom(i).z;

		if (i == 0)
		{
			boundsMin_.x = getAtom(i).x;	boundsMin_.y = getAtom(i).y;	boundsMin_.z = getAtom(i).z;
			boundsMax_.x = getAtom(i).x;	boundsMax_.y = getAtom(i).y;	boundsMax_.z = getAtom(i).z;
		}

		if (getAtom(i).x < boundsMin_.x)
			boundsMin_.x = getAtom(i).x;
		if (getAtom(i).y < boundsMin_.y)
			boundsMin_.y = getAtom(i).y;
		if (getAtom(i).z < boundsMin_.z)
			boundsMin_.z = getAtom(i).z;

		if (getAtom(i).x > boundsMax_.x)
			boundsMax_.x = getAtom(i).x;
		if (getAtom(i).y > boundsMax_.y)
			boundsMax_.y = getAtom(i).y;
		if (getAtom(i).z > boundsMax_.z)
			boundsMax_.z = getAtom(i).z;

		totalMass += getAtom(i).mass;
	}

	centerMass.x /= totalMass;
	centerMass.y /= totalMass;
	centerMass.z /= totalMass;

	centerArithmetic.x /= atomIndex_.size();
	centerArithmetic.y /= atomIndex_.size();
	centerArithmetic.z /= atomIndex_.size();

	modelMassCenter_ = centerMass;
	modelArithmeticCenter_ = centerArithmetic;
}

Coordinates Model::getMassCenter()
{
	return modelMassCenter_;
}

void Model::centerAtomsArithmetically()
{
	unsigned int i=0;

	getArithmeticCenter();

	for (i=0; i<atomIndex_.size(); i++)
	{
		getAtom(i).x -= modelArithmeticCenter_.x;
		getAtom(i).y -= modelArithmeticCenter_.y;
		getAtom(i).z -= modelArithmeticCenter_.z;
	}
}

void Model::centerAtomsByMass()
{
	unsigned int i=0;

	getMassCenter();

	for (i=0; i<atomIndex_.size(); i++)
	{
		getAtom(i).x -= modelArithmeticCenter_.x;
		getAtom(i).y -= modelArithmeticCenter_.y;
		getAtom(i).z -= modelArithmeticCenter_.z;
	}
}

void Model::MakeBonds()
{
	unsigned int i=0, j=0;
	double distance=0.0f, maxDistance=0.0f;
	Bond currentBond;

	if (atomList_ == NULL)
		return;

	bonds_.clear();

//	FILE *fp;
//	fp = fopen("asd.txt", "w");

//	fprintf (fp, "atoms_.size() = %d\n", atoms_.size());

//	fprintf (fp, "------------------------------\n");

	for (i=0; i<atomIndex_.size(); i++)
	{
		for (j=(i+1); j<atomIndex_.size(); j++)
		{
            distance = sqrt((double) ((getAtom(i).x - getAtom(j).x)*(getAtom(i).x - getAtom(j).x) + (getAtom(i).y - getAtom(j).y)*(getAtom(i).y - getAtom(j).y) + (getAtom(i).z - getAtom(j).z)*(getAtom(i).z - getAtom(j).z)));
            maxDistance = getAtom(i).r + getAtom(j).r; // + 0.56

            maxDistance = maxDistance * 1.0f/2.0f;

            if (distance <= maxDistance)
            {
/*
            	fprintf (fp, "i = %d\nj = %d\n", i, j);
            	fprintf (fp, "distance = %f\n", distance);
            	fprintf (fp, "radius1 = %f\nradius2 = %f\n", atoms_[i].r, atoms_[j].r);
            	fprintf (fp, "maxDistance = %f\n\n", maxDistance);
*/

//            	char asd;
//            	scanf("%c", &asd);

            	currentBond.atom1 = &getAtom(i);
            	currentBond.atom2 = &getAtom(j);

            	bonds_.push_back(currentBond);
            }
		}

//		fprintf (fp, "------------------------------\n");
//		break;
	}
}

std::vector<Bond>& Model::getBonds()
{
	return bonds_;
}

vector<AtomPdb>* Model::getAtomList()
{
	return atomList_;
}

void Model::setAtomList(std::vector<AtomPdb> *atomList)
{
	atomList_ = atomList;
}

AtomPdb& Model::getAtom(unsigned long int atomIndex)
{
	return (*atomList_)[atomIndex_[atomIndex]];
}

bool Model::getCenterAtomsByMass()
{
	return centerAtomsByMass_;
}

bool Model::getCenterAtomsArithmetically()
{
	return centerAtomsArithmetically_;
}
