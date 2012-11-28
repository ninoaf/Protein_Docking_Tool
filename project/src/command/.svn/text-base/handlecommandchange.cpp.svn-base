/*
 * handlecommandchange.cpp
 *
 *  Created on: May 16, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"



int VmolCommand::handleCommandChange(std::vector<CommandParameter> commandVector)
{
	bool isFound=false;
	unsigned int i=0;
	void *varPointer=NULL;
	Parameters params;

	params = handleParameters(commandVector);

	isFound = false;

	if (isFound == false)
	{
		for (i=0; i<charList_.size(); i++)
		{
			if (charList_[i].name == commandVector[1].parameter)
			{
				int tempInt=0;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%d", &tempInt) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					charList_[i].value = (char) tempInt;
				}

				if (params.name.size() > 0)
				{
					charList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<uCharList_.size(); i++)
		{
			if (uCharList_[i].name == commandVector[1].parameter)
			{
				unsigned int tempInt=0;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%u", &tempInt) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					uCharList_[i].value = (unsigned char) tempInt;
				}

				if (params.name.size() > 0)
				{
					uCharList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<longIntList_.size(); i++)
		{
			if (longIntList_[i].name == commandVector[1].parameter)
			{
				long int tempInt=0;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%ld", &tempInt) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					longIntList_[i].value = tempInt;
				}

				if (params.name.size() > 0)
				{
					longIntList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<uLongIntList_.size(); i++)
		{
			if (uLongIntList_[i].name == commandVector[1].parameter)
			{
				unsigned long int tempInt=0;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%lu", &tempInt) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					uLongIntList_[i].value =  tempInt;
				}

				if (params.name.size() > 0)
				{
					uLongIntList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		int scanRet=0;

		for (i=0; i<uLongLongIntList_.size(); i++)
		{
			if (uLongLongIntList_[i].name == commandVector[1].parameter)
			{
				unsigned long long int tempInt=0;

				if (params.value.size() > 0)
				{
					if (params.value.substr(0, 2) == "0x")
						scanRet = sscanf(params.value.c_str(), "0x%llx", &(tempInt));
					else
						scanRet = sscanf(params.value.c_str(), "%llu", &(tempInt));

//					if (sscanf(params.value.c_str(), "%llu", &tempInt) != 1)
					if (scanRet != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					uLongLongIntList_[i].value =  tempInt;
				}

				if (params.name.size() > 0)
				{
					uLongLongIntList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<floatList_.size(); i++)
		{
			if (floatList_[i].name == commandVector[1].parameter)
			{
				float tempFloat=0.0f;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%f", &tempFloat) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					floatList_[i].value = tempFloat;
				}

				if (params.name.size() > 0)
				{
					floatList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<doubleList_.size(); i++)
		{
			if (doubleList_[i].name == commandVector[1].parameter)
			{
				double tempDouble=0.0f;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%lf", &tempDouble) != 1)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					doubleList_[i].value = tempDouble;
				}

				if (params.name.size() > 0)
				{
					doubleList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<stringList_.size(); i++)
		{
			if (stringList_[i].name == commandVector[1].parameter)
			{
				if (params.value.size() > 0)
				{
					*(stringList_[i].value) = params.value;
				}

				if (params.name.size() > 0)
				{
					stringList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<vector3List_.size(); i++)
		{
			if (vector3List_[i].name == commandVector[1].parameter)
			{
				double x=0.0f, y=0.0f, z=0.0f;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%lf %lf %lf", &x, &y, &z) != 3)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					vector3List_[i].value.x = x;
					vector3List_[i].value.y = y;
					vector3List_[i].value.z = z;
				}

				if (params.name.size() > 0)
				{
					vector3List_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<colorList_.size(); i++)
		{
			if (colorList_[i].name == commandVector[1].parameter)
			{
				unsigned int r=0, g=0, b=0, a=0;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%u %u %u %u", &r, &g, &b, &a) != 4)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					colorList_[i].value.r = r;
					colorList_[i].value.g = g;
					colorList_[i].value.b = b;
					colorList_[i].value.a = a;
				}

				if (params.name.size() > 0)
				{
					colorList_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<eulerVector3List_.size(); i++)
		{
			if (eulerVector3List_[i].name == commandVector[1].parameter)
			{
				double alpha=0.0f, beta=0.0f, gamma=0.0f;

				if (params.value.size() > 0)
				{
					if (sscanf(params.value.c_str(), "%lf %lf %lf", &alpha, &beta, &gamma) != 3)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters while changing values!");
						return 1;
					}

					eulerVector3List_[i].value.alpha = alpha;
					eulerVector3List_[i].value.beta = beta;
					eulerVector3List_[i].value.gamma = gamma;
				}

				if (params.name.size() > 0)
				{
					eulerVector3List_[i].name = params.name;
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}



	if (isFound == false)
	{
		for (i=0; i<meshList_.size(); i++)
		{
			if (meshList_[i]->getName() == commandVector[1].parameter)
			{
				if (params.path.size() > 0)
				{
					meshList_[i]->clear();
//					meshList_[i]->loadDat(params.path, meshList_[i]->getCentered());

					if (params.type == "dat")
					{
						if (meshList_[i]->loadDat(params.path, params.center) != 0)
						{
							Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", params.path.c_str());
							return 1;
						}
					}
					else if (params.type == "ms")
					{
						string verticesPath="", indicesPath="";

						verticesPath = params.path + ".vert";
						indicesPath = params.path + ".face";

				//		if (meshList_[i]->loadMS(verticesPath, indicesPath, params.center) != 0)
						if (meshList_[i]->loadMS(params.path, params.center) != 0)
						{
							Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s or %s!", verticesPath.c_str(), indicesPath.c_str());
							return 1;
						}
					}
					else if (params.type == "grid")
					{
						char tempChar[100];
						bool autoIsoValue=false;
						double isoValue=0.0f;
						string autoIsoValueString="";

						if (sscanf(params.value.c_str(), "%s %lf", tempChar, &isoValue) != 2)
						{
							Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
							return 1;
						}

						autoIsoValueString = tempChar;

						if (autoIsoValueString == "true")
							autoIsoValue = true;
						else
							autoIsoValue = false;

						if (meshList_[i]->loadGrid(params.path, params.center, autoIsoValue, isoValue) != 0)
						{
							Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", params.path.c_str());
							return 1;
						}
					}
				}

				if (params.center == true)
				{
					meshList_[i]->center();
				}

				if (params.autoScale != 0.0f)
					meshList_[i]->autoScale(params.autoScale);

				if (params.name.size() > 0)
				{
					meshList_[i]->setName(params.name);
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<pdbList_.size(); i++)
		{
			if (pdbList_[i]->getName() == commandVector[1].parameter)
			{
				if (params.path.size() > 0)
				{
					pdbList_[i]->clear();
					pdbList_[i]->Init(params.path.c_str());
				}

				if (params.radiusPath.size() > 0)
				{
					if (pdbList_[i]->LoadAtmtypenumbers(params.radiusPath.c_str()) == false)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", params.radiusPath.c_str());
						return 1;
					}
				}

				if (params.radiusType.size() > 0)
				{
					if (params.radiusType == "explicit")
						pdbList_[i]->UseExplicitRadius();
					else
						pdbList_[i]->UseUnitedRadius();
				}

				if (params.name.size() > 0)
				{
					pdbList_[i]->setName(params.name);
				}

				if (params.path.size() > 0)
				{
//					pdbList_[i]->clear();
//					pdbList_[i]->Init(params.path.c_str());
//					pdbList_[i]->cpdbList_[i]->getCentered();

					if (pdbList_[i]->Import(pdbList_[i]->getCentered()) == false)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", commandVector[1].value.c_str());
						return 1;
					}
				}

				if (params.centerType.size() > 0)
				{
					if (params.centerType == "mass")
						pdbList_[i]->centerAtomsByMass();
					else if (params.centerType == "arith")
						pdbList_[i]->centerAtomsArithmetically();
				}

				if (params.center == true)
				{
					pdbList_[i]->center();
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<viewList_.size(); i++)
		{
			if (viewList_[i]->getName() == commandVector[1].parameter)
			{
				VmolSceneNode *newRootNode=NULL;

				if (params.nodeParams.size() > 0)
				{
					if ((newRootNode = ((VmolSceneNode *) findVariable(COMMAND_VAR_NODE, params.nodeParams.c_str()))) == NULL)
					{
						Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.parent.c_str());
						return 1;
					}

					rootNodes_[i] = newRootNode;
					viewList_[i]->setSceneRootNode(newRootNode);
				}

				if (params.name.size() > 0)
				{
					viewList_[i]->setName(params.name);
				}

				isFound = true;
				Log::getInstance()->writeToLog("Changed object %s successfully.", commandVector[1].parameter.c_str());
				break;
			}
		}
	}

	if (isFound == false)
	{
		for (i=0; i<nodeList_.size(); i++)
		{
			if (nodeList_[i]->getName() == commandVector[1].parameter)
			{
				handleSubcommandChangeNode(params, nodeList_[i]);
			}
		}
	}

/*
	if ((varPointer = findVariableIndex(COMMAND_VAR_NODE, params.nodeParams.c_str())) != NULL)
	{
		if (params.name.size() > 0)
			((char *) varPointer)
	}
	else if ((varPointer = findVariable(COMMAND_VAR_NODE, params.nodeParams.c_str())) != NULL)
	{
		if (params.name.size() > 0)
			((VmolSceneNode *) varPointer)->setName(params.name);
		if (params.nodeType.size() > 0)
			((VmolSceneNode *) varPointer)->initNode(((VmolSceneNode *) varPointer)->getNodeTypeFromString(params.nodeType));
	}
*/

	{
//		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.parent.c_str());
//		return 1;
	}

	return 0;
}

