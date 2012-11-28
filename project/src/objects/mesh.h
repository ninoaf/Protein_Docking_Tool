/*
 * mesh.h
 *
 *  Created on: Apr 5, 2010
 *      Author: ivan
 */

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include <math.h>
#include "../grid/grid.h"
#include "../structures/structures.h"
#include "../structures/vmolstructures.h"
#include <cstdlib>



class MsVertexInfo
{
public:
	unsigned long int d, atomNumber, probeRadius;

	MsVertexInfo()
	{
		d = atomNumber = probeRadius = 0;
	}
};

class MsFaceInfo
{
public:
	long int param[2];

	MsFaceInfo()
	{
		param[0] = param[1] = 0;
	}
};



class Mesh
{
public:
	Mesh();
	~Mesh();

	void init();
	void clear();

	int loadDat(std::string path, bool centerMesh=true);
	int loadGrid(std::string path, bool centerMesh=false, bool automaticIsosurface=true, double isoValue=0.8f);
//	int loadMS(std::string pathVertices, std::string pathIndices, bool centerMesh=false);
	int loadMS(std::string path, bool centerMesh=false);

	void setName(std::string meshName);
	std::string getName();
	void setPath(std::string path);
	std::string getPath();
	void setMeshType(std::string meshType);
	std::string getMeshType();

	std::vector<Vector3>& getVertices();
	std::vector<Vector3>& getNormals();
	std::vector<Color>& getColors();
	std::vector<TextureCoord2>& getTextureCoords();
	std::vector<Face3>& getFaces();
	int center();
	bool getCentered();
	void findCenter();

	void autoScale(double maxSize);
	double getAutoScale();

	void setAutoIsoValue(bool autoIsoValue);
	bool getAutoIsoValue();
	void setGridIsoValue(double isoValue);
	double getGridIsoValue();

private:
	std::string meshName_;

	std::vector<Vector3> vertices_;
	std::vector<Vector3> normals_;
	std::vector<Color> colors_;
	std::vector<TextureCoord2> textureCoords_;
	std::vector<Face3> faces_;
	std::vector<MsVertexInfo> msVertexInfo_;
	std::vector<MsFaceInfo> msFaceInfo_;

	unsigned int numVertices_;
	Vector3 boundsMin_;
	Vector3 boundsMax_;
	Vector3 arithmeticCenter_;
	bool centered_;

	unsigned long int msNumSpheres_;
	double msDensity_;
	double msProbeRadius_;

	bool autoIsoValue_;
	double gridIsoValue_;

	std::string meshType_;
	std::string path_;
	double autoScale_;



	double fGetOffset(double fValue1, double fValue2, double fValueDesired);
	void marchingCubes(Grid *grid, double isoSurface);
	void marchingCube(Grid *grid, unsigned long int indexI, unsigned long int indexJ, unsigned long int indexK, double isoValue);
	double calculateIsovalue(Grid *grid);
};

#endif /* MESH_H_ */
