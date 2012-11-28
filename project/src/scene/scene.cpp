
/*
 * scene.cpp
 *
 *  Created on: Mar 12, 2010
 *      Author: ivan
 */

#include "scene.h"
#include "scenenode.h"
#include "../log/log.h"
#include "../command/vmolcommand.h"

VmolScene* VmolScene::singleInstance_=NULL;



VmolScene::VmolScene()
{

}

VmolScene::~VmolScene()
{

}

VmolScene* VmolScene::getInstance()
{
	if (singleInstance_ == NULL)
	{
		singleInstance_ = new VmolScene();
		return singleInstance_;
	}

	return singleInstance_;
}

void VmolScene::renderScene(VmolSceneNode *rootNode)
{
	renderSceneRecursion(rootNode, 0);
}

void VmolScene::renderSceneRecursion(VmolSceneNode *currentNode, int currentLevel)
{
	GLdouble matrix[16];
//	if (currentLevel == 1)
//		glLoadIdentity();

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	glPushMatrix();
	glLoadMatrixd(matrix);

	renderNode(currentNode);

	for (unsigned int i=0; i<currentNode->getChildren().size(); i++)
	{
		renderSceneRecursion(currentNode->getChildren()[i], (currentLevel+1));
	}

	glPopMatrix();
}

int VmolScene::renderNode(VmolSceneNode *node)
{
	if (node->getNodeType() == VMOL_TRANSLATION)
	{
		Vector3 *translation;
//		translation = node->getVectorParam();
		if (node->getTranslationParameters(&translation))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		glTranslatef(translation->x, translation->y, translation->z);
	}
	else if (node->getNodeType() == VMOL_ROTATION_CARTHESIAN_X)
	{
		double *rotationAngle;

		if (node->getRotationAngleParameters(&rotationAngle))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		glRotatef(*rotationAngle, 1.0f, 0.0f, 0.0f);
	}
	else if (node->getNodeType() == VMOL_ROTATION_CARTHESIAN_Y)
	{
		double *rotationAngle;

		if (node->getRotationAngleParameters(&rotationAngle))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

//		printf ("%s rotationAngle = %lf\n", node->getName().c_str(), rotationAngle);

		glRotatef(*rotationAngle, 0.0f, 1.0f, 0.0f);
	}
	else if (node->getNodeType() == VMOL_ROTATION_CARTHESIAN_Z)
	{
		double *rotationAngle;

		if (node->getRotationAngleParameters(&rotationAngle))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		glRotatef(*rotationAngle, 0.0f, 0.0f, 1.0f);
	}
	else if (node->getNodeType() == VMOL_ROTATION_EULER)
	{
		EulerVector3 *rotation;
//		rotation = node->getEulerVectorParam();
		if (node->getEulerRotationParameters(&rotation))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		glRotatef(rotation->alpha, 0.0f, 0.0f, 1.0f);
		glRotatef(rotation->beta, 0.0f, 1.0f, 0.0f);
		glRotatef(rotation->gamma, 0.0f, 0.0f, 1.0f);

//		printf ("alpha = %.2lf\tbeta = %.2lf\tgamma = %.2lf\n", rotation.alpha, rotation.beta, rotation.gamma);
	}
	else if (node->getNodeType() == VMOL_COLOR)
	{
		Color color;
		Color *colorPointer;

//		color = node->getColorParam();
		if (node->getColorParameters(&colorPointer))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		color = *colorPointer;
		glColor4ub(color.r, color.g, color.b, color.a);
	}
	else if (node->getNodeType() == VMOL_SCALE)
	{
		Vector3 *scale;

//		scale = node->getScale();
		if (node->getScaleParameters(&scale))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		glScalef(scale->x, scale->y, scale->z);
	}

	else if (node->getNodeType() == VMOL_TEXTURE)
	{
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture()
	}

	else if (node->getNodeType() == VMOL_MESH)
	{
//		renderPdb(node->getPdbDataParam());
		Mesh *meshParam;
		unsigned long long int *nodeModeParam;

		if (node->getMeshParameters(&meshParam, &nodeModeParam))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		renderMesh(meshParam, *nodeModeParam);
	}
	else if (node->getNodeType() == VMOL_PDB)
	{
		PdbFile *pdbParam;
		Mesh *meshSphereParam, *meshStickParam;
		unsigned long long int *nodeModeParam;

		if (node->getPdbParameters(&pdbParam, &meshSphereParam, &meshStickParam, &nodeModeParam))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

//		printf ("name: %s\n", pdbParam->getName().c_str());

		renderPdb(pdbParam, meshSphereParam, meshStickParam, *nodeModeParam);

//		printf ("Rendered node VMOL_PDB!\n");

	}
	else if (node->getNodeType() == VMOL_LOOK_AT)
	{
		Vector3 *paramPosition, *paramLookVector, *paramUpVector;

		if (node->getViewParameters(&paramPosition, &paramLookVector, &paramUpVector))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

		gluLookAt(paramPosition->x, paramPosition->y, paramPosition->z, paramLookVector->x, paramLookVector->y, paramLookVector->z, paramUpVector->x, paramUpVector->y, paramUpVector->z);
	}
	else if (node->getNodeType() == VMOL_SCRIPT)
	{
		string *scriptPath;

		if (node->getScriptParameters(&scriptPath))
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Can not execute node %s, type %d!", node->getName().c_str(), node->getNodeType());
			return 1;
		}

//		printf ("path = %s\n", scriptPath->c_str());

		return VmolCommand::getInstance()->loadScript(*scriptPath, false);
	}
	else if (node->getNodeType() == VMOL_NOP)
	{
		// no operation (i.e. root node)
	}

	return 0;
}

