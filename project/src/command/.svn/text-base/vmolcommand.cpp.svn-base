 /*
 * vmolcommand.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: ivan
 */

#include "vmolcommand.h"
#include "../log/log.h"

using namespace std;

VmolCommand* VmolCommand::singleInstance_=NULL;



VmolCommand::VmolCommand()
{
	init();
}

VmolCommand::~VmolCommand()
{
}

VmolCommand* VmolCommand::getInstance()
{
	if (singleInstance_ == NULL)
	{
		singleInstance_ = new VmolCommand();
		return singleInstance_;
	}

	return singleInstance_;
}

void VmolCommand::init()
{
	pdbList_.clear();
	meshList_.clear();
	viewList_.clear();
	nodeList_.clear();

	initCommands();
	scoresData_.init();
}

void VmolCommand::initCommands()
{
	commandList_.clear();
	subCommandList_.clear();
	parameterList_.clear();

	commandList_.push_back(COMMAND_CREATE);
	commandList_.push_back(COMMAND_CHANGE);
	commandList_.push_back(COMMAND_REMOVE);

	subCommandList_.push_back(SUBCOMMAND_MESH);
	subCommandList_.push_back(SUBCOMMAND_PDB);
	subCommandList_.push_back(SUBCOMMAND_GRID);
	subCommandList_.push_back(SUBCOMMAND_VIEW);
	subCommandList_.push_back(SUBCOMMAND_NODE);

	parameterList_.push_back(PARAMETER_NAME);
	parameterList_.push_back(PARAMETER_PATH);
	parameterList_.push_back(PARAMETER_CENTER);
	parameterList_.push_back(PARAMETER_NODE_TYPE);
	parameterList_.push_back(PARAMETER_TRANSLATE);
	parameterList_.push_back(PARAMETER_ROTATE_X);
	parameterList_.push_back(PARAMETER_ROTATE_Y);
	parameterList_.push_back(PARAMETER_ROTATE_Z);
	parameterList_.push_back(PARAMETER_ROTATE_EULER);
}

int VmolCommand::executeCommand(std::string commandString, bool outputToLog)
{
	unsigned int i=0;
	int ret=0;
	string singleCommand="";			// if the string consists of multiple commands (split by ';' character)

	if (outputToLog == true)
		commandHistory_.push_back(commandString);

	for (i=0; i<commandString.size(); i++)
	{
		if (commandString[i] == ';')
		{
			ret = splitAndExecute(singleCommand, outputToLog);
			singleCommand = "";

			if (ret != 0)
				return ret;
		}
		else
		{
			singleCommand += commandString[i];
		}
	}

	if (singleCommand.size() > 0)
	{
		ret = splitAndExecute(singleCommand);

		if (ret != 0)
			return ret;
	}

	return 0;
}

