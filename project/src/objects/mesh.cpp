/*
 * mesh.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: ivan
 */

#include "mesh.h"
#include "../log/log.h"
#include <fstream>
#include <iostream>



using namespace std;



Mesh::Mesh()
{
	init();
}

Mesh::~Mesh()
{
	clear();
}

void Mesh::init()
{
	vertices_.clear();
	normals_.clear();
	colors_.clear();
	textureCoords_.clear();
	faces_.clear();
	msVertexInfo_.clear();
	msFaceInfo_.clear();
	arithmeticCenter_.init();
	centered_ = false;
	numVertices_ = 0;

	msNumSpheres_ = 0;
	msDensity_ = 0.0f;
	msProbeRadius_ = 0.0f;

	setName("DefaultMesh");

	meshType_ = "";
    setAutoIsoValue(true);
    setGridIsoValue(0.0f);
}

void Mesh::clear()
{
	vertices_.clear();
	normals_.clear();
	colors_.clear();
	textureCoords_.clear();
	faces_.clear();
	msVertexInfo_.clear();
	msFaceInfo_.clear();
	arithmeticCenter_.init();
}

vector<Vector3>& Mesh::getVertices()
{
	return vertices_;
}

vector<Vector3>& Mesh::getNormals()
{
	return normals_;
}

vector<Color>& Mesh::getColors()
{
	return colors_;
}

vector<TextureCoord2>& Mesh::getTextureCoords()
{
	return textureCoords_;
}

vector<Face3>& Mesh::getFaces()
{
	return faces_;
}

void Mesh::autoScale(double maxSize)
{
	unsigned int i=0;
	double maxDistance=0.0f;

	autoScale_ = maxSize;

	findCenter();

	if (maxSize == 0.0f)
		return;

	maxDistance = fabs(boundsMax_.x);
	if (fabs(boundsMax_.y) > maxDistance) maxDistance = fabs(boundsMax_.y);
	if (fabs(boundsMax_.z) > maxDistance) maxDistance = fabs(boundsMax_.z);

	if (fabs(boundsMin_.x) > maxDistance) maxDistance = fabs(boundsMin_.x);
	if (fabs(boundsMin_.y) > maxDistance) maxDistance = fabs(boundsMin_.y);
	if (fabs(boundsMin_.z) > maxDistance) maxDistance = fabs(boundsMin_.z);

//	printf ("maxDistance = %lf\n", maxDistance);

	for (i=0; i<vertices_.size(); i++)
	{
//		printf ("%f\t%f\t%f\n", vertices_[i].x, vertices_[i].y, vertices_[i].z);
		vertices_[i].x = (vertices_[i].x / maxDistance) * maxSize;
		vertices_[i].y = (vertices_[i].y / maxDistance) * maxSize;
		vertices_[i].z = (vertices_[i].z / maxDistance) * maxSize;
//		printf ("%f\t%f\t%f\n", vertices_[i].x, vertices_[i].y, vertices_[i].z);

        if (i == 0)
        {
        	boundsMin_.x = boundsMax_.x = vertices_[i].x;
        	boundsMin_.y = boundsMax_.y = vertices_[i].y;
        	boundsMin_.z = boundsMax_.z = vertices_[i].z;
        }

        if (vertices_[i].x < boundsMin_.x)	boundsMin_.x = vertices_[i].x;
        if (vertices_[i].y < boundsMin_.y)	boundsMin_.y = vertices_[i].y;
        if (vertices_[i].z < boundsMin_.z)	boundsMin_.z = vertices_[i].z;

        if (vertices_[i].x > boundsMax_.x)	boundsMax_.x = vertices_[i].x;
        if (vertices_[i].y > boundsMax_.y)	boundsMax_.y = vertices_[i].y;
        if (vertices_[i].z > boundsMax_.z)	boundsMax_.z = vertices_[i].z;
	}
}

void Mesh::setName(std::string meshName)
{
	meshName_ = meshName;
}