int VmolScene::renderMesh(Mesh *meshData, unsigned long long int nodeMode)
{
	return renderMeshVA(meshData, nodeMode);
}

int VmolScene::renderMeshVA(Mesh *meshData, unsigned long long int nodeMode)
{
//    if (vertices==NULL || colors==NULL || index==NULL)
//        return false;
	if (meshData->getVertices().size() == 0)
		return 1;



	if ((nodeMode & VMOL_MODE_WIREFRAME) != 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		printf ("Tu sam 1!\n");
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		printf ("Tu sam 2!\n");
	}

//	if (meshData->getVertices().size()!=0 && (nodeMode & VMOL_MODE_GEOMETRY)!=0)
	if ((nodeMode & VMOL_MODE_GEOMETRY) != 0)
	{
		glVertexPointer (3, GL_DOUBLE, 0, &(meshData->getVertices()[0]));
		glEnableClientState (GL_VERTEX_ARRAY);
	}

	if (meshData->getNormals().size()!=0 && (nodeMode & VMOL_MODE_NORMALS)!=0)
	{
		glEnableClientState (GL_NORMAL_ARRAY);
//		glNormalPointer (GL_DOUBLE, 0, &(meshData->getNormals()[0]));
		glNormalPointer (GL_DOUBLE, 0, &(meshData->getNormals()[0]));
//		printf ("%f\t%f\t%f\n", meshData->getNormals().elements[0].x, meshData->getNormals().elements[0].y, meshData->getNormals().elements[0].z);
//		printf ("%f\t%f\t%f\n", meshData->getNormals().elements[1].x, meshData->getNormals().elements[1].y, meshData->getNormals().elements[1].z);
	}

	if (meshData->getColors().size()!=0 && (nodeMode & VMOL_MODE_COLORS)!=0)
	{
		glEnableClientState (GL_COLOR_ARRAY);
		glColorPointer (4, GL_UNSIGNED_BYTE, 0, &(meshData->getColors()[0]));
	}

//	glEnableClientState (GL_TEXTURE_ARRAY);

//	printf ("Tu sam!\n");

    glDrawElements (GL_TRIANGLES, meshData->getFaces().size()*3, GL_UNSIGNED_INT, &(meshData->getFaces()[0].index[0]));

	glDisableClientState (GL_VERTEX_ARRAY);

	if (meshData->getNormals().size() != 0)
		glDisableClientState (GL_NORMAL_ARRAY);
	if (meshData->getColors().size() != 0)
		glDisableClientState (GL_COLOR_ARRAY);

	return 0;
}