int VmolCommand::splitAndExecute(std::string commandString, bool outputToLog)
{
	unsigned int i=0, j=0;
	int bracket1Level=0;			// level of opened brackets ()
	int bracket2Level=0;			// level of opened brackets []
	int bracket3Level=0;			// level of opened brackets {}
	string parameterString;
	CommandParameter commandParameter;
	vector<CommandParameter> commandVector;

	parameterString = "";
	commandVector.clear();

	if (commandString.size() == 0)
		return 0;

//	Log::getInstance()->writeToLog("> %s", commandString.c_str());

//	printf ("%s\n", commandString.c_str());

	commandString = handleSpecialCharacters(commandString);

	for (i=0; i<commandString.size(); i++)
	{
		if (commandString[i]=='(' && (i>0 && commandString[i-1]!='\\'))	{ bracket1Level += 1; }
		if (commandString[i]==')' && (i>0 && commandString[i-1]!='\\'))	{ bracket1Level -= 1; }
		if (commandString[i]=='[' && (i>0 && commandString[i-1]!='\\'))	{ bracket2Level += 1; }
		if (commandString[i]==']' && (i>0 && commandString[i-1]!='\\'))	{ bracket2Level -= 1; }
		if (commandString[i]=='{' && (i>0 && commandString[i-1]!='\\'))	{ bracket3Level += 1; }
		if (commandString[i]=='}' && (i>0 && commandString[i-1]!='\\'))	{ bracket3Level -= 1; }

		if (commandString[i]=='{' && bracket3Level==1)	continue;
		if (commandString[i]=='}' && bracket3Level==0)	continue;

		if (commandString[i]!=' ' && commandString[i]!='\t' && commandString[i]!='\n' || bracket3Level>0)
			parameterString += commandString[i];
		else
		{
			// za popraviti: ako je naredba imala parametar u viticastim zagradama, unutar nje parametri ne smiju imati znak '=', jer ce biti
			// rastavljeni, ako prije prve viticaste zagrade ne postoji '='

//			printf ("--> %s\n", parameterString.c_str());

			if (parameterString.size() > 0)
			{
				for (j=0; j<parameterString.size(); j++)
				{
					if (parameterString[j]=='=' && (j==0 || j>0 && parameterString[j-1]!='\\') && bracket3Level==0)
						break;
				}

// printf ("bracket3Level = %d\n", bracket3Level);

				commandParameter.parameter = commandParameter.value = "";

				commandParameter.parameter = parameterString.substr(0, j);
				if (j< parameterString.size())
					commandParameter.value = parameterString.substr((j+1), (parameterString.size()-j));

				commandVector.push_back(commandParameter);
			}
			parameterString = "";
		}
	}

	if (parameterString.size() > 0)
	{
		for (j=0; j<parameterString.size(); j++)
		{
			if (parameterString[j]=='=' && (j==0 || j>0 && parameterString[j-1]!='\\') && bracket3Level==0)
				break;
		}

		commandParameter.parameter = commandParameter.value = "";

		commandParameter.parameter = parameterString.substr(0, j);
		if (j< parameterString.size())
			commandParameter.value = parameterString.substr((j+1), (parameterString.size()-j));

		commandVector.push_back(commandParameter);
	}

	parameterString = "";

	return executeCommand(commandVector, outputToLog);
}

int VmolCommand::executeCommand(std::vector<CommandParameter> commandVector, bool outputToLog)
{
	unsigned int i=0;
	int syntaxErrorCode=0;

	if (commandVector.size() == 0)
		return 1;

	syntaxErrorCode = checkSyntax(commandVector);

	if (syntaxErrorCode)
		return syntaxErrorCode;

//	for (i=0; i<commandVector.size(); i++)
//		printf ("|%s| = |%s|\n", commandVector[i].parameter.c_str(), commandVector[i].value.c_str());

//	printf ("doubleList_.size() = %d\n", doubleList_.size());

	handleCommands(commandVector);

	return 0;
}

int VmolCommand::parseCommandString(std::string commandString)
{
}

/*
PdbFile* VmolCommand::findPdbByName(std::string pdbName)
{
	for (unsigned int i=0; i<pdbList_.size(); i++)
	{
		if (pdbList_[i]->getName() == pdbName)
			return (pdbList_[i]);
	}

	return NULL;
}

Mesh* VmolCommand::findMeshByName(std::string meshName)
{
	for (unsigned int i=0; i<meshList_.size(); i++)
	{
		if (meshList_[i]->getName() == meshName)
			return (meshList_[i]);
	}

	return NULL;
}
*/

int VmolCommand::checkSyntax(std::vector<CommandParameter> commandVector)
{
	return 0;
}

string VmolCommand::trimFileName(string path)
{
	int i=0;
	unsigned int firstDot=0;
	string singleCharacter="";
	string ret="";

	firstDot = path.size();

	for (i=(path.size()-1); i>=0; i--)
	{
		if (path[i] == '/')
			break;

		if (path[i]=='.' && firstDot==path.size())
			firstDot = i;
	}

	ret = path.substr((i+1), (path.size()-i)-1);

	if (firstDot < path.size())
		ret = ret.substr(0, (ret.size()-(path.size()-firstDot)));

	return ret;
}

