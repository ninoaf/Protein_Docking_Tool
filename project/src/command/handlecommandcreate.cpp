/*
 * handlecommandcreate.cpp
 *
 *  Created on: May 16, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"
#include "../msmswrapper/msmswrapper.h"



int VmolCommand::handleCommandCreate(std::vector<CommandParameter> commandVector)
{
	if (commandVector[0].parameter != COMMAND_CREATE)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	if (commandVector[1].parameter == SUBCOMMAND_PDB)
	{
		return handleSubcommandCreatePdb(commandVector);
	}
	else if (commandVector[1].parameter == SUBCOMMAND_MESH)
	{
		return handleSubcommandCreateMesh(commandVector);
	}
	else if (commandVector[1].parameter == SUBCOMMAND_NODE)
	{
		return handleSubcommandCreateNode(commandVector);
	}
	else if (commandVector[1].parameter == SUBCOMMAND_VARIABLE)
	{
		return handleSubcommandCreateVariable(commandVector);
	}
	else if (commandVector[1].parameter == SUBCOMMAND_VIEW)
	{
		return handleSubcommandCreateView(commandVector);
	}
	else if (commandVector[1].parameter == SUBCOMMAND_MS)
	{
		return handleSubcommandCreateMs(commandVector);
	}

	return 1;
}

int VmolCommand::handleSubcommandCreatePdb(vector<CommandParameter> commandVector)
{
//	bool paramCenterAtoms=true, paramCenterByMass=true, paramCenterArithmetically=false, paramUseUnitedRadius=true, paramUseExplicitRadius=true;
//	string paramName="", paramRadiusPath="";
	string pdbName="", pdbPath="";
	Parameters params;
	PdbFile *newPdb;

//	printf ("Create PDB...");

	newPdb = new PdbFile();

	params = handleParameters(commandVector);

	if (params.name.size() == 0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	pdbPath = commandVector[1].value;
	if (params.path.size() > 0)
		pdbPath = params.path;

	if (pdbPath.size()==0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	newPdb->Init(pdbPath.c_str());

	if (newPdb->LoadAtmtypenumbers(params.radiusPath.c_str()) == false)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", params.radiusPath.c_str());
		return 1;
	}

	if (params.radiusType == "explicit")
		newPdb->UseExplicitRadius();
	else
		newPdb->UseUnitedRadius();

	newPdb->setName(params.name);

	if (newPdb->importModel(0, params.center) != 0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", commandVector[1].value.c_str());
		return 1;
	}

	if (params.center == true)
	{
		if (params.centerType == "mass")
			newPdb->centerAtomsByMass();
		else if (params.centerType == "arith")
			newPdb->centerAtomsArithmetically();
	}

	pdbList_.push_back(newPdb);

	Log::getInstance()->writeToLog("Created PDB file #%d, name: %s.", pdbList_.size(), params.name.c_str());

//	printf ("done!\n");

	return 0;
}

int VmolCommand::handleSubcommandCreateMesh(vector<CommandParameter> commandVector)
{
	string meshPath="";
	Parameters params;
	Mesh *newMesh;

	params = handleParameters(commandVector);

	if (params.name.size()==0 || params.type.size()==0 || (params.type=="grid" && params.value.size()<1))
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	meshPath = commandVector[1].value;
	if (params.path.size()>0)
		meshPath = params.path;

//	printf ("meshPath = %s\n", meshPath.c_str());

	if (meshPath.size() == 0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	newMesh = new Mesh();

	if (params.type == "dat")
	{
		if (newMesh->loadDat(meshPath, params.center) != 0)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", meshPath.c_str());
			return 1;
		}
	}
	else if (params.type == "ms")
	{
		string verticesPath="", indicesPath="";

		verticesPath = meshPath + ".vert";
		indicesPath = meshPath + ".face";

//		if (newMesh->loadMS(verticesPath, indicesPath, params.center) != 0)
		if (newMesh->loadMS(meshPath, params.center) != 0)
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

		if (newMesh->loadGrid(meshPath, params.center, autoIsoValue, isoValue) != 0)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", meshPath.c_str());
			return 1;
		}
	}

//	if (params.autoScale != 0.0f)
	newMesh->autoScale(params.autoScale);

	newMesh->setName(params.name);

	meshList_.push_back(newMesh);

	Log::getInstance()->writeToLog("Created Mesh file #%d, name: %s.", meshList_.size(), params.name.c_str());

	return 0;
}

int VmolCommand::handleSubcommandCreateNode(vector<CommandParameter> commandVector)
{
	unsigned int nodeTypeInt=0;
	Parameters params;
	VmolSceneNode *newNode;
	VmolSceneNode *parentNode=NULL;

	params = handleParameters(commandVector);

	newNode = new VmolSceneNode();

	nodeTypeInt = newNode->getNodeTypeFromString(params.nodeType);

//		newPdb.Init(commandVector[1].value.c_str());

	newNode->initNode(nodeTypeInt);

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

		newNode->setMeshParameters(meshParam, nodeModeParam);
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

		newNode->setPdbParameters(pdbParam, meshSphereParam, meshStickParam, nodeModeParam);
	}
	else if (nodeTypeInt == VMOL_COLOR)
	{
		Color *colorParam=NULL;

		if ((colorParam = ((Color *) findVariable(COMMAND_VAR_COLOR, params.nodeParams.c_str()))) == NULL)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.nodeParams.c_str());
			return 1;
		}

		newNode->setColorParameters(colorParam);
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

		newNode->setViewParameters(positionParam, lookVectorParam, lookUpParam);
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

		newNode->setTranslationParameters(translationParam);
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

		newNode->setRotationAngleParameters(rotationParam);
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

		newNode->setEulerRotationParameters(rotationParam);
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

		newNode->setScaleParameters(scaleParam);
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

//		printf ("path2 = %s\n", scriptPathParam->c_str());

		newNode->setScriptParameters(scriptPathParam);
	}

	newNode->setName(params.name);

/*
	if (nodeTypeInt == VMOL_SCRIPT)
	{
		string *tempString;
		newNode->getScriptParameters(&tempString);
//		printf ("path3 = %s\n", tempString->c_str());
	}
*/

	nodeList_.push_back(newNode);