int VmolScene::renderMeshTriangle(Mesh *meshData, unsigned long long int nodeMode)
{
	if (meshData->getVertices().size() == 0)
		return 1;

	glBegin(GL_TRIANGLES);
		for (unsigned int i=0; i<meshData->getFaces().size(); i++)
		{
			if (meshData->getColors().size()!=0 && (nodeMode & VMOL_MODE_COLORS)!=0)
				glColor4f(meshData->getColors()[meshData->getFaces()[i].index[0]].r, meshData->getColors()[meshData->getFaces()[i].index[0]].g, meshData->getColors()[meshData->getFaces()[i].index[0]].b, meshData->getColors()[meshData->getFaces()[i].index[0]].a);
			if (meshData->getNormals().size()!=0 && (nodeMode & VMOL_MODE_NORMALS)!=0)
				glNormal3f(meshData->getNormals()[meshData->getFaces()[i].index[0]].x, meshData->getNormals()[meshData->getFaces()[i].index[0]].y, meshData->getNormals()[meshData->getFaces()[i].index[0]].z);
			if ((nodeMode & VMOL_MODE_GEOMETRY) != 0)
				glVertex3f(meshData->getVertices()[meshData->getFaces()[i].index[0]].x, meshData->getVertices()[meshData->getFaces()[i].index[0]].y, meshData->getVertices()[meshData->getFaces()[i].index[0]].z);

			if (meshData->getColors().size()!=0 && (nodeMode & VMOL_MODE_COLORS)!=0)
				glColor4f(meshData->getColors()[meshData->getFaces()[i].index[1]].r, meshData->getColors()[meshData->getFaces()[i].index[1]].g, meshData->getColors()[meshData->getFaces()[i].index[1]].b, meshData->getColors()[meshData->getFaces()[i].index[1]].a);
			if (meshData->getNormals().size()!=0 && (nodeMode & VMOL_MODE_NORMALS)!=0)
				glNormal3f(meshData->getNormals()[meshData->getFaces()[i].index[1]].x, meshData->getNormals()[meshData->getFaces()[i].index[1]].y, meshData->getNormals()[meshData->getFaces()[i].index[1]].z);
			if ((nodeMode & VMOL_MODE_GEOMETRY) != 0)
				glVertex3f(meshData->getVertices()[meshData->getFaces()[i].index[1]].x, meshData->getVertices()[meshData->getFaces()[i].index[1]].y, meshData->getVertices()[meshData->getFaces()[i].index[1]].z);

			if (meshData->getColors().size()!=0 && (nodeMode & VMOL_MODE_COLORS)!=0)
				glColor4f(meshData->getColors()[meshData->getFaces()[i].index[2]].r, meshData->getColors()[meshData->getFaces()[i].index[2]].g, meshData->getColors()[meshData->getFaces()[i].index[2]].b, meshData->getColors()[meshData->getFaces()[i].index[1]].a);
			if (meshData->getNormals().size()!=0 && (nodeMode & VMOL_MODE_NORMALS)!=0)
				glNormal3f(meshData->getNormals()[meshData->getFaces()[i].index[2]].x, meshData->getNormals()[meshData->getFaces()[i].index[2]].y, meshData->getNormals()[meshData->getFaces()[i].index[2]].z);
			if ((nodeMode & VMOL_MODE_GEOMETRY) != 0)
				glVertex3f(meshData->getVertices()[meshData->getFaces()[i].index[2]].x, meshData->getVertices()[meshData->getFaces()[i].index[2]].y, meshData->getVertices()[meshData->getFaces()[i].index[2]].z);
		}
	glEnd();

	return 0;
}