void* VmolCommand::findVariable(unsigned long int variableType, std::string variableName)
{
	unsigned long int i=0;

	if (variableType==COMMAND_VAR_CHAR || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<charList_.size(); i++)
			if (charList_[i].name == variableName)
				return ((void *) &(charList_[i].value));
	}

	if (variableType==COMMAND_VAR_UNSIGNED_CHAR || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<uCharList_.size(); i++)
			if (uCharList_[i].name == variableName)
				return ((void *) &(uCharList_[i].value));
	}

	if (variableType==COMMAND_VAR_STRING || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<stringList_.size(); i++)
			if (stringList_[i].name == variableName)
				return ((void *) ((stringList_[i].value)));
	}

	if (variableType==COMMAND_VAR_LONG_INT || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<longIntList_.size(); i++)
			if (longIntList_[i].name == variableName)
				return ((void *) &(longIntList_[i].value));
	}

	if (variableType==COMMAND_VAR_UNSIGNED_LONG || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<uLongIntList_.size(); i++)
			if (uLongIntList_[i].name == variableName)
				return ((void *) &(uLongIntList_[i].value));
	}

	if (variableType==COMMAND_VAR_UNSIGNED_LONG_LONG || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<uLongLongIntList_.size(); i++)
			if (uLongLongIntList_[i].name == variableName)
				return ((void *) &(uLongLongIntList_[i].value));
	}

	if (variableType==COMMAND_VAR_FLOAT || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<floatList_.size(); i++)
			if (floatList_[i].name == variableName)
				return ((void *) &(floatList_[i].value));
	}

	if (variableType==COMMAND_VAR_DOUBLE || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<doubleList_.size(); i++)
			if (doubleList_[i].name == variableName)
				return ((void *) &(doubleList_[i].value));
	}

	if (variableType==COMMAND_VAR_VECTOR3 || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<vector3List_.size(); i++)
			if (vector3List_[i].name == variableName)
				return ((void *) &(vector3List_[i].value));
	}

	if (variableType==COMMAND_VAR_COLOR || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<colorList_.size(); i++)
			if (colorList_[i].name == variableName)
				return ((void *) &(colorList_[i].value));
	}

	if (variableType==COMMAND_VAR_EULER_VECTOR3 || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<eulerVector3List_.size(); i++)
			if (eulerVector3List_[i].name == variableName)
				return ((void *) &(eulerVector3List_[i].value));
	}

	if (variableType==COMMAND_VAR_MESH || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<meshList_.size(); i++)
			if (meshList_[i]->getName() == variableName)
				return ((void *) (meshList_[i]));
	}

	if (variableType==COMMAND_VAR_PDB || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<pdbList_.size(); i++)
			if (pdbList_[i]->getName() == variableName)
				return ((void *) (pdbList_[i]));
	}

	if (variableType==COMMAND_VAR_VIEW || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<viewList_.size(); i++)
			if (viewList_[i]->getName() == variableName)
				return ((void *) (viewList_[i]));
	}

	if (variableType==COMMAND_VAR_NODE || variableType==COMMAND_VAR_ALL)
	{
		for (i=0; i<nodeList_.size(); i++)
			if (nodeList_[i]->getName() == variableName)
				return ((void *) ((nodeList_[i])));
	}

	return NULL;
}