std::string Mesh::getName()
{
	return meshName_;
}

void Mesh::findCenter()
{
	unsigned int i=0;

	boundsMin_.init();
	boundsMax_.init();

    for (i=0; i<vertices_.size(); i++)
    {
        arithmeticCenter_.x += vertices_[i].x;
        arithmeticCenter_.y += vertices_[i].y;
        arithmeticCenter_.z += vertices_[i].z;

        if (i == 0)
        {
        	boundsMin_.x = boundsMax_.x = vertices_[i].x;
        	boundsMin_.y = boundsMax_.y = vertices_[i].y;
        	boundsMin_.z = boundsMax_.z = vertices_[i].z;
        }

        if (vertices_[i].x < boundsMin_.x)	boundsMin_.x = vertices_[i].x;
        if (vertices_[i].y < boundsMin_.y)	boundsMin_.y = vertices_[i].y;
        if (vertices_[i].z < boundsMin_.z)	boundsMin_.z = vertices_[i].z;

        if (vertices_[i].x > boundsMax_.x)	boundsMax_.x = vertices_[i].x;
        if (vertices_[i].y > boundsMax_.y)	boundsMax_.y = vertices_[i].y;
        if (vertices_[i].z > boundsMax_.z)	boundsMax_.z = vertices_[i].z;
    }

    if (vertices_.size() > 0)
    {
    	arithmeticCenter_.x /= vertices_.size();
    	arithmeticCenter_.y /= vertices_.size();
    	arithmeticCenter_.z /= vertices_.size();
    }
}

int Mesh::center()
{
	arithmeticCenter_ = 0;

/*
	for (unsigned int i=0; i<vertices_.size(); i++)
	{
		arithmeticCenter_.x += vertices_[i].x;
		arithmeticCenter_.y += vertices_[i].y;
		arithmeticCenter_.z += vertices_[i].z;
	}

	if (vertices_.size() > 0)
	{
		arithmeticCenter_.x /= vertices_.size();
		arithmeticCenter_.y /= vertices_.size();
		arithmeticCenter_.z /= vertices_.size();
	}
*/

	findCenter();

//    printf ("x = %lf\ty = %lf\tz = %lf\n", arithmeticCenter_.x, arithmeticCenter_.y, arithmeticCenter_.z);

	for (unsigned int i=0; i<vertices_.size(); i++)
	{
		vertices_[i].x -= arithmeticCenter_.x;
		vertices_[i].y -= arithmeticCenter_.y;
		vertices_[i].z -= arithmeticCenter_.z;
	}

	boundsMin_.x -= arithmeticCenter_.x;	boundsMin_.y -= arithmeticCenter_.y;	boundsMin_.z -= arithmeticCenter_.z;
	boundsMax_.x -= arithmeticCenter_.x;	boundsMax_.y -= arithmeticCenter_.y;	boundsMax_.z -= arithmeticCenter_.z;

	arithmeticCenter_.x = arithmeticCenter_.y = arithmeticCenter_.z = 0.0f;

	centered_ = true;

	return 0;
}

bool Mesh::getCentered()
{
	return centered_;
}

std::string Mesh::getMeshType()
{
	return meshType_;
}

void Mesh::setMeshType(std::string meshType)
{
	meshType_ = meshType;
}

double Mesh::getAutoScale()
{
	return autoScale_;
}

void Mesh::setPath(std::string path)
{
	path_ = path;
}

std::string Mesh::getPath()
{
	return path_;
}

void Mesh::setAutoIsoValue(bool autoIsoValue)
{
	autoIsoValue_ = autoIsoValue;
}

bool Mesh::getAutoIsoValue()
{
	return autoIsoValue_;
}

void Mesh::setGridIsoValue(double isoValue)
{
	gridIsoValue_ = isoValue;
}

double Mesh::getGridIsoValue()
{
	return gridIsoValue_;
}
