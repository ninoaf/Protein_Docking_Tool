/*
 * loadDat.cpp
 *
 *  Created on: May 26, 2010
 *      Author: ivan
 */

#include "mesh.h"
#include "../log/log.h"
#include <fstream>
#include <iostream>



int Mesh::loadDat(std::string path, bool centerMesh)
{
	unsigned int i=0;
	unsigned int numVertices=0, numIndex=0;
	FILE *fp=NULL;
	Vector3 tempVertex, tempNormal;
	Color tempColor;
	Face3 tempFace;

/*
	vertices_.clear();		/////	vertices_.init();
	normals_.clear();		/////	normals_.init();
	colors_.clear();		/////	colors_.init();
	textureCoords_.clear();	/////	textureCoords_.init();
	faces_.clear();			/////	faces_.init();

	arithmeticCenter_.init();
*/

	clear();

	fp = fopen(path.c_str(), "r");
	if (fp == NULL)
	{
		printf ("Could not open mesh %s!\n", path.c_str());
		return 1;
	}

    fscanf(fp, "%d", &numVertices);
    fscanf(fp, "%d", &numIndex);

    for (i=0; i<numVertices; i++)
    {
        fscanf (fp, "%lf %lf %lf %lf %lf %lf", &(tempVertex.x), &(tempVertex.y), &(tempVertex.z), &(tempNormal.x), &(tempNormal.y), &(tempNormal.z));
        tempColor.r = 0.8f;	tempColor.g = 0.8f;	tempColor.b = 0.8f;	tempColor.a = 1.0f;
//        tempTextureCoord
//        printf ("%f\t%f\t%f\n", tempVertex.x, tempVertex.y, tempVertex.z);
        tempNormal.normalize();
        vertices_.push_back(tempVertex);
        normals_.push_back(tempNormal);
        colors_.push_back(tempColor);

        arithmeticCenter_.x += tempVertex.x;
        arithmeticCenter_.y += tempVertex.y;
        arithmeticCenter_.z += tempVertex.z;

        if (i == 0)
        {
        	boundsMin_.x = boundsMax_.x = tempVertex.x;
        	boundsMin_.y = boundsMax_.y = tempVertex.y;
        	boundsMin_.z = boundsMax_.z = tempVertex.z;
        }

        if (tempVertex.x < boundsMin_.x)	boundsMin_.x = tempVertex.x;
        if (tempVertex.y < boundsMin_.y)	boundsMin_.y = tempVertex.y;
        if (tempVertex.z < boundsMin_.z)	boundsMin_.z = tempVertex.z;

        if (tempVertex.x > boundsMax_.x)	boundsMax_.x = tempVertex.x;
        if (tempVertex.y > boundsMax_.y)	boundsMax_.y = tempVertex.y;
        if (tempVertex.z > boundsMax_.z)	boundsMax_.z = tempVertex.z;
    }

    for (i=0; i<numIndex; i++)
    {
        fscanf (fp, "%d %d %d", &(tempFace.index[0]), &(tempFace.index[1]), &(tempFace.index[2]));
        faces_.push_back(tempFace);
    }

    fclose (fp);

    arithmeticCenter_.x /= numVertices;
    arithmeticCenter_.y /= numVertices;
    arithmeticCenter_.z /= numVertices;

    if (centerMesh == true)
    {
    	center();
    }

    setMeshType("dat");
    setPath(path);

	return 0;
}
