/*
 * scenenode.h
 *
 *  Created on: Apr 4, 2010
 *      Author: ivan
 */

#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "../structures/vmolstructures.h"
#include "../pdbparser/pdbparser.h"
#include "../objects/mesh.h"
#include <GL/gl.h>




/*
enum NodeTypeEnum
{
	NOP,

	GEOMETRY,
	PDB,
	COLOR,
	TEXTURE,

	ROTATION_CARTHESIAN,
	ROTATION_EULER,
	TRANSLATION,

	SHADER_PIXEL,
	SHADER_VERTEX,
	SHADER_GEOMETRY,

	PROJECTION_MATRIX,
	MODELVIEW_MATRIX
};
*/

#define		VMOL_NOP						0
#define		VMOL_MESH						1
#define		VMOL_PDB						2
#define		VMOL_COLOR						3
#define		VMOL_TEXTURE					4

#define		VMOL_LOOK_AT					5
#define		VMOL_TRANSLATION				6
#define		VMOL_ROTATION_CARTHESIAN_X		7
#define		VMOL_ROTATION_CARTHESIAN_Y		8
#define		VMOL_ROTATION_CARTHESIAN_Z		9
#define		VMOL_ROTATION_EULER				10
#define		VMOL_SCALE						11

#define		VMOL_SHADER_PIXEL				12
#define		VMOL_SHADER_VERTEX				13
#define		VMOL_SHADER_GEOMETRY			14

#define		VMOL_PROJECTION_MATRIX			15
#define		VMOL_MODELVIEW_MATRIX			16

#define		VMOL_SCRIPT						17



// #define		VMOL_PDB_CALLOTE				16
// #define		VMOL_PDB
// Node mode registers:
#define VMOL_MODE_GEOMETRY					1<<0
#define VMOL_MODE_COLORS					1<<1
#define VMOL_MODE_NORMALS					1<<2
#define VMOL_MODE_TEXTURE_COORDS			1<<3

#define VMOL_MODE_TEXTURES					1<<4
#define VMOL_MODE_LIGHTING					1<<5
#define VMOL_MODE_WIREFRAME					1<<6
#define VMOL_MODE_TRANSPARENT				1<<7

#define VMOL_MODE_PDB_CALLOTE				1<<8
#define VMOL_MODE_PDB_STICKS				1<<9
#define VMOL_MODE_PDB_STICKS_BALLS			1<<10
#define VMOL_MODE_PDB_WIRE					1<<11

#define VMOL_MODE_PDB_COLOR_ATOM			1<<12
#define VMOL_MODE_PDB_COLOR_AMINO			1<<13
#define VMOL_MODE_PDB_COLOR_CHAIN			1<<14
#define VMOL_MODE_UNDEFINED1				1<<15

#define VMOL_MODE_OBJECT_CENTER				1<<16
#define VMOL_MODE_OBJECT_BOUNDS				1<<17
#define VMOL_MODE_UNDEFINED2				1<<18

#define VMOL_MODE_USE_DEFAULT				1<<19



// #define VMOL_MODE_PDB_SURFACE				1<<11
// #define VMOL_MODE_PDB_CALLOTE				1<<11



class VmolSceneNode
{
public:
	VmolSceneNode();
	~VmolSceneNode();

	void clear();

	void addChild(VmolSceneNode *newNode);
	VmolSceneNode* getChild(unsigned int i);
	std::vector<VmolSceneNode *>& getChildren();

	unsigned int getNodeType();
	unsigned long long int getNodeMode();
	static unsigned int getNodeTypeFromString(std::string nodeType);
	void setName(std::string nodeName);
	std::string getName();



	void initNode(unsigned int nodeType);

	// For ROTATION_*, TRANSLATION
	void setViewParameters(Vector3 *paramPosition, Vector3 *paramLookVector, Vector3 *paramUpVector);			// parameters for configuring the view on the scene
	void setTranslationParameters(Vector3 *paramTranslation);														// parameters for translation
	void setColorParameters(Color *color);														// parameters for color
	void setGlModeParameters(GLenum glMode);														// parameters for changing OpenGL mode
	void setPdbParameters(PdbFile *pdbData, Mesh *sphereMesh, Mesh *stickMesh, unsigned long long int *nodeMode);
	void setMeshParameters(Mesh *meshData, unsigned long long int *nodeMode);
	void setEulerRotationParameters(EulerVector3 *param);
	void setRotationAngleParameters(double *param);
	void setScaleParameters(Vector3 *paramScale);
	void setScriptParameters(std::string *scriptPath);

/*
	void getViewParameters(Vector3 &paramPosition, Vector3 &paramLookVector, Vector3 &paramUpVector);			// parameters for configuring the view on the scene
	void setTranslationParameters(Vector3 &paramTranslation);														// parameters for translation
	void setColorParameters(Color &color);														// parameters for color
	void setGlModeParameters(GLenum glMode);														// parameters for changing OpenGL mode
	void setPdbParameters(PdbFile *pdbData, Mesh *sphereMesh, Mesh *stickMesh, unsigned long long int nodeMode);
	void setMeshParameters(Mesh *meshData, unsigned long long int nodeMode);
	void setEulerVectorParameters(EulerVector3 &param);
	void setRotationAngleParameters(double &param);
	void setName(std::string nodeName);
*/

	int getViewParameters(Vector3 **paramPosition, Vector3 **paramLookVector, Vector3 **paramUpVector);
	int getTranslationParameters(Vector3 **paramTranslation);
	int getColorParameters(Color **color);
	int getGlModeParameters(GLenum *glMode);
	int getPdbParameters(PdbFile **pdbData, Mesh **sphereMesh, Mesh **stickMesh, unsigned long long int **nodeMode);
	int getMeshParameters(Mesh **meshData, unsigned long long int **nodeMode);
	int getEulerRotationParameters(EulerVector3 **param);
	int getRotationAngleParameters(double **param);
	int getScaleParameters(Vector3 **paramScale);
	int getScriptParameters(std::string **scriptPath);

	std::string getParentName();
	void setParentName(std::string parentName);

/*
	Vector3 getVectorParam();
	double getRotationAngleParam();
	EulerVector3 getEulerVectorParam();
	PdbFile* getPdbDataParam();
	Mesh *getSphereMeshParam();
	Mesh *getStickMeshParam();
	Mesh* getMeshParam();
	Color getColorParam();
	Vector3 getScale();

	Vector3 getLookPositionParam();
	Vector3 getLookVectorParam();
	Vector3 getLookUpVectorParam();
*/




private:
	unsigned int nodeType_;
	unsigned long long int *nodeModeParam_;
	std::vector<VmolSceneNode *> child_;

	PdbFile *pdbDataParam_;
	std::vector<Mesh *> meshParam_;
	std::vector<Vector3 *> vectorParam_;
	std::vector<EulerVector3 *> eulerVectorParam_;
	std::vector<double *> doubleParam_;
	Color *colorParam_;
	std::vector<std::string *> stringParam_;

	int glModeParam_;

	std::string parentName_;


//	double rotationAngleParam_;

	std::string name_;
};

#endif /* SCENENODE_H_ */
