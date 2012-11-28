/*
 * vmolcommand.h
 *
 *  Created on: Apr 4, 2010
 *      Author: ivan
 */

#ifndef VMOLCOMMAND_H_
#define VMOLCOMMAND_H_

#include <string>
#include <vector>
#include "../pdbparser/pdbparser.h"
#include "../objects/mesh.h"
#include "../gui/glwindow.h"
#include "../pdbwriter/scoreloader.h"

#include "commanddefinitions.h"

class CommandParameter;



class CommandParameter
{
public:
	std::string parameter;
	std::string value;

	CommandParameter()
	{
		parameter = value = "";
	}
};

template <class T>
class VariableName
{
public:
	T value;
	std::string name;
};


class VmolCommand
{
public:
	VmolCommand();
	~VmolCommand();

	static VmolCommand* getInstance();

	void init();
	void initCommands();
	int executeCommand(std::string commandString, bool outputToLog=true);
	int parseCommandString(std::string commandString);
	vector<string> splitWords(string inputString);

//	PdbFile* findPdbByName(std::string pdbName);
//	Mesh* findMeshByName(std::string meshName);
	void* findVariable(unsigned long int variableType, std::string variableName);			// return pointer must be cast to desired variable type
	void* findVariable(std::string variableName, unsigned long int *retVariableType);
	std::string findVariable(void *variablePointer, unsigned long int *retVariableType);
	int checkSyntax(std::vector<CommandParameter> commandVector);
//	std::vector<VmolView *>& getViewList();
	int exportCommandHistory(std::string path);

	int loadScript(std::string scriptPath, bool outputToLog=true);

	std::vector< VariableName<char> >& getCharList();
	std::vector< VariableName<unsigned char> >& getUCharList();
	std::vector< VariableName<long int> >& getLongIntList();
	std::vector< VariableName<unsigned long int> >& getULongIntList();
	std::vector< VariableName<unsigned long long int> >& getULongLongIntList();
	std::vector< VariableName<float> >& getFloatList();
	std::vector< VariableName<double> >& getDoubleList();
	std::vector< VariableName<Vector3> >& getVector3List();
	std::vector< VariableName<Color> >& getColorList();
	std::vector< VariableName<EulerVector3> >& getEulerVector3List();
	std::vector< VariableName<std::string *> >& getStringList();
	std::vector<Mesh *>& getMeshList();
	std::vector<PdbFile *>& getPdbList();
	std::vector<VmolView *>& getViewList();
	std::vector<VmolSceneNode *>& getNodeList();
	ScoreLoader &getScoresData();
	std::vector<VmolSceneNode *>& getRootNodes();
	std::vector<std::string>& getCommandHistory();

	unsigned long long int getVariableTypeFromString(std::string variableType);
	std::string getVariableTypeFromInt(unsigned long int variableType);



	int handleTemplates(string templateName, string *templateValue);

private:
	static VmolCommand* singleInstance_;

	std::vector<std::string> commandHistory_;

	// variables available to the user
	std::vector< VariableName<char> > charList_;
	std::vector< VariableName<unsigned char> > uCharList_;
	std::vector< VariableName<long int> > longIntList_;
	std::vector< VariableName<unsigned long int> > uLongIntList_;
	std::vector< VariableName<unsigned long long int> > uLongLongIntList_;
	std::vector< VariableName<float> > floatList_;
	std::vector< VariableName<double> > doubleList_;
	std::vector< VariableName<Vector3> > vector3List_;
	std::vector< VariableName<Color> > colorList_;
	std::vector< VariableName<EulerVector3> > eulerVector3List_;
	std::vector< VariableName<std::string *> > stringList_;
	std::vector<Mesh *> meshList_;
	std::vector<PdbFile *> pdbList_;
	std::vector<VmolView *> viewList_;
	std::vector<VmolSceneNode *> nodeList_;

	// list of all available commands
	std::vector<std::string> commandList_;
	std::vector<std::string> subCommandList_;
	std::vector<std::string> parameterList_;

	std::vector<VmolSceneNode *> rootNodes_;

	ScoreLoader scoresData_;




	int splitAndExecute(std::string commandString, bool outputToLog=true);
	int executeCommand(std::vector<CommandParameter> commandVector, bool outputToLog=true);

	std::string handleSpecialCharacters(std::string commandString);

	int handleCommands(std::vector<CommandParameter> commandVector);
	int handleCommandCreate(std::vector<CommandParameter> commandVector);
	int handleCommandChange(std::vector<CommandParameter> commandVector);
	int handleCommandRemove(std::vector<CommandParameter> commandVector);
	int handleCommandRun(std::vector<CommandParameter> commandVector);
	int handleCommandMath(std::vector<CommandParameter> commandVector);

	int handleSubcommandCreatePdb(std::vector<CommandParameter> commandVector);
	int handleSubcommandCreateMesh(std::vector<CommandParameter> commandVector);
	int handleSubcommandCreateNode(std::vector<CommandParameter> commandVector);
	int handleSubcommandCreateVariable(std::vector<CommandParameter> commandVector);
	int handleSubcommandCreateView(std::vector<CommandParameter> commandVector);
	int handleSubcommandCreateMs(std::vector<CommandParameter> commandVector);

	int handleSubcommandChangeNode(Parameters params, VmolSceneNode *changeNode);

	Parameters handleParameters(vector<CommandParameter> commandVector);



	std::string trimFileName(std::string path);
	VmolSceneNode* findParentNodeRecursion(VmolSceneNode *currentNode, string nodeName);
};

#endif /* VMOLCOMMAND_H_ */