void* VmolCommand::findVariable(std::string variableName, unsigned long int *retVariableType)
{
	unsigned long int i=0;

	for (i=0; i<charList_.size(); i++)
	{
		if (charList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_CHAR;
			return ((void *) &(charList_[i].value));
		}
	}

	for (i=0; i<uCharList_.size(); i++)
	{
		if (uCharList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_CHAR;
			return ((void *) &(uCharList_[i].value));
		}
	}

	for (i=0; i<stringList_.size(); i++)
	{
		if (stringList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_STRING;
			return ((void *) ((stringList_[i].value)));
		}
	}

	for (i=0; i<longIntList_.size(); i++)
	{
		if (longIntList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_LONG_INT;
			return ((void *) &(longIntList_[i].value));
		}
	}

	for (i=0; i<uLongIntList_.size(); i++)
	{
		if (uLongIntList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_LONG;
			return ((void *) &(uLongIntList_[i].value));
		}
	}

	for (i=0; i<uLongLongIntList_.size(); i++)
	{
		if (uLongLongIntList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_LONG_LONG;
			return ((void *) &(uLongLongIntList_[i].value));
		}
	}

	for (i=0; i<floatList_.size(); i++)
	{
		if (floatList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_FLOAT;
			return ((void *) &(floatList_[i].value));
		}
	}

	for (i=0; i<doubleList_.size(); i++)
	{
		if (doubleList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_DOUBLE;
			return ((void *) &(doubleList_[i].value));
		}
	}

	for (i=0; i<vector3List_.size(); i++)
	{
		if (vector3List_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_VECTOR3;
			return ((void *) &(vector3List_[i].value));
		}
	}

	for (i=0; i<colorList_.size(); i++)
	{
		if (colorList_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_COLOR;
			return ((void *) &(colorList_[i].value));
		}
	}

	for (i=0; i<eulerVector3List_.size(); i++)
	{
		if (eulerVector3List_[i].name == variableName)
		{
			*retVariableType = COMMAND_VAR_EULER_VECTOR3;
			return ((void *) &(eulerVector3List_[i].value));
		}
	}

	for (i=0; i<meshList_.size(); i++)
	{
		if (meshList_[i]->getName() == variableName)
		{
			*retVariableType = COMMAND_VAR_MESH;
			return ((void *) (meshList_[i]));
		}
	}

	for (i=0; i<pdbList_.size(); i++)
	{
		if (pdbList_[i]->getName() == variableName)
		{
			*retVariableType = COMMAND_VAR_PDB;
			return ((void *) (pdbList_[i]));
		}
	}

	for (i=0; i<viewList_.size(); i++)
	{
		if (viewList_[i]->getName() == variableName)
		{
			*retVariableType = COMMAND_VAR_VIEW;
			return ((void *) (viewList_[i]));
		}
	}

	for (i=0; i<nodeList_.size(); i++)
	{
		if (nodeList_[i]->getName() == variableName)
		{
			*retVariableType = COMMAND_VAR_NODE;
			return ((void *) ((nodeList_[i])));
		}
	}

	return NULL;
}

std::string VmolCommand::findVariable(void *variablePointer, unsigned long int *retVariableType)
{
	unsigned long int i=0;

	for (i=0; i<charList_.size(); i++)
	{
		if (&charList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_CHAR;
			return ((charList_[i].name));
		}
	}

	for (i=0; i<uCharList_.size(); i++)
	{
		if (&uCharList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_CHAR;
			return ((uCharList_[i].name));
		}
	}

	for (i=0; i<stringList_.size(); i++)
	{
		if (&stringList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_STRING;
			return ( ((stringList_[i].name)));
		}
	}

	for (i=0; i<longIntList_.size(); i++)
	{
		if (&longIntList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_LONG_INT;
			return ((longIntList_[i].name));
		}
	}

	for (i=0; i<uLongIntList_.size(); i++)
	{
		if (&uLongIntList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_LONG;
			return ((uLongIntList_[i].name));
		}
	}

	for (i=0; i<uLongLongIntList_.size(); i++)
	{
		if (&uLongLongIntList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_UNSIGNED_LONG_LONG;
			return ((uLongLongIntList_[i].name));
		}
	}

	for (i=0; i<floatList_.size(); i++)
	{
		if (&floatList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_FLOAT;
			return ((floatList_[i].name));
		}
	}

	for (i=0; i<doubleList_.size(); i++)
	{
		if (&doubleList_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_DOUBLE;
			return ((doubleList_[i].name));
		}
	}

	for (i=0; i<vector3List_.size(); i++)
	{
		if (&vector3List_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_VECTOR3;
			return ((vector3List_[i].name));
		}
	}

//	printf ("variablePointer = %ld\n", (long int) variablePointer);

	for (i=0; i<colorList_.size(); i++)
	{
		if (((void *) &(colorList_[i].value)) == variablePointer)
		{
			*retVariableType = COMMAND_VAR_COLOR;
			return ((colorList_[i].name));
		}
	}

	for (i=0; i<eulerVector3List_.size(); i++)
	{
		if (&eulerVector3List_[i].value == variablePointer)
		{
			*retVariableType = COMMAND_VAR_EULER_VECTOR3;
			return ((eulerVector3List_[i].name));
		}
	}

	for (i=0; i<meshList_.size(); i++)
	{
		if (meshList_[i] == variablePointer)
		{
			*retVariableType = COMMAND_VAR_MESH;
			return ((meshList_[i])->getName());
		}
	}

	for (i=0; i<pdbList_.size(); i++)
	{
		if (pdbList_[i] == variablePointer)
		{
			*retVariableType = COMMAND_VAR_PDB;
			return ((pdbList_[i])->getName());
		}
	}

	for (i=0; i<viewList_.size(); i++)
	{
		if (viewList_[i] == variablePointer)
		{
			*retVariableType = COMMAND_VAR_VIEW;
			return ((viewList_[i])->getName());
		}
	}





	for (i=0; i<nodeList_.size(); i++)
	{
		if (nodeList_[i] == variablePointer)
		{
			*retVariableType = COMMAND_VAR_NODE;
			return (((nodeList_[i]))->getName());
		}
	}

	return "";
}

