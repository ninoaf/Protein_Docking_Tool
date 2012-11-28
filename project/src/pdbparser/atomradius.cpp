#include "atomradius.h"

using namespace std;



AtomRadii::AtomRadii()
{
	init();
}

AtomRadii::~AtomRadii()
{
	init();
}

void AtomRadii::init()
{
	numPatterns_ = 0;
	atmTypeNumbersLoaded_ = false;

	residuePatterns_.clear();
	atomPatterns_.clear();

	atomNumber_.clear();
	for (int i=0; i<100; i++)
	{
		unitedRadius_[i] = 0.0f;
		explicitRadius_[0] = 0.0f;
	}
}

double AtomRadii::findRadius(AtomPdb *atom, bool useUnitedRadius)
{
	for (int i=0; i<numPatterns_; i++)
	{
		if (comparePattern(atomPatterns_[i], atom->atomName) && comparePattern(residuePatterns_[i], atom->resName))
		{
			if (useUnitedRadius == true)
				return unitedRadius_[atomNumber_[i]];

			return explicitRadius_[atomNumber_[i]];
		}
	}

	return 0.1f;
}

int AtomRadii::comparePattern(std::string pattern, std::string name)
{
	unsigned int i=0;
	string tempName;
	string tempPat;

	if (pattern.length()<=0 || name.length()<=0)
		return 3;

	if (pattern == "*")
		return 2;

	tempPat = "";
	for (i=0; i<pattern.length(); i++)
	{
		if (pattern.c_str()[i] != ' ')
			tempPat = tempPat + pattern.c_str()[i];
	}

	tempName = "";
	for (i=0; i<name.length(); i++)
	{
		if (name.c_str()[i] != ' ')
			tempName = tempName + name.c_str()[i];
	}



	if (tempPat.c_str()[0] == '*')
		tempPat = "." + tempPat;
	tempPat = "^" + tempPat + "$";

	boost::regex regexPattern(tempPat.c_str());

	if (boost::regex_match(tempName.c_str(), regexPattern))
		return 1;

	return 0;
}

string AtomRadii::clearMultipleVoids(string line)
{
	string ret;

	for (unsigned int i=0; i<line.length(); i++)
	{
		if (line.c_str()[i]!=' ' && line.c_str()[i]!='\t')
		{
			ret = ret + line.c_str()[i];
		}
		else
		{
			if (ret.length()>0 && ret.c_str()[(ret.length()-1)]!=' ' && ret.c_str()[(ret.length()-1)]!='\t')
				ret = ret + line.c_str()[i];
		}
	}

	return ret;
}

int AtomRadii::getNumParam(string line)
{
	int ret=0;

	for (unsigned int i=0; i<line.length(); i++)
		if (line.c_str()[i]==' ' || line.c_str()[i]=='\t')
			ret += 1;

	if (line.c_str()[(line.length()-1)] != ' ')
		ret += 1;

	return ret;
}

bool AtomRadii::loadRadii(string path)
{
	unsigned int i=0;
	int numParam=0, radiusNumber=0, tempInt=0;
    char param[10][100];
    double tempDist=0.0f, tempExplicit=0.0f, tempUnited=0.0f;
    string line;
    string resPat, namePat;
	ifstream input((char *) path.c_str());

	if (input == NULL)
		return false;

	numPatterns_ = 0;

	init();

	while (getline(input, line))
	{
		line = clearMultipleVoids(line);
		numParam = getNumParam(line);

		if (line.length()>0 && line.c_str()[0]!='#')
		{
            sscanf(line.c_str(), "%s %s %s %s %s", param[0], param[1], param[2], param[3], param[4]);

            if (strcmp(param[0], "radius")==0)
            {
                if (numParam==4 || param[4][0]=='#')
                {
                    sscanf(line.c_str(), "%s %d %lf %lf", param[0], &radiusNumber, &tempDist, &tempExplicit);
                    explicitRadius_[radiusNumber] = tempExplicit;
                    unitedRadius_[radiusNumber] = tempExplicit;
                }
                else if (numParam>4 && param[4][0]!='#')
                {
                    sscanf(line.c_str(), "%s %d %lf %lf %lf", param[0], &radiusNumber, &tempDist, &tempExplicit, &tempUnited);
                    explicitRadius_[radiusNumber] = tempExplicit;
                    unitedRadius_[radiusNumber] = tempUnited;
                }

                continue;
            }
            else
            {
				sscanf(line.c_str(), "%s %s %d", param[0], param[1], &tempInt);
				residuePatterns_.push_back(param[0]);
				atomPatterns_.push_back(param[1]);
				atomNumber_.push_back(tempInt);

				if (explicitRadius_[tempInt] == 0.0f)
				{
					explicitRadius_[tempInt] = 0.01f;
					unitedRadius_[tempInt] = 0.01f;
				}

				int patBegin=0, numPipes=0;
				string tempString;
				string tempAtmPat;
				int tempAtmNum;

				tempString = residuePatterns_[numPatterns_];
				tempAtmPat = atomPatterns_[numPatterns_];
				tempAtmNum = atomNumber_[numPatterns_];

				for (i=0; i<tempString.length(); i++)
				{
					if (tempString.c_str()[i] == '|')
					{
						residuePatterns_.push_back(tempString.substr(patBegin, (i-patBegin)));
						atomPatterns_.push_back(tempAtmPat);
						atomNumber_.push_back(tempAtmNum);

						patBegin = i + 1;
						numPipes += 1;
					}
				}

				if (i==tempString.length() && tempString.c_str()[(i-1)]!='|')
					residuePatterns_[numPatterns_] = tempString.substr(patBegin, (i-patBegin));

				numPatterns_ += numPipes;
				numPatterns_ += 1;
            }
		}

	}

	atmTypeNumbersLoaded_ = true;

    return true;
}