//	printf ("parent = '%s', name = '%s'\n", params.parent.c_str(), params.name.c_str());

	if (params.parent.size() > 0)
	{
		if ((parentNode = ((VmolSceneNode *) findVariable(COMMAND_VAR_NODE, params.parent.c_str()))) == NULL)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.parent.c_str());
			return 1;
		}

		newNode->setParentName(params.parent);
	}
	else
	{
		newNode->setParentName("");
		rootNodes_.push_back(newNode);
	}

//	printf ("rootNodes_.size() = %d\n", rootNodes_.size());



//	printf ("newNode = %s, parent = %s\n", newNode->getName().c_str(), params.parent.c_str());



	VmolSceneNode *nodeVar=NULL;
	nodeVar = (VmolSceneNode *) findVariable(COMMAND_VAR_NODE, params.name);
	if (nodeVar == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.name.c_str());
		return 1;
	}

	if (parentNode != NULL)
	{
		parentNode->addChild(newNode);
	}
	else
	{
//		for (unsigned int i=0; i<rootNodes_.size(); i++)
//			rootNodes_[i]->addChild(nodeVar);
	}

	Log::getInstance()->writeToLog("Created node #%d, name: %s.", nodeList_.size(), params.name.c_str());

	return 0;
}



int VmolCommand::handleSubcommandCreateVariable(vector<CommandParameter> commandVector)
{
	string varName="";
	Parameters params;

	params = handleParameters(commandVector);

	varName = commandVector[1].value;
	if (params.name.size() > 0)
		varName = params.name;

	if (params.name.size() == 0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	if (findVariable(COMMAND_VAR_ALL, params.name) != NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, variable %s already exists!", params.name.c_str());
		return 1;
	}



	if (params.type == "char")
	{
		int tempInt=0;

		VariableName<char> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%d", &tempInt) != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		newVar.value = (char) tempInt;

		charList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type char, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "uchar")
	{
		unsigned int tempInt=0;
		VariableName<unsigned char> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%ud", &tempInt) != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		newVar.value = (unsigned int) tempInt;

		uCharList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type uchar, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "long")
	{
		VariableName<long int> newVar;

		int scanRet=0;
		if (params.value.substr(0, 2) == "0x")
			scanRet = sscanf(params.value.c_str(), "0x%lx", &(newVar.value));
		else
			scanRet = sscanf(params.value.c_str(), "%ld", &(newVar.value));

		newVar.name = varName;
		if (scanRet != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		longIntList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type long, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "ulong")
	{
		VariableName<unsigned long int> newVar;

		int scanRet=0;
		if (params.value.substr(0, 2) == "0x")
			scanRet = sscanf(params.value.c_str(), "0x%x", &(newVar.value));
		else
			scanRet = sscanf(params.value.c_str(), "%lu", &(newVar.value));

		newVar.name = varName;
		if (scanRet != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		uLongIntList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type long long, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "ulonglong")
	{
		VariableName<unsigned long long int> newVar;

		int scanRet=0;
		if (params.value.substr(0, 2) == "0x")
			scanRet = sscanf(params.value.c_str(), "0x%llx", &(newVar.value));
		else
			scanRet = sscanf(params.value.c_str(), "%lld", &(newVar.value));

		newVar.name = varName;
		if (scanRet != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		uLongLongIntList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type ulonglong, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "float")
	{
		VariableName<float> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%f", &(newVar.value)) != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		floatList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type float, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "double")
	{
		VariableName<double> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%lf", &(newVar.value)) != 1)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		doubleList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type double, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "vector3")
	{
		VariableName<Vector3> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%lf %lf %lf", &(newVar.value.x), &(newVar.value.y), &(newVar.value.z)) != 3)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		vector3List_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type vector3, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "color")
	{
		unsigned int r=0, g=0, b=0, a=0;

		VariableName<Color> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%u %u %u %u", &r, &g, &b, &a) != 4)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		newVar.value.r = (unsigned char) r;
		newVar.value.g = (unsigned char) g;
		newVar.value.b = (unsigned char) b;
		newVar.value.a = (unsigned char) a;

		colorList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type color, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "eulervector3")
	{
		VariableName<EulerVector3> newVar;

		newVar.name = varName;
		if (sscanf(params.value.c_str(), "%lf %lf %lf", &(newVar.value.alpha), &(newVar.value.beta), &(newVar.value.gamma)) != 3)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
			return 1;
		}

		eulerVector3List_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type eulervector3, name: %s.", varName.c_str());

		return 0;
	}
	else if (params.type == "string")
	{
		VariableName<string *> newVar;
		string *newValue=NULL;

		newValue = new string;
		(*newValue) = params.value;

		newVar.name = varName;
//		newVar.value = params.value;
		newVar.value = newValue;

		stringList_.push_back(newVar);

		Log::getInstance()->writeToLog("Created variable, type string, name: %s.", varName.c_str());

		return 0;
	}

	Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Variable %s can not be created, variable type undefined!", varName.c_str());

	return 1;
}

int VmolCommand::handleSubcommandCreateView(vector<CommandParameter> commandVector)
{
	char positionName[100], lookName[100], upName[100], rootNodeName[100];
	unsigned int i=0;
	Parameters params;
	Vector3 *positionParam=NULL, *lookParam=NULL, *upParam=NULL;
	VmolSceneNode *newRootNode=NULL;
	VmolSceneNode *nodeParam=NULL;

	if (viewList_.size() >= NUM_OPENGL_BOXES)
	{
		Log::getInstance()->errorReport("WARNING", ERR_COMMAND_CANT_EXECUTE, "Can not execute command 'view', maximum number of views already created!");
		return 1;
	}

	params = handleParameters(commandVector);

	if (params.nodeParams.size() > 0)
	{
		if ((newRootNode = ((VmolSceneNode *) findVariable(COMMAND_VAR_NODE, params.nodeParams.c_str()))) == NULL)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.parent.c_str());
			return 1;
		}
	}

//	rootNodes_.push_back(newRootNode);

/*
	newRootNode = new VmolSceneNode();
	if (params.name.size() == 0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	newRootNode->initNode(VMOL_LOOK_AT);

	VariableName<Vector3> position, look, up;
	sprintf (positionName, "rootnode#%d_position", rootNodes_.size());
	sprintf (lookName, "rootnode#%d_look", rootNodes_.size());
	sprintf (upName, "rootnode#%d_up", rootNodes_.size());

	// initialize default values and names
	position.value.x = 0.0f;	position.value.y = 0.0f;	position.value.z = -40.0f;
	position.name = positionName;
	look.value.x = 0.0f;		look.value.y = 0.0f;		look.value.z = 0.0f;
	look.name = lookName;
	up.value.x = 0.0f;			up.value.y = 1.0f;			up.value.z = 0.0f;
	up.name = upName;

	vector3List_.push_back(position);
	vector3List_.push_back(look);
	vector3List_.push_back(up);

	positionParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, position.name);
	lookParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, look.name);
	upParam = (Vector3 *) findVariable(COMMAND_VAR_VECTOR3, up.name);

	if (positionParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", position.name.c_str());
		return 1;
	}
	if (lookParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", look.name.c_str());
		return 1;
	}
	if (upParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", up.name.c_str());
		return 1;
	}



	sprintf (rootNodeName, "rootnode#%d", rootNodes_.size());

	newRootNode->setViewParameters(positionParam, lookParam, upParam);
	newRootNode->setName((string) rootNodeName);

	nodeList_.push_back(newRootNode);

	nodeParam = (VmolSceneNode *) findVariable(COMMAND_VAR_NODE, (string) rootNodeName);

	if (nodeParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", rootNodeName);
		return 1;
	}

	rootNodes_.push_back(nodeParam);
//	printf ("create_view: nodeParam = %s\n", rootNodes_[rootNodes_.size()-1]->getName().c_str());
*/



//	VmolGui::getInstance()->mainWindow->begin();
//	VmolGui::getInstance()->mainWindow->hide();

/*
	VmolView *newView;

	newView = new VmolView(1, 1, 100, 100);
	newView->setSceneRootNode(rootNodes_[rootNodes_.size()-1]);
	newView->setName(params.name);

	viewList_.push_back(newView);



	VmolGui::getInstance()->changeBoxNumber(viewList_.size());
//	for (unsigned int i=0; i<viewList_.size(); i++)
//		viewList_[i]->resize(VmolGui::getInstance()->getOglBoxPosition()[i].x, VmolGui::getInstance()->getOglBoxPosition()[i].y, VmolGui::getInstance()->getOglBoxPosition()[i].width, VmolGui::getInstance()->getOglBoxPosition()[i].height);

	VmolGui::getInstance()->mainWindow->add(newView);
	VmolGui::getInstance()->mainWindow->flush();
	VmolGui::getInstance()->mainWindow->redraw();

	VmolGui::getInstance()->mainWindow->show();
//	VmolGui::getInstance()->mainWindow->end();
//	VmolGui::getInstance()->mainWindow->f
*/

//	VmolGui::getInstance()->getOglBox()[(viewList_.size())]->setSceneRootNode(rootNodes_[rootNodes_.size()-1]);
	VmolGui::getInstance()->getOglBox()[(viewList_.size())]->setSceneRootNode(newRootNode);
	VmolGui::getInstance()->getOglBox()[(viewList_.size())]->setName(params.name);
	viewList_.push_back((VmolGui::getInstance()->getOglBox()[(viewList_.size())]));
	VmolGui::getInstance()->changeBoxNumberAndResize(viewList_.size());

	for (i=0; i<viewList_.size(); i++)
	{
		viewList_[i]->setInitializedGL(false);
		viewList_[i]->redraw();
	}

	Log::getInstance()->writeToLog("Created view #%d, name: %s.", viewList_.size(), params.name.c_str());

	return 0;

}

int VmolCommand::handleSubcommandCreateMs(vector<CommandParameter> commandVector)
{
	unsigned long long int *nodeModeParam=NULL;
	PdbFile *pdbParam=NULL;
	string atomsPath="";
	MSMSWrapper wrapper;
	Parameters params;

	params = handleParameters(commandVector);

	if (params.name.size()==0 || params.path.size()==0 || params.value.size()==0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating molecular surface!");
		return 1;
	}

	nodeModeParam = (unsigned long long int *) findVariable(COMMAND_VAR_UNSIGNED_LONG_LONG, params.value);
	pdbParam = (PdbFile *) findVariable(COMMAND_VAR_PDB, params.name);

	if (nodeModeParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.value.c_str());
		return 1;
	}

	if (pdbParam == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist, or is of incorrect type!", params.name.c_str());
		return 1;
	}

	atomsPath = params.path + ".atc";			// atom coords file

	if (pdbParam->SaveCoords(atomsPath.c_str()) == false)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_RETURNED_FUNCTION, "Can't save coords while executing 'create ms' command!");
		return 1;
	}

//	printf ("vertices = %s\nindices = %s\n", verticesPath.c_str(), indicesPath.c_str());
//	printf ("atomsPath = %s\n", atomsPath.c_str());

	if (wrapper.load(atomsPath, false) == false)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_RETURNED_FUNCTION, "Can't create molecular surface while executing 'create ms' command!");
		return 1;
	}

	return 0;
}