int VmolCommand::loadScript(std::string scriptPath, bool outputToLog)
{
	string buffer;
	ifstream input(scriptPath.c_str());

	if (input == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", scriptPath.c_str());
		return 1;
	}

	while (getline(input, buffer))
	{

//		printf ("naredba = %s\n", buffer.c_str());

		executeCommand(buffer, outputToLog);
	}

	return 0;
}

string VmolCommand::handleSpecialCharacters(string commandString)
{
	bool isTemplate=false;
	unsigned int i=0;
	int position=0;
	string ret="", tempRet="", templateString="";
	string *templateParam=NULL;

	ret = commandString;

	position = commandString.find("%");



	isTemplate = false;
	templateString = "";
	tempRet = "";
	for (i=0; i<commandString.size(); i++)
	{
		if (commandString[i] == '\\')
		{
			continue;
		}

		if (i>0 && commandString[i-1]=='\\')
		{
//			if (commandString[i] == '
//			tempRet[tempRet.size()-1] = commandString[i];
			tempRet += commandString[i];
//			continue;
		}
		else
		{
			if (commandString[i]==':' && (i==0 || (i>0 && commandString[i-1]!='\\')) && isTemplate==false)
			{
				isTemplate = true;
				templateString = "";
			}
			else if ((commandString[i]==' ' || isalnum(commandString[i])==0) && isTemplate==true)
			{
				isTemplate = false;

				string retTemplate;
				handleTemplates(templateString, &retTemplate);

				tempRet += retTemplate;
				tempRet += commandString[i];
			}
			else if (commandString[i]=='%' && (i==0 || (i>0 && commandString[i-1]!='\\')))
			{
				if (isTemplate == true)
				{
					isTemplate = false;

					string retTemplate;
					handleTemplates(templateString, &retTemplate);

					tempRet += retTemplate;
				}

				break;
			}
			else
			{
				if (isTemplate == true)
				{
					templateString += commandString[i];
				}
				else if (isTemplate == false)
				{
					tempRet += commandString[i];
				}
			}
		}
	}

//	printf ("special: %s>%d\n", tempRet.c_str(), tempRet.size());

	ret = tempRet;

	return ret;
}

vector<string> VmolCommand::splitWords(string inputString)
{
	unsigned int i=0;
	string parameterString;
	vector<string> ret;

	ret.clear();
	for (i=0; i<inputString.size(); i++)
	{
		if (inputString[i]!=' ' && inputString[i]!='\t' && inputString[i]!='\n')
			parameterString += inputString[i];
		else
		{
			if (parameterString.size() > 0)
			{
				ret.push_back(parameterString);
			}

			parameterString = "";
		}
	}

	if (parameterString.size() > 0)
	{
		ret.push_back(parameterString);
	}

	return ret;
}


std::vector< VariableName<char> >& VmolCommand::getCharList()
{
	return charList_;
}

std::vector< VariableName<unsigned char> >& VmolCommand::getUCharList()
{
	return uCharList_;
}

std::vector< VariableName<long int> >& VmolCommand::getLongIntList()
{
	return longIntList_;
}

std::vector< VariableName<unsigned long int> >& VmolCommand::getULongIntList()
{
	return uLongIntList_;
}

std::vector< VariableName<unsigned long long int> >& VmolCommand::getULongLongIntList()
{
	return uLongLongIntList_;
}

std::vector< VariableName<float> >& VmolCommand::getFloatList()
{
	return floatList_;
}

std::vector< VariableName<double> >& VmolCommand::getDoubleList()
{
	return doubleList_;
}

std::vector< VariableName<Vector3> >& VmolCommand::getVector3List()
{
	return vector3List_;
}

std::vector< VariableName<Color> >& VmolCommand::getColorList()
{
	return colorList_;
}