int VmolScene::renderPdb(PdbFile *pdbData, Mesh *sphereMesh, Mesh *stickMesh, unsigned long long int nodeMode)
{
	unsigned int i=0, j=0;
	double vectorAngle=0.0f, stickSize=0.0f;
	unsigned long long int selectedModel=0, mask=0;
	Model *currentModel=NULL;
	AtomPdb *currentAtom=NULL;
	AtomPdb *firstBondAtom=NULL;
	AtomPdb *secondBondAtom=NULL;
	AtomPdb centerBond;
	Color atomColor;
	Color *colorPointer;
	Color *firstBondColor;
	Color *secondBondColor;
	Vector3 vector1, vector2, rotationVector;
	Vector3 firstBondCenter, secondBondCenter;

	if (pdbData == NULL)
	{
		printf ("Invalid PDB data for rendering!\n");
		return 0;
	}




	mask = 65535;
	selectedModel = nodeMode >> 48;
	selectedModel = selectedModel & mask;

	for (i=0; i<pdbData->getModels().size(); i++)
	{
//		if (((unsigned int) selectedModel)==(i+1) || ((unsigned int) selectedModel)==65535)
		{

			currentModel = &(pdbData->getModels()[i]);

			if ((nodeMode & VMOL_MODE_PDB_CALLOTE) != 0)
			{
				if (sphereMesh == NULL)
				{
					printf ("Invalid mesh data for rendering!\n");
					return 0;
				}

				for (j=0; j<currentModel->getAtomIndex().size(); j++)
				{
					currentAtom = &(currentModel->getAtom(j));
					colorPointer = NULL;
					if ((nodeMode & VMOL_MODE_PDB_COLOR_ATOM) != 0)
					{
						colorPointer = currentAtom->atomColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_AMINO) != 0)
					{
						colorPointer = currentAtom->aminoColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_CHAIN) != 0)
					{
						colorPointer = currentAtom->chainColorPointer;
					}

	//				atomColor = findAtomColor(currentModel->getAtoms()[j]);
					glPushMatrix();

	//				glColor4ub(atomColor.r, atomColor.g, atomColor.b, atomColor.a);
						if (colorPointer != NULL)
							glColor4ub(colorPointer->r, colorPointer->g, colorPointer->b, colorPointer->a);
						glTranslatef(currentAtom->x, currentAtom->y, currentAtom->z);
						glScalef(currentAtom->r, currentAtom->r, currentAtom->r);

						renderMesh(sphereMesh, nodeMode);
					glPopMatrix();
				}
			}

			if ((nodeMode & VMOL_MODE_PDB_WIRE) != 0)
			{
				glPushMatrix();
				glBegin(GL_LINES);
				for (j=0; j<currentModel->getBonds().size(); j++)
				{
					firstBondAtom = (currentModel->getBonds()[j].atom1);
					secondBondAtom = (currentModel->getBonds()[j].atom2);
					centerBond.x = (firstBondAtom->x + secondBondAtom->x) / 2.0f;
					centerBond.y = (firstBondAtom->y + secondBondAtom->y) / 2.0f;
					centerBond.z = (firstBondAtom->z + secondBondAtom->z) / 2.0f;
					firstBondColor = NULL;
					secondBondColor = NULL;

					if ((nodeMode & VMOL_MODE_PDB_COLOR_ATOM) != 0)
					{
						firstBondColor = firstBondAtom->atomColorPointer;
						secondBondColor = secondBondAtom->atomColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_AMINO) != 0)
					{
						firstBondColor = firstBondAtom->aminoColorPointer;
						secondBondColor = secondBondAtom->aminoColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_CHAIN) != 0)
					{
						firstBondColor = firstBondAtom->chainColorPointer;
						secondBondColor = secondBondAtom->chainColorPointer;
					}

					if (firstBondColor != NULL)
						glColor4ub(firstBondColor->r, firstBondColor->g, firstBondColor->b, firstBondColor->a);
					glVertex3f(firstBondAtom->x, firstBondAtom->y, firstBondAtom->z);
					glVertex3f(centerBond.x, centerBond.y, centerBond.z);

					if (secondBondColor != NULL)
						glColor4ub(secondBondColor->r, secondBondColor->g, secondBondColor->b, secondBondColor->a);
					glVertex3f(centerBond.x, centerBond.y, centerBond.z);
					glVertex3f(secondBondAtom->x, secondBondAtom->y, secondBondAtom->z);
				}
				glEnd();
				glPopMatrix();
			}

			if ((nodeMode & VMOL_MODE_PDB_STICKS)!=0 || (nodeMode & VMOL_MODE_PDB_STICKS_BALLS)!=0)
			{
				if (sphereMesh==NULL || stickMesh==NULL)
				{
					printf ("Invalid mesh data for rendering!\n");
					return 0;
				}

	//			printf ("getBonds().size() = %d\n", currentModel->getBonds().size());

				// first draw the sticks
				for (j=0; j<currentModel->getBonds().size(); j++)
				{
					firstBondAtom = (currentModel->getBonds()[j].atom1);
					secondBondAtom = (currentModel->getBonds()[j].atom2);
					centerBond.x = (firstBondAtom->x + secondBondAtom->x) / 2.0f;
					centerBond.y = (firstBondAtom->y + secondBondAtom->y) / 2.0f;
					centerBond.z = (firstBondAtom->z + secondBondAtom->z) / 2.0f;
					firstBondColor = NULL;
					secondBondColor = NULL;

					if ((nodeMode & VMOL_MODE_PDB_COLOR_ATOM) != 0)
					{
						firstBondColor = firstBondAtom->atomColorPointer;
						secondBondColor = secondBondAtom->atomColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_AMINO) != 0)
					{
						firstBondColor = firstBondAtom->aminoColorPointer;
						secondBondColor = secondBondAtom->aminoColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_CHAIN) != 0)
					{
						firstBondColor = firstBondAtom->chainColorPointer;
						secondBondColor = secondBondAtom->chainColorPointer;
					}

					vector1.x = 0.0f;   vector1.y = 1.0f;   vector1.z = 0.0f;
					vector2.x = secondBondAtom->x - firstBondAtom->x;	vector2.y = secondBondAtom->y - firstBondAtom->y;	vector2.z = secondBondAtom->z - firstBondAtom->z;

					vectorAngle = (vector1.dotProduct(vector2)) / (vector1.magnitude() * vector2.magnitude());
					vectorAngle = acos(vectorAngle) * 180.0f / 3.14159f;

					rotationVector = vector1.crossProduct(vector2);
					rotationVector.normalize();

					stickSize = sqrt((double) (firstBondAtom->x-secondBondAtom->x)*(firstBondAtom->x-secondBondAtom->x) + (firstBondAtom->y-secondBondAtom->y)*(firstBondAtom->y-secondBondAtom->y) + (firstBondAtom->z-secondBondAtom->z)*(firstBondAtom->z-secondBondAtom->z));
	//                stickSize = stickSize / (4.0f);			// distance between an atom and center between two atoms (half the distance, but a little bit larger, just so that there is no hole between two rendered sticks)
					stickSize = stickSize / (4.0f);			// the distance is divided by four, because the stick model is centered around origin (0.0f, 0.0f, 0.0f), so its total size is half the distance (quarter the distance from the origin alongside the axis)

					firstBondCenter.x = firstBondAtom->x + (secondBondAtom->x - firstBondAtom->x) / 4;
					firstBondCenter.y = firstBondAtom->y + (secondBondAtom->y - firstBondAtom->y) / 4;
					firstBondCenter.z = firstBondAtom->z + (secondBondAtom->z - firstBondAtom->z) / 4;

					secondBondCenter.x = firstBondAtom->x + (secondBondAtom->x - firstBondAtom->x) * 3 / 4;
					secondBondCenter.y = firstBondAtom->y + (secondBondAtom->y - firstBondAtom->y) * 3 / 4;
					secondBondCenter.z = firstBondAtom->z + (secondBondAtom->z - firstBondAtom->z) * 3 / 4;

	// printf ("Tu sam 1!\n");

					glPushMatrix();
						if (firstBondColor != NULL)
							glColor4ub(firstBondColor->r, firstBondColor->g, firstBondColor->b, firstBondColor->a);
	//                    glTranslatef(firstBondAtom->x, firstBondAtom->y, firstBondAtom->z);
						glTranslatef(firstBondCenter.x, firstBondCenter.y, firstBondCenter.z);
						glRotated(vectorAngle, rotationVector.x, rotationVector.y, rotationVector.z);
						glScaled(1.0f, stickSize, 1.0f);

						renderMesh(stickMesh, nodeMode);
					glPopMatrix();

	//				printf ("Tu sam 2!\n");

					glPushMatrix();
						if (secondBondColor != NULL)
							glColor4ub(secondBondColor->r, secondBondColor->g, secondBondColor->b, secondBondColor->a);
	//                    glTranslatef(centerBond.x, centerBond.y, centerBond.z);
						glTranslatef(secondBondCenter.x, secondBondCenter.y, secondBondCenter.z);
						glRotated(vectorAngle, rotationVector.x, rotationVector.y, rotationVector.z);
						glScaled(1.0f, stickSize, 1.0f);

						renderMesh(stickMesh, nodeMode);
					glPopMatrix();

	//				printf ("Tu sam 3!\n");

	//				glColor4ub(secondBondColor->r, secondBondColor->g, secondBondColor->b, secondBondColor->a);
				}
			}

			if ((nodeMode & VMOL_MODE_PDB_STICKS_BALLS) != 0)
			{
				if (sphereMesh == NULL)
				{
					printf ("Invalid mesh data for rendering!\n");
					return 0;
				}
				// now draw the balls
				for (j=0; j<currentModel->getAtomIndex().size(); j++)
				{
					currentAtom = &(currentModel->getAtom(j));
					colorPointer = NULL;
					if ((nodeMode & VMOL_MODE_PDB_COLOR_ATOM) != 0)
					{
						colorPointer = currentAtom->atomColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_AMINO) != 0)
					{
						colorPointer = currentAtom->aminoColorPointer;
					}
					else if ((nodeMode & VMOL_MODE_PDB_COLOR_CHAIN) != 0)
					{
						colorPointer = currentAtom->chainColorPointer;
					}

					glPushMatrix();
						if (colorPointer != NULL)
							glColor4ub(colorPointer->r, colorPointer->g, colorPointer->b, colorPointer->a);
						glTranslatef(currentAtom->x, currentAtom->y, currentAtom->z);
						glScalef(0.3f, 0.3f, 0.3f);

						renderMesh(sphereMesh, nodeMode);
					glPopMatrix();
				}
			}

			if ((nodeMode & VMOL_MODE_OBJECT_CENTER) != 0)
			{
				glPushMatrix();
				//	   		pdbData->findCenters();
					if (currentModel->getCenterAtomsByMass() == true)
						glTranslatef(currentModel->getMassCenter().x, currentModel->getMassCenter().y, currentModel->getMassCenter().z);
					else
						glTranslatef(currentModel->getArithmeticCenter().x, currentModel->getArithmeticCenter().y, currentModel->getArithmeticCenter().z);

					glBegin(GL_LINES);
						glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f(50.0f, 0.0f, 0.0f);

						glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f(0.0f, 50.0f, 0.0f);

						glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f(0.0f, 0.0f, 50.0f);
					glEnd();
				glPopMatrix();
			}
		}
	}

	if ((nodeMode & VMOL_MODE_OBJECT_CENTER) != 0)
	{
		glPushMatrix();
		//	   		pdbData->findCenters();
			if (pdbData->getCenterAtomsByMass() == true)
				glTranslatef(pdbData->getPdbMassCenter().x, pdbData->getPdbMassCenter().y, pdbData->getPdbMassCenter().z);
			else
				glTranslatef(pdbData->getPdbArithmeticCenter().x, pdbData->getPdbArithmeticCenter().y, pdbData->getPdbArithmeticCenter().z);

			glBegin(GL_LINES);
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(50.0f, 0.0f, 0.0f);

				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 50.0f, 0.0f);

				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, 50.0f);
			glEnd();
		glPopMatrix();
	}

	return 1;
}

/*
Color VmolScene::findAtomColor(AtomPDT *atom)
{
	Color ret;

	return ret;
}
*/
