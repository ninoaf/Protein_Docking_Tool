/*
 * msmswrapper.h
 *
 *  Created on: Nov 4, 2009
 *      Author: ivan
 */

#ifndef MSMSWRAPPER_H_
#define MSMSWRAPPER_H_

#include "../structures/structures.h"
#include <vector>
#include <string>
#include <fstream>



class MSMSWrapper
{
public:
	unsigned int numCoords;
	unsigned int numSpheres;
	unsigned int numFaces;
	double density;
	double probeRadius;

	std::vector<MSMSCoord> vertices;
	std::vector<MSMSFace> faces;



	MSMSWrapper();
	~MSMSWrapper();

	void init();
	void clear();
	bool load(std::string filePath);
	bool importCoords(std::string filePath);
	bool importFaces(std::string filePath);
};

#endif /* MSMSWRAPPER_H_ */