std::vector< VariableName<EulerVector3> >& VmolCommand::getEulerVector3List()
{
	return eulerVector3List_;
}

std::vector< VariableName<std::string *> >& VmolCommand::getStringList()
{
	return stringList_;
}

std::vector<Mesh *>& VmolCommand::getMeshList()
{
	return meshList_;
}

std::vector<PdbFile *>& VmolCommand::getPdbList()
{
	return pdbList_;
}

std::vector<VmolView *>& VmolCommand::getViewList()
{
	return viewList_;
}

std::vector<VmolSceneNode *>& VmolCommand::getNodeList()
{
	return nodeList_;
}

ScoreLoader& VmolCommand::getScoresData()
{
	return scoresData_;
}

std::vector<VmolSceneNode *>& VmolCommand::getRootNodes()
{
	return rootNodes_;
}

unsigned long long int VmolCommand::getVariableTypeFromString(std::string variableType)
{
	if (variableType == "char")
		return COMMAND_VAR_CHAR;
	else if (variableType == "uchar")
		return COMMAND_VAR_UNSIGNED_CHAR;
	else if (variableType == "long")
		return COMMAND_VAR_LONG_INT;
	else if (variableType == "ulong")
		return COMMAND_VAR_UNSIGNED_LONG;
	else if (variableType == "ulonglong")
		return COMMAND_VAR_UNSIGNED_LONG_LONG;
	else if (variableType == "float")
		return COMMAND_VAR_FLOAT;
	else if (variableType == "double")
		return COMMAND_VAR_DOUBLE;
	else if (variableType == "vector3")
		return COMMAND_VAR_VECTOR3;
	else if (variableType == "color")
		return COMMAND_VAR_COLOR;
	else if (variableType == "eulervector3")
		return COMMAND_VAR_EULER_VECTOR3;
	else if (variableType == "string")
		return COMMAND_VAR_STRING;
	else if (variableType == "mesh")
		return COMMAND_VAR_MESH;
	else if (variableType == "pdb")
		return COMMAND_VAR_PDB;
	else if (variableType == "node")
		return COMMAND_VAR_NODE;
	else if (variableType == "view")
		return COMMAND_VAR_VIEW;

	return 0;
}

string VmolCommand::getVariableTypeFromInt(unsigned long int variableType)
{
	if (variableType == COMMAND_VAR_CHAR)
		return ((string) "char");
	else if (variableType == COMMAND_VAR_UNSIGNED_CHAR)
		return ((string) "uchar");
	else if (variableType == COMMAND_VAR_LONG_INT)
		return ((string) "long");
	else if (variableType == COMMAND_VAR_UNSIGNED_LONG)
		return ((string) "ulong");
	else if (variableType == COMMAND_VAR_UNSIGNED_LONG_LONG)
		return ((string) "ulonglong");
	else if (variableType == COMMAND_VAR_FLOAT)
		return ((string) "float");
	else if (variableType == COMMAND_VAR_DOUBLE)
		return ((string) "double");
	else if (variableType == COMMAND_VAR_VECTOR3)
		return ((string) "vector3");
	else if (variableType == COMMAND_VAR_COLOR)
		return ((string) "color");
	else if (variableType == COMMAND_VAR_EULER_VECTOR3)
		return ((string) "eulervector3");
	else if (variableType == COMMAND_VAR_STRING)
		return ((string) "string");
	else if (variableType == COMMAND_VAR_MESH)
		return ((string) "mesh");
	else if (variableType == COMMAND_VAR_PDB)
		return ((string) "pdb");
	else if (variableType == COMMAND_VAR_NODE)
		return ((string) "node");
	else if (variableType == COMMAND_VAR_VIEW)
		return ((string) "view");

	return ((string) "");
}

int VmolCommand::exportCommandHistory(std::string path)
{
	unsigned int i=0;
	FILE *fp;

	fp = fopen(path.c_str(), "w");
	if (fp == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", path.c_str());
		return 1;
	}

	for (i=0; i<commandHistory_.size(); i++)
	{
		fprintf (fp, "%s\n", commandHistory_[i].c_str());
	}

	fclose(fp);

	return 0;
}

std::vector<std::string>& VmolCommand::getCommandHistory()
{
	return commandHistory_;
}
