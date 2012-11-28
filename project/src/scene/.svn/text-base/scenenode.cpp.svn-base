/*
 * scenenode.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: ivan
 */

#include "scenenode.h"



VmolSceneNode::VmolSceneNode()
{
	nodeModeParam_ = 0x0000000000000000;
}

VmolSceneNode::~VmolSceneNode()
{

}

void VmolSceneNode::clear()
{
	pdbDataParam_ = NULL;
	meshParam_.clear();
	vectorParam_.clear();
	eulerVectorParam_.clear();
	doubleParam_.clear();
	colorParam_ = NULL;
	stringParam_.clear();

	nodeType_ = VMOL_NOP;
}

void VmolSceneNode::initNode(unsigned int nodeType)
{
	nodeType_ = nodeType;
	setName("DefaultNode");
}

unsigned int VmolSceneNode::getNodeType()
{
	return nodeType_;
}

unsigned long long int VmolSceneNode::getNodeMode()
{
	return *nodeModeParam_;
}

void VmolSceneNode::addChild(VmolSceneNode *newNode)
{
	child_.push_back(newNode);
}

VmolSceneNode* VmolSceneNode::getChild(unsigned int i)
{
	return child_[i];
}

std::vector<VmolSceneNode *>& VmolSceneNode::getChildren()
{
	return child_;
}



void VmolSceneNode::setViewParameters(Vector3 *paramPosition, Vector3 *paramLookVector, Vector3 *paramUpVector)
{
	vectorParam_.clear();
	vectorParam_.push_back(paramPosition);
	vectorParam_.push_back(paramLookVector);
	vectorParam_.push_back(paramUpVector);
}

void VmolSceneNode::setTranslationParameters(Vector3 *paramTranslation)
{
	vectorParam_.clear();
	vectorParam_.push_back(paramTranslation);
}

void VmolSceneNode::setColorParameters(Color *color)
{
	colorParam_ = color;
}

void VmolSceneNode::setGlModeParameters(GLenum glMode)
{
	glModeParam_ = glMode;
}

void VmolSceneNode::setPdbParameters(PdbFile *pdbData, Mesh *sphereMesh, Mesh *stickMesh, unsigned long long int *nodeMode)
{
	pdbDataParam_ = pdbData;

	meshParam_.clear();
	meshParam_.push_back(sphereMesh);
	meshParam_.push_back(stickMesh);

	nodeModeParam_ = nodeMode;
}

void VmolSceneNode::setMeshParameters(Mesh *meshData, unsigned long long int *nodeMode)
{
	meshParam_.clear();
	meshParam_.push_back(meshData);

	nodeModeParam_ = nodeMode;
}

void VmolSceneNode::setEulerRotationParameters(EulerVector3 *param)
{
	eulerVectorParam_.clear();
	eulerVectorParam_.push_back(param);
}

void VmolSceneNode::setRotationAngleParameters(double *param)
{
	doubleParam_.clear();
	doubleParam_.push_back(param);
}

void VmolSceneNode::setScaleParameters(Vector3 *paramScale)
{
	vectorParam_.clear();
	vectorParam_.push_back(paramScale);
}

void VmolSceneNode::setScriptParameters(string *scriptPath)
{
	stringParam_.clear();
	stringParam_.push_back(scriptPath);
}



int VmolSceneNode::getViewParameters(Vector3 **paramPosition, Vector3 **paramLookVector, Vector3 **paramUpVector)
{
	if (vectorParam_.size() < 3)
		return 1;

	*paramPosition = vectorParam_[0];
	*paramLookVector = vectorParam_[1];
	*paramUpVector = vectorParam_[2];

	return 0;
}

int VmolSceneNode::getTranslationParameters(Vector3 **paramTranslation)
{
	if (vectorParam_.size() < 1)
		return 1;

	*paramTranslation = vectorParam_[0];

	return 0;
}

int VmolSceneNode::getColorParameters(Color **color)
{
	*color = colorParam_;

	return 0;
}

int VmolSceneNode::getGlModeParameters(GLenum *glMode)
{
	*glMode = glModeParam_;

	return 0;
}

int VmolSceneNode::getPdbParameters(PdbFile **pdbData, Mesh **sphereMesh, Mesh **stickMesh, unsigned long long int **nodeMode)
{
	if (meshParam_.size() < 2)
		return 1;

	*pdbData = pdbDataParam_;
	*sphereMesh = meshParam_[0];
	*stickMesh = meshParam_[1];

	*nodeMode = nodeModeParam_;

	return 0;
}

int VmolSceneNode::getMeshParameters(Mesh **meshData, unsigned long long int **nodeMode)
{
	if (meshParam_.size() < 1)
		return 1;

	*meshData = meshParam_[0];

	*nodeMode = nodeModeParam_;

	return 0;
}

int VmolSceneNode::getEulerRotationParameters(EulerVector3 **param)
{
	if (eulerVectorParam_.size() < 1)
		return 1;

	*param = eulerVectorParam_[0];

	return 0;
}

int VmolSceneNode::getRotationAngleParameters(double **param)
{
	if (doubleParam_.size() < 1)
		return 1;

	*param = doubleParam_[0];

	return 0;
}

int VmolSceneNode::getScaleParameters(Vector3 **paramScale)
{
	if (vectorParam_.size() < 1)
		return 1;

	*paramScale = vectorParam_[0];

	return 0;
}



unsigned int VmolSceneNode::getNodeTypeFromString(string nodeType)
{
	if (nodeType == "nop")	return VMOL_NOP;
	else if (nodeType == "mesh") return VMOL_MESH;
	else if (nodeType == "pdb") return VMOL_PDB;
	else if (nodeType == "color") return VMOL_COLOR;
	else if (nodeType == "texture") return VMOL_TEXTURE;
	else if (nodeType == "lookat") return VMOL_LOOK_AT;
	else if (nodeType == "translation") return VMOL_TRANSLATION;
	else if (nodeType == "rotationx") return VMOL_ROTATION_CARTHESIAN_X;
	else if (nodeType == "rotationy") return VMOL_ROTATION_CARTHESIAN_Y;
	else if (nodeType == "rotationz") return VMOL_ROTATION_CARTHESIAN_Z;
	else if (nodeType == "rotationeuler") return VMOL_ROTATION_EULER;
	else if (nodeType == "scale")	return VMOL_SCALE;
	else if (nodeType == "shaderpixel") return VMOL_SHADER_PIXEL;
	else if (nodeType == "shadervertex") return VMOL_SHADER_VERTEX;
	else if (nodeType == "shadergeometry") return VMOL_SHADER_GEOMETRY;
	else if (nodeType == "projectionmatrix") return VMOL_PROJECTION_MATRIX;
	else if (nodeType == "modelviewmatrix") return VMOL_MODELVIEW_MATRIX;
	else if (nodeType == "script")	return VMOL_SCRIPT;

	return VMOL_NOP;
}

void VmolSceneNode::setName(string nodeName)
{
	name_ = nodeName;
}

string VmolSceneNode::getName()
{
	return name_;
}

int VmolSceneNode::getScriptParameters(string **scriptPath)
{
	if (stringParam_.size() < 1)
		return 1;

	*scriptPath = stringParam_[0];

//	printf ("path1 = %s\tname = %s\tparam = %s\tsize = %d\n", (*scriptPath)->c_str(), getName().c_str(), stringParam_[0]->c_str(), stringParam_.size());

	return 0;
}

std::string VmolSceneNode::getParentName()
{
	return parentName_;
}

void VmolSceneNode::setParentName(std::string parentName)
{
	parentName_ = parentName;
}
