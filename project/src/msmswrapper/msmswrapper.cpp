/*
 * msmswrapper.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: ivan
 */

#include "msmswrapper.h"

using namespace std;



MSMSWrapper::MSMSWrapper()
{
	init();
}

MSMSWrapper::~MSMSWrapper()
{
	clear();
}

void MSMSWrapper::init()
{
	numSpheres = 0;
	density = 0.0f;
	probeRadius = 0.0f;
	vertices.clear();
	faces.clear();
}

void MSMSWrapper::clear()
{
	vertices.clear();
	faces.clear();
}

bool MSMSWrapper::load(std::string filePath, bool import)
{
	bool ret1=false, ret2=false, ret3=false;
	string cmdLine;

	cmdLine = "./data/system/msms -if ";
	cmdLine = cmdLine + filePath + " -of ";
	cmdLine += filePath;
	cmdLine += " > data/log/log_msms_output.txt 2> /dev/null";
	ret1 = system(cmdLine.c_str());

    if (ret1 != 0)
    {
        fprintf(stderr, "Can't find msms executable. Should be in data/msmsx\n");
        exit(1);
    }

    if (import == true)
    {
		cmdLine = filePath;
		cmdLine += ".vert";
		ret2 = importCoords(cmdLine.c_str());
		remove(cmdLine.c_str());

		cmdLine = filePath;
		cmdLine += ".face";
		ret3 = importFaces(cmdLine.c_str());
		remove(cmdLine.c_str());

		return (!ret1 && ret2 && ret3);
    }

    return !ret1;
}

bool MSMSWrapper::importCoords(string filePath)
{
	unsigned int lineNumber=0;
	string line;
	MSMSCoord temp;
	ifstream input((char *) filePath.c_str());

	if (input == NULL)
		return false;

	vertices.clear();

	while (getline(input, line))
	{
		if (line.length()>0)
		{
			if (lineNumber == 2)
			{
				// header
				sscanf (line.c_str(), "%d %d %lf %lf", &numCoords, &numSpheres, &density, &probeRadius);
			}
			else if (lineNumber > 2)
			{
				sscanf (line.c_str(), "%lf %lf %lf %lf %lf %lf %ld %ld %ld", &temp.coord.x, &temp.coord.y, &temp.coord.z, &temp.vector.x, &temp.vector.y, &temp.vector.z, &temp.d, &temp.atomNumber, &temp.f);
				vertices.push_back(temp);
			}
		}

		lineNumber += 1;
	}

	return true;
}

bool MSMSWrapper::importFaces(string filePath)
{
	unsigned int lineNumber=0;
	string line;
	MSMSFace temp;
	ifstream input((char *) filePath.c_str());

	if (input == NULL)
		return false;

	while (getline(input, line))
	{
		if (line.length()>0)
		{
			if (lineNumber == 2)
			{
				// header
				sscanf (line.c_str(), "%d %d %lf %lf", &numFaces, &numSpheres, &density, &probeRadius);
			}
			else if (lineNumber > 2)
			{
				sscanf (line.c_str(), "%d %d %d %d %d", &(temp.face.index[0]), &(temp.face.index[1]), &(temp.face.index[2]), &(temp.attrib1), &(temp.attrib2));
				faces.push_back(temp);
			}
		}

		lineNumber += 1;
	}

	return true;
}
