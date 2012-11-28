/*
 * scene.h
 *
 *  Created on: Mar 12, 2010
 *      Author: ivan
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>
#include <vector>

#include "../structures/vmolstructures.h"
#include "../pdbparser/pdbparser.h"
#include "scenenode.h"
#include "../objects/mesh.h"



class VmolScene
{
public:
	VmolScene();
	~VmolScene();

//	void initScene(VmolSceneNode *rootNode);
	static VmolScene* getInstance();

	void renderScene(VmolSceneNode *rootNode);
	int renderNode(VmolSceneNode *node);
	int renderMesh(Mesh *meshData, unsigned long long int nodeMode);
	int renderMeshVA(Mesh *meshData, unsigned long long int nodeMode);
	int renderMeshTriangle(Mesh *meshData, unsigned long long int nodeMode);
	int renderPdb(PdbFile *pdbData, Mesh *sphereMesh_, Mesh *stickMesh_, unsigned long long int nodeMode);

private:
	static VmolScene* singleInstance_;

	void renderSceneRecursion(VmolSceneNode *currentNode, int currentLevel);
};

#endif /* SCENE_H_ */
