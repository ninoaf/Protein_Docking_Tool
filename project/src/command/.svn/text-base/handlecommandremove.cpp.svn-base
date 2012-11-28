/*
 * handlecommandremove.cpp
 *
 *  Created on: May 16, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"



int VmolCommand::handleCommandRemove(std::vector<CommandParameter> commandVector)
{
	bool isFound=false;
	unsigned long int i=0, j=0, k=0;
	VmolSceneNode *parentNode=NULL;

	isFound = false;

	for(j=1; j<commandVector.size(); j++)
	{
		if (isFound == false)
		{
			for (i=0; i<charList_.size(); i++)
			{
				if (charList_[i].name == commandVector[j].parameter)
				{
					charList_.erase(charList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<uCharList_.size(); i++)
			{
				if (uCharList_[i].name == commandVector[j].parameter)
				{
					uCharList_.erase(uCharList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<stringList_.size(); i++)
			{
				if (stringList_[i].name == commandVector[j].parameter)
				{
					delete stringList_[i].value;
					stringList_.erase(stringList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<longIntList_.size(); i++)
			{
				if (longIntList_[i].name == commandVector[j].parameter)
				{
					longIntList_.erase(longIntList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<uLongIntList_.size(); i++)
			{
				if (uLongIntList_[i].name == commandVector[j].parameter)
				{
					uLongIntList_.erase(uLongIntList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<uLongLongIntList_.size(); i++)
			{
				if (uLongLongIntList_[i].name == commandVector[j].parameter)
				{
					uLongLongIntList_.erase(uLongLongIntList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<floatList_.size(); i++)
			{
				if (floatList_[i].name == commandVector[j].parameter)
				{
					floatList_.erase(floatList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<doubleList_.size(); i++)
			{
				if (doubleList_[i].name == commandVector[j].parameter)
				{
					doubleList_.erase(doubleList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<vector3List_.size(); i++)
			{
				if (vector3List_[i].name == commandVector[j].parameter)
				{
					vector3List_.erase(vector3List_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<colorList_.size(); i++)
			{
				if (colorList_[i].name == commandVector[j].parameter)
				{
					colorList_.erase(colorList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<eulerVector3List_.size(); i++)
			{
				if (eulerVector3List_[i].name == commandVector[j].parameter)
				{
					eulerVector3List_.erase(eulerVector3List_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<meshList_.size(); i++)
			{
				if (meshList_[i]->getName() == commandVector[j].parameter)
				{
					delete meshList_[i];
					meshList_.erase(meshList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<pdbList_.size(); i++)
			{
				if (pdbList_[i]->getName() == commandVector[j].parameter)
				{
					delete pdbList_[i];
					pdbList_.erase(pdbList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<viewList_.size(); i++)
			{
				if (viewList_[i]->getName() == commandVector[j].parameter)
				{
					delete viewList_[i];
					viewList_.erase(viewList_.begin()+i);
					isFound = true;
					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());
					break;
				}
			}
		}

		if (isFound == false)
		{
			for (i=0; i<nodeList_.size(); i++)
			{
				if (nodeList_[i]->getName() == commandVector[j].parameter)
				{
					// before we remove the node itself, we have to remove all references to that node from other nodes
					for (j=0; j<nodeList_.size(); j++)
					{
						if (i == j)
							continue;

						for (k=0; k<nodeList_[j]->getChildren().size(); k++)
						{
							if (nodeList_[j]->getChildren()[k]->getName() == nodeList_[i]->getName())
							{
								nodeList_[j]->getChildren().erase(nodeList_[j]->getChildren().begin()+k);
								printf ("%s->%s\n", nodeList_[j]->getName().c_str(), nodeList_[i]->getName().c_str());
								break;
							}
						}
					}

printf ("Asd 1!\n");

					// the same goes if the node is also a root node
					for (j=0; j<rootNodes_.size(); j++)
					{
						if (rootNodes_[j]->getName() == nodeList_[i]->getName())
						{
							rootNodes_.erase(rootNodes_.begin()+j);
							break;
						}
					}

					printf ("Asd 2!\n");

					// now to delete the node
					delete nodeList_[i];
					nodeList_.erase(nodeList_.begin()+i);
//					isFound = true;
//					Log::getInstance()->writeToLog("Removed object %s successfully.", commandVector[j].parameter.c_str());

					printf ("Asd 3!\n");

					break;
				}
			}
		}

		if (isFound == false)
		{
			Log::getInstance()->errorReport("WARNING", ERR_COMMAND_WRONG_PARAM, "Can not remove object %s, object not found!", commandVector[j].parameter.c_str());

			return 1;
		}
	}

	return 0;
}