VmolSceneNode* VmolCommand::findParentNodeRecursion(VmolSceneNode *currentNode, string nodeName)
{
	unsigned int i=0;
	VmolSceneNode *tempRet=NULL;

	for (i=0; i<currentNode->getChildren().size(); i++)
	{
		if (currentNode->getChildren()[i]->getName() == nodeName)
		{
			return currentNode;
		}
	}

	for (i=0; i<currentNode->getChildren().size(); i++)
	{
		tempRet = findParentNodeRecursion(currentNode->getChildren()[i], nodeName);
		if (tempRet != NULL)
			return tempRet;
	}

	return NULL;
}

int VmolCommand::handleSubcommandChangeNode(Parameters params, VmolSceneNode *changeNode)
{
	unsigned int i=0;
	int nodeTypeInt=0;
	string oldName, oldParent;

	oldName = changeNode->getName();
	oldParent = changeNode->getParentName();

	changeNode->clear();

	if (params.nodeType.size() > 0)
	{
		nodeTypeInt = changeNode->getNodeTypeFromString(params.nodeType);
		changeNode->initNode(nodeTypeInt);
	}

	if (params.name.size() > 0)
	{
		changeNode->setName(params.name);
	}

	if (params.nodeParams.size() > 0)
	{
		if (nodeTypeInt == VMOL_NOP)
		{
		}
		else if (nodeTypeInt == VMOL_MESH)
		{
			char *meshName=NULL, *modeName=NULL;
			unsigned long long int *nodeModeParam=NULL;
			Mesh *meshParam;

			meshName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			modeName = (char *) calloc(params.nodeParams.size(), sizeof(char));

			if (meshName==NULL || modeName==NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_MEMORY, "Not enough memory to create a node!");

				if (meshName)
					free(meshName);
				if (modeName)
					free(modeName);

				return 1;
			}

			if (sscanf(params.nodeParams.c_str(), "%s %s", meshName, modeName) != 2)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return 1;
			}

			meshParam = (Mesh *) findVariable(COMMAND_VAR_MESH, meshName);
			nodeModeParam = (unsigned long long int *) findVariable(COMMAND_VAR_UNSIGNED_LONG_LONG, modeName);

			if (meshName)
				free(meshName);
			if (modeName)
				free(modeName);

	/*
			if (meshParam==NULL || nodeModeParam==NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return 1;
			}
	*/
			if (meshParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", meshName);
				return 1;
			}
			if (nodeModeParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", modeName);
				return 1;
			}

			changeNode->setMeshParameters(meshParam, nodeModeParam);
		}
		else if (nodeTypeInt == VMOL_PDB)
		{
			char *pdbName, *meshSphereName, *meshStickName, *modeName;
			unsigned long long int *nodeModeParam=NULL;
			PdbFile *pdbParam=NULL;
			Mesh *meshSphereParam=NULL, *meshStickParam=NULL;

			pdbName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			meshSphereName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			meshStickName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			modeName = (char *) calloc(params.nodeParams.size(), sizeof(char));

			if (pdbName==NULL || meshSphereName==NULL || meshStickName==NULL || modeName==NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_MEMORY, "Not enough memory to create a node!");

				if (pdbName)
					free(pdbName);
				if (meshSphereName)
					free(meshSphereName);
				if (meshStickName)
					free(meshStickName);
				if (modeName)
					free(modeName);

				return 1;
			}

			if (sscanf(params.nodeParams.c_str(), "%s %s %s %s", pdbName, meshSphereName, meshStickName, modeName) != 4)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return 1;
			}

			pdbParam = (PdbFile *) findVariable(COMMAND_VAR_PDB, pdbName);
			meshSphereParam = (Mesh *) findVariable(COMMAND_VAR_MESH, meshSphereName);
			meshStickParam = (Mesh *) findVariable(COMMAND_VAR_MESH, meshStickName);
			nodeModeParam = (unsigned long long int *) findVariable(COMMAND_VAR_UNSIGNED_LONG_LONG, modeName);

			if (pdbName)
				free(pdbName);
			if (meshSphereName)
				free(meshSphereName);
			if (meshStickName)
				free(meshStickName);
			if (modeName)
				free(modeName);

			if (pdbParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", pdbName);
				return 1;
			}
			if (meshSphereParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", meshSphereName);
				return 1;
			}
			if (meshStickParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", meshStickName);
				return 1;
			}
			if (nodeModeParam == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", modeName);
				return 1;
			}

			changeNode->setPdbParameters(pdbParam, meshSphereParam, meshStickParam, nodeModeParam);
		}
		else if (nodeTypeInt == VMOL_COLOR)
		{
			Color *colorParam=NULL;

			if ((colorParam = ((Color *) findVariable(COMMAND_VAR_COLOR, params.nodeParams.c_str()))) == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setColorParameters(colorParam);
		}
		else if (nodeTypeInt == VMOL_TEXTURE)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}

		else if (nodeTypeInt == VMOL_LOOK_AT)
		{
			char *positionName, *lookVectorName, *lookUpName;
			Vector3 *positionParam, *lookVectorParam, *lookUpParam;

			positionName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			lookVectorName = (char *) calloc(params.nodeParams.size(), sizeof(char));
			lookUpName = (char *) calloc(params.nodeParams.size(), sizeof(char));

			if (positionName==NULL || lookVectorName==NULL || lookUpName==NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_MEMORY, "Not enough memory to create a node!");

				if (positionName)
					free(positionName);
				if (lookVectorName)
					free(lookVectorName);
				if (lookUpName)
					free(lookUpName);

				return 1;
			}

			if (sscanf(params.nodeParams.c_str(), "%s %s %s", positionName, lookVectorName, lookUpName) != 3)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return 1;
			}

			positionParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, positionName);
			lookVectorParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, lookVectorName);
			lookUpParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, lookUpName);

			if (positionName)
				free(positionName);
			if (lookVectorName)
				free(lookVectorName);
			if (lookUpName)
				free(lookUpName);

			if (positionParam==NULL || lookVectorParam==NULL || lookUpParam==NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return 1;
			}

			changeNode->setViewParameters(positionParam, lookVectorParam, lookUpParam);
		}
		else if (nodeTypeInt == VMOL_TRANSLATION)
		{
			Vector3 *translationParam=NULL;

			if ((translationParam = ((Vector3 *) findVariable(COMMAND_VAR_VECTOR3, params.nodeParams.c_str()))) == NULL)
			{
	//			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setTranslationParameters(translationParam);
		}
		else if (nodeTypeInt==VMOL_ROTATION_CARTHESIAN_X || nodeTypeInt==VMOL_ROTATION_CARTHESIAN_Y || nodeTypeInt==VMOL_ROTATION_CARTHESIAN_Z)
		{
			double *rotationParam=NULL;

			if ((rotationParam = ((double *) findVariable(COMMAND_VAR_DOUBLE, params.nodeParams.c_str()))) == NULL)
			{
	//			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setRotationAngleParameters(rotationParam);
		}
		else if (nodeTypeInt == VMOL_ROTATION_EULER)
		{
			EulerVector3 *rotationParam=NULL;

			if ((rotationParam = ((EulerVector3 *) findVariable(COMMAND_VAR_EULER_VECTOR3, params.nodeParams.c_str()))) == NULL)
			{
	//			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setEulerRotationParameters(rotationParam);
		}
		else if (nodeTypeInt == VMOL_SCALE)
		{
			Vector3 *scaleParam=NULL;

			if ((scaleParam = ((Vector3 *) findVariable(COMMAND_VAR_VECTOR3, params.nodeParams.c_str()))) == NULL)
			{
	//			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setScaleParameters(scaleParam);
		}

		else if (nodeTypeInt == VMOL_SHADER_PIXEL)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}
		else if (nodeTypeInt == VMOL_SHADER_VERTEX)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}
		else if (nodeTypeInt == VMOL_SHADER_GEOMETRY)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}

		else if (nodeTypeInt == VMOL_PROJECTION_MATRIX)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}
		else if (nodeTypeInt == VMOL_MODELVIEW_MATRIX)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_NOT_IMPLEMENTED, "Command not yet implemented!");
			return 1;
		}
		else if (nodeTypeInt == VMOL_SCRIPT)
		{
			string *scriptPathParam=NULL;

			if ((scriptPathParam = ((string *) findVariable(COMMAND_VAR_STRING, params.nodeParams.c_str()))) == NULL)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
				return 1;
			}

			changeNode->setScriptParameters(scriptPathParam);
		}
	}

