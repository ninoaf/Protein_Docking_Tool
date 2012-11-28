/*
 * loadMs.cpp
 *
 *  Created on: May 26, 2010
 *      Author: ivan
 */

#include "mesh.h"
#include "../log/log.h"
#include <fstream>
#include <iostream>



// int Mesh::loadMS(string pathVertices, string pathFaces, bool centerMesh)
int Mesh::loadMS(string path, bool centerMesh)
{
	unsigned int lineNumber=0;
	bool headerLine=true;
	string buffer;
	string pathVertices, pathFaces;
	Vector3 newVertex;
	Vector3 newNormal;
	Face3 newFace;
	MsVertexInfo newVertexInfo;
	MsFaceInfo newFaceInfo;
	Color newColor;
	TextureCoord2 newTextureCoord;

	pathVertices = path + ".vert";
	pathFaces = path + ".face";

	ifstream inputVertices(pathVertices.c_str());
	ifstream inputFaces(pathFaces.c_str());

//	system("pwd");
//	printf ("pathVertices = %s\n", path.c_str());

	if (inputVertices == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", pathVertices.c_str());
		return 1;
	}

	if (inputFaces == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", pathFaces.c_str());
		return 1;
	}



	clear();

	newColor.r = newColor.g = newColor.b = newColor. a = 255;
	newTextureCoord.u = newTextureCoord.v = 0.0f;

	headerLine = true;
	while (getline(inputVertices, buffer))
	{
		if (buffer[0] != '#')
		{
			if (headerLine == true)
			{
				sscanf(buffer.c_str(), "%d %d %lf %lf", &numVertices_, &msNumSpheres_, &msDensity_, &msProbeRadius_);
				headerLine = false;
			}
			else
			{
				sscanf(buffer.c_str(), "%lf %lf %lf %lf %lf %lf %ld %ld %ld",
										&(newVertex.x), &(newVertex.y), &(newVertex.z),
										&(newNormal.x), &(newNormal.y), &(newNormal.z),
										&(newVertexInfo.d), &(newVertexInfo.atomNumber), &(newVertexInfo.probeRadius));

				vertices_.push_back(newVertex);
				normals_.push_back(newNormal);
				colors_.push_back(newColor);
				textureCoords_.push_back(newTextureCoord);
				msVertexInfo_.push_back(newVertexInfo);
			}
		}

		lineNumber += 1;
	}

	headerLine = true;
	while (getline(inputFaces, buffer))
	{
		if (buffer[0] != '#')
		{
			if (headerLine == true)
			{
				sscanf(buffer.c_str(), "%d %d %lf %lf", &numVertices_, &msNumSpheres_, &msDensity_, &msProbeRadius_);
				headerLine = false;
			}
			else
			{
				sscanf(buffer.c_str(), "%u %u %u %d %d",
										&(newFace.index[0]), &(newFace.index[1]), &(newFace.index[2]),
										&(newFaceInfo.param[0]), &(newFaceInfo.param[1]));

				newFace.index[0] -= 1;
				newFace.index[1] -= 1;
				newFace.index[2] -= 1;

				faces_.push_back(newFace);
				msFaceInfo_.push_back(newFaceInfo);
			}
		}

		lineNumber += 1;
	}

	findCenter();

    if (centerMesh == true)
    {
    	center();
    }

    setMeshType("ms");
    setPath(path);

//	printf ("numVertices = %d\n", vertices_.size());
//	printf ("numFaces = %d\n", faces_.size());

	return 0;
}