//	if (params.parent.size() > 0)
//	{
		VmolSceneNode *currentParentNode=NULL;

/*
		for (i=0; i<rootNodes_.size(); i++)
		{
			currentParentNode = findParendNodeRecursion(rootNodes_[i], changeNode->getName());

			if (currentParentNode != NULL)
				break;
		}
*/

	int rootIndex=-1, parentIndex=-1;

	for (i=0; i<rootNodes_.size(); i++)
	{
		if (rootNodes_[i]->getName() == oldName)
		{
			rootIndex = i;
			break;
		}
	}

	for (i=0; i<nodeList_.size(); i++)
	{
		if (nodeList_[i]->getName() == oldParent)
		{
			parentIndex = i;
			break;
		}
	}

	if (oldParent=="" && params.parent!="")
	{
		if (rootIndex >= 0)
			rootNodes_.erase(rootNodes_.begin()+rootIndex);

		for (i=0; i<nodeList_.size(); i++)
		{
			if (nodeList_[i]->getName() == params.parent)
			{
				nodeList_[i]->getChildren().push_back(changeNode);
				changeNode->setParentName(params.parent);
				break;
			}
		}
	}
	else if (oldParent!="" && params.parent=="")
	{
		if (parentIndex >= 0)
		{
			for (i=0; i<nodeList_[parentIndex]->getChildren().size(); i++)
			{
				if (nodeList_[parentIndex]->getChildren()[i] == changeNode)
				{
					nodeList_[parentIndex]->getChildren().erase(nodeList_[parentIndex]->getChildren().begin()+i);
					break;
				}
			}
		}

		rootNodes_.push_back(changeNode);
	}
	else if (oldParent!="" && params.parent!="")
	{
		if (parentIndex >= 0)
		{
			for (i=0; i<nodeList_[parentIndex]->getChildren().size(); i++)
			{
				if (nodeList_[parentIndex]->getChildren()[i] == changeNode)
				{
					nodeList_[parentIndex]->getChildren().erase(nodeList_[parentIndex]->getChildren().begin()+i);
					break;
				}
			}
		}

		for (i=0; i<nodeList_.size(); i++)
		{
			if (nodeList_[i]->getName() == params.parent)
			{
				nodeList_[i]->getChildren().push_back(changeNode);
				changeNode->setParentName(params.parent);
				break;
			}
		}
	}

	changeNode->setParentName(params.parent);

	if (currentParentNode != NULL)
	{
	}
//	}

	return 0;
}
