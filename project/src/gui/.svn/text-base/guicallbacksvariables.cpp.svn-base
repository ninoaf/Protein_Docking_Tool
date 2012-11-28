/*
 * guicallbacksvariables.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: ivan
 */

#include "vmolgui.h"
#include "../command/vmolcommand.h"

using namespace std;



void VmolGui::callbackVariablesScalar(Fl_Widget *w, void *data)
{
	char tempChar[100];
	unsigned int i=0;
	void *variablePointer=NULL;
	unsigned long int selectedTypeInt=0;
	string selectedName, selectedType, retString;

	if (VmolGui::getInstance()->variablesScalar_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesScalar_->text(VmolGui::getInstance()->variablesScalar_->value());

	variablePointer = VmolCommand::getInstance()->findVariable(selectedName, &selectedTypeInt);
	selectedType = VmolCommand::getInstance()->getVariableTypeFromInt(selectedTypeInt);

	VmolGui::getInstance()->variablesScalarName_->value(selectedName.c_str());
	for (i=0; i<VmolGui::getInstance()->variablesScalarType_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesScalarType_->text(i)) == selectedType)
		{
			VmolGui::getInstance()->variablesScalarType_->value(i);
			break;
		}
	}

	if (selectedType == "vector3")
	{
		sprintf (tempChar, "%.2lf", ((Vector3 *) variablePointer)->x);
		VmolGui::getInstance()->variablesValueX_->value(tempChar);

		sprintf (tempChar, "%.2lf", ((Vector3 *) variablePointer)->y);
		VmolGui::getInstance()->variablesValueY_->value(tempChar);

		sprintf (tempChar, "%.2lf", ((Vector3 *) variablePointer)->z);
		VmolGui::getInstance()->variablesValueZ_->value(tempChar);

		VmolGui::getInstance()->variablesValueW_->value("");
	}
	else if (selectedType == "color")
	{
		sprintf (tempChar, "%u", ((Color *) variablePointer)->r);
		VmolGui::getInstance()->variablesValueX_->value(tempChar);

		sprintf (tempChar, "%u", ((Color *) variablePointer)->g);
		VmolGui::getInstance()->variablesValueY_->value(tempChar);

		sprintf (tempChar, "%u", ((Color *) variablePointer)->b);
		VmolGui::getInstance()->variablesValueZ_->value(tempChar);

		sprintf (tempChar, "%u", ((Color *) variablePointer)->a);
		VmolGui::getInstance()->variablesValueW_->value(tempChar);
	}
	else if (selectedType == "eulervector3")
	{
		sprintf (tempChar, "%.2lf", ((EulerVector3 *) variablePointer)->alpha);
		VmolGui::getInstance()->variablesValueX_->value(tempChar);

		sprintf (tempChar, "%.2lf", ((EulerVector3 *) variablePointer)->beta);
		VmolGui::getInstance()->variablesValueY_->value(tempChar);

		sprintf (tempChar, "%.2lf", ((EulerVector3 *) variablePointer)->gamma);
		VmolGui::getInstance()->variablesValueZ_->value(tempChar);

		VmolGui::getInstance()->variablesValueW_->value("");
	}
	else
	{
		VmolCommand::getInstance()->handleTemplates(selectedName, &retString);
		VmolGui::getInstance()->variablesValueX_->value(retString.c_str());
	}
}

void VmolGui::callbackVariablesChangeScalar(Fl_Widget *w, void *data)
{
	char tempChar[200];
	string selectedName, newName, newValue;
	string commandString;

	if (VmolGui::getInstance()->variablesScalar_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesScalar_->text(VmolGui::getInstance()->variablesScalar_->value());
	newName = VmolGui::getInstance()->variablesScalarName_->value();
	sprintf (tempChar, "%s %s %s %s", VmolGui::getInstance()->variablesValueX_->value(), VmolGui::getInstance()->variablesValueY_->value(), VmolGui::getInstance()->variablesValueZ_->value(), VmolGui::getInstance()->variablesValueW_->value());
	newValue = tempChar;

	commandString = "change " + selectedName + " name={" + newName + "} value={" + newValue + "}";
	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesCreateScalar(Fl_Widget *w, void *data)
{
	char tempChar[200];
	string selectedName, newName, newType, newValue;
	string commandString;

	newName = VmolGui::getInstance()->variablesScalarName_->value();
	newType = VmolGui::getInstance()->variablesScalarType_->text(VmolGui::getInstance()->variablesScalarType_->value());

	sprintf (tempChar, "%s %s %s %s", VmolGui::getInstance()->variablesValueX_->value(), VmolGui::getInstance()->variablesValueY_->value(), VmolGui::getInstance()->variablesValueZ_->value(), VmolGui::getInstance()->variablesValueW_->value());
	newValue = tempChar;

	commandString = "create variable name={" + newName + "} type={" + newType + "} value={" + newValue + "}";

	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesRemoveScalar(Fl_Widget *w, void *data)
{
	string selectedName;
	string commandString;

	if (VmolGui::getInstance()->variablesScalar_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesScalar_->text(VmolGui::getInstance()->variablesScalar_->value());

	commandString = "remove " + selectedName;
	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesMesh(Fl_Widget *w,void *data)
{
	char tempChar[100];
	unsigned int i=0;
	Mesh *variablePointer=NULL;
	unsigned long int selectedTypeInt=0;
	string selectedName, selectedType, retString;

	if (VmolGui::getInstance()->variablesMesh_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesMesh_->text(VmolGui::getInstance()->variablesMesh_->value());

	variablePointer = (Mesh *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_MESH, selectedName);

	VmolGui::getInstance()->variablesMeshName_->value(selectedName.c_str());
	VmolGui::getInstance()->variablesMeshPath_->value(variablePointer->getPath().c_str());

	sprintf (tempChar, "%.2lf", variablePointer->getAutoScale());
	VmolGui::getInstance()->variablesMeshAutoscale_->value(tempChar);

	if (variablePointer->getMeshType() == "dat")
		VmolGui::getInstance()->variablesMeshType_->value(0);
	else if (variablePointer->getMeshType() == "grid")
		VmolGui::getInstance()->variablesMeshType_->value(1);
	else if (variablePointer->getMeshType() == "ms")
		VmolGui::getInstance()->variablesMeshType_->value(2);

	if (variablePointer->getCentered() == false)
		VmolGui::getInstance()->variablesMeshCenter_->value(0);
	else if (variablePointer->getCentered() == true)
		VmolGui::getInstance()->variablesMeshCenter_->value(1);

	if (variablePointer->getAutoIsoValue() == false)
		VmolGui::getInstance()->variablesMeshAutoIsovalue_->value(0);
	else if (variablePointer->getAutoIsoValue() == true)
		VmolGui::getInstance()->variablesMeshAutoIsovalue_->value(1);

	sprintf (tempChar, "%.2lf", variablePointer->getGridIsoValue());
	VmolGui::getInstance()->variablesMeshIsovalue_->value(tempChar);

	for (i=0; i<VmolGui::getInstance()->variablesMeshAssignNode_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesMeshAssignNode_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesMeshAssignNode_->value(i);
			break;
		}
	}

	for (i=0; i<VmolGui::getInstance()->variablesMeshNodeMode_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesMeshNodeMode_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesMeshNodeMode_->value(i);
			break;
		}
	}
}

void VmolGui::callbackVariablesChangeMesh(Fl_Widget *w,void *data)
{
	char tempChar[200];
	string selectedName, newName, newPath, newType, newCenter, newAutoIsovalue, newIsovalue, newAutoscale;
	string commandString;

	if (VmolGui::getInstance()->variablesMesh_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesMesh_->text(VmolGui::getInstance()->variablesMesh_->value());
	newName = VmolGui::getInstance()->variablesMeshName_->value();
	newPath = VmolGui::getInstance()->variablesMeshPath_->value();
	newType = VmolGui::getInstance()->variablesMeshType_->text(VmolGui::getInstance()->variablesMeshType_->value());
	newCenter = VmolGui::getInstance()->variablesMeshCenter_->text(VmolGui::getInstance()->variablesMeshCenter_->value());
	newAutoIsovalue = VmolGui::getInstance()->variablesMeshAutoIsovalue_->text(VmolGui::getInstance()->variablesMeshAutoIsovalue_->value());
	newIsovalue = VmolGui::getInstance()->variablesMeshIsovalue_->value();
	newAutoscale = VmolGui::getInstance()->variablesMeshAutoscale_->value();

	commandString = "change " + selectedName + " name={" + newName + "} path={" + newPath +
					"} type={" + newType + "} center={" + newCenter + "} autoScale={" + newAutoscale + "} ";

	if (newType == "grid")
	{
		commandString = commandString + "value={" + newAutoIsovalue + " " + newIsovalue + "}";
	}

	printf ("commandString = %s\n", commandString.c_str());

	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesCreateMesh(Fl_Widget *w, void *data)
{
	char tempChar[200];
	string selectedName, newName, newPath, newType, newCenter, newAutoIsovalue, newIsovalue, newAutoscale;
	string newNodeMode, newAssignNode;
	string commandString;

	newName = VmolGui::getInstance()->variablesMeshName_->value();
	newPath = VmolGui::getInstance()->variablesMeshPath_->value();
	newType = VmolGui::getInstance()->variablesMeshType_->text(VmolGui::getInstance()->variablesMeshType_->value());
	newCenter = VmolGui::getInstance()->variablesMeshCenter_->text(VmolGui::getInstance()->variablesMeshCenter_->value());
	newAutoIsovalue = VmolGui::getInstance()->variablesMeshAutoIsovalue_->text(VmolGui::getInstance()->variablesMeshAutoIsovalue_->value());
	newIsovalue = VmolGui::getInstance()->variablesMeshIsovalue_->value();
	newAutoscale = VmolGui::getInstance()->variablesMeshAutoscale_->value();
	newNodeMode = VmolGui::getInstance()->variablesMeshNodeMode_->text(VmolGui::getInstance()->variablesMeshNodeMode_->value());
	newAssignNode = VmolGui::getInstance()->variablesMeshAssignNode_->text(VmolGui::getInstance()->variablesMeshAssignNode_->value());

	commandString = "create mesh name={" + newName + "} path={" + newPath +
					"} type={" + newType + "} center={" + newCenter + "} autoScale={" + newAutoscale + "} ";

	if (newType == "grid")
	{
		commandString = commandString + "value={" + newAutoscale + " " + newIsovalue + "}";
	}

	VmolCommand::getInstance()->executeCommand(commandString);


	if (newNodeMode!="(unknown)" && newAssignNode!="(unknown)")
	{
		commandString = "create node name={mesh" + newName + "} nodeType={mesh} nodeParams={" +
						newName + " " + newNodeMode + "} parent={" + newAssignNode + "}";

		VmolCommand::getInstance()->executeCommand(commandString);
	}

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesRemoveMesh(Fl_Widget *w, void *data)
{
	string selectedName;
	string commandString;

	if (VmolGui::getInstance()->variablesMesh_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesMesh_->text(VmolGui::getInstance()->variablesMesh_->value());

	commandString = "remove " + selectedName;
	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesMeshPathPick(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Open mesh file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->variablesMeshPath_->value(newFileChooser.value());
	}
}



void VmolGui::callbackVariablesPdb(Fl_Widget *w, void *data)
{
	char tempChar[100];
	unsigned int i=0;
	PdbFile *variablePointer=NULL;
	unsigned long int selectedTypeInt=0;
	string selectedName, selectedType, retString;

	if (VmolGui::getInstance()->variablesPdb_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesPdb_->text(VmolGui::getInstance()->variablesPdb_->value());
	variablePointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, selectedName);

	VmolGui::getInstance()->variablesPdbName_->value(selectedName.c_str());
	VmolGui::getInstance()->variablesPdbPath_->value(variablePointer->getFileName().c_str());
	VmolGui::getInstance()->variablesPdbRadiusPath_->value(variablePointer->getRadiusPath().c_str());

	if (variablePointer->getUseUnitedRadius() == true)
		VmolGui::getInstance()->variablesPdbRadiusType_->value(0);
	else if (variablePointer->getUseUnitedRadius() == false)
		VmolGui::getInstance()->variablesPdbRadiusType_->value(1);

	if (variablePointer->getCentered() == false)
		VmolGui::getInstance()->variablesPdbCenter_->value(0);
	else if (variablePointer->getCentered() == true)
		VmolGui::getInstance()->variablesPdbCenter_->value(1);

	if (variablePointer->getCenterAtomsArithmetically()==false && variablePointer->getCenterAtomsByMass()==true)
		VmolGui::getInstance()->variablesPdbCenterType_->value(0);
	else if (variablePointer->getCenterAtomsArithmetically()==true && variablePointer->getCenterAtomsByMass()==false)
		VmolGui::getInstance()->variablesPdbCenterType_->value(1);
	else if (variablePointer->getCenterAtomsArithmetically()==false && variablePointer->getCenterAtomsByMass()==false)
		VmolGui::getInstance()->variablesPdbCenterType_->value(2);

	for (i=0; i<VmolGui::getInstance()->variablesPdbAssignNode_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesPdbAssignNode_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesPdbAssignNode_->value(i);
			break;
		}
	}

	for (i=0; i<VmolGui::getInstance()->variablesPdbNodeMode_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesPdbNodeMode_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesPdbNodeMode_->value(i);
			break;
		}
	}

	for (i=0; i<VmolGui::getInstance()->variablesPdbSphereMesh_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesPdbSphereMesh_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesPdbSphereMesh_->value(i);
			break;
		}
	}

	for (i=0; i<VmolGui::getInstance()->variablesPdbStickMesh_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->variablesPdbStickMesh_->text(i)) == ((string) "(unknown)"))
		{
			VmolGui::getInstance()->variablesPdbStickMesh_->value(i);
			break;
		}
	}
}

void VmolGui::callbackVariablesChangePdb(Fl_Widget *w, void *data)
{
	char tempChar[200];
	string selectedName, newName, newPath, newRadiusPath, newRadiusType, newCenter, newCenterType;
	string commandString;

	if (VmolGui::getInstance()->variablesPdb_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesPdb_->text(VmolGui::getInstance()->variablesPdb_->value());
	newName = VmolGui::getInstance()->variablesPdbName_->value();
	newPath = VmolGui::getInstance()->variablesPdbPath_->value();
	newRadiusPath = VmolGui::getInstance()->variablesPdbRadiusPath_->value();
	newRadiusType = VmolGui::getInstance()->variablesPdbRadiusType_->text(VmolGui::getInstance()->variablesPdbRadiusType_->value());
	newCenter = VmolGui::getInstance()->variablesPdbCenter_->text(VmolGui::getInstance()->variablesPdbCenter_->value());
	newCenterType = VmolGui::getInstance()->variablesPdbCenterType_->text(VmolGui::getInstance()->variablesPdbCenterType_->value());

	if (newCenterType == "arithmetic")
		newCenterType = "arithmetic";

	commandString = "change " + selectedName + " name={" + newName + "} path={" + newPath +
					"} radiusPath={" + newRadiusPath + "} radiusType={" + newRadiusType +
					"} center={" + newCenter + "} centerType={" + newCenterType + "}";

	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesCreatePdb(Fl_Widget *w, void *data)
{
	char tempChar[200];
	string selectedName, newName, newPath, newRadiusPath, newRadiusType, newCenter, newCenterType;
	string newNodeMode, newAssignNode, newSphereMesh, newStickMesh;
	string commandString;

	newName = VmolGui::getInstance()->variablesPdbName_->value();
	newPath = VmolGui::getInstance()->variablesPdbPath_->value();
	newRadiusPath = VmolGui::getInstance()->variablesPdbRadiusPath_->value();
	newRadiusType = VmolGui::getInstance()->variablesPdbRadiusType_->text(VmolGui::getInstance()->variablesPdbRadiusType_->value());
	newCenter = VmolGui::getInstance()->variablesPdbCenter_->text(VmolGui::getInstance()->variablesPdbCenter_->value());
	newCenterType = VmolGui::getInstance()->variablesPdbCenterType_->text(VmolGui::getInstance()->variablesPdbCenterType_->value());
	newNodeMode = VmolGui::getInstance()->variablesPdbNodeMode_->text(VmolGui::getInstance()->variablesPdbNodeMode_->value());
	newAssignNode = VmolGui::getInstance()->variablesPdbAssignNode_->text(VmolGui::getInstance()->variablesPdbAssignNode_->value());
	newSphereMesh = VmolGui::getInstance()->variablesPdbSphereMesh_->text(VmolGui::getInstance()->variablesPdbSphereMesh_->value());
	newStickMesh = VmolGui::getInstance()->variablesPdbStickMesh_->text(VmolGui::getInstance()->variablesPdbStickMesh_->value());

	if (newCenterType == "arithmetic")
		newCenterType = "arithmetic";

	commandString = "create pdb name={" + newName + "} path={" + newPath +
					"} radiusPath={" + newRadiusPath + "} radiusType={" + newRadiusType +
					"} center={" + newCenter + "} centerType={" + newCenterType + "}";

	VmolCommand::getInstance()->executeCommand(commandString);

	if (newNodeMode!="(unknown)" && newAssignNode!="(unknown)" && newSphereMesh!="(unknown)" && newStickMesh!="(unknown)")
	{
		commandString = "create node name={node" + newName + "} nodeType={pdb} nodeParams={" +
						newName + " " + newSphereMesh + " " + newStickMesh + " " + newNodeMode + "} parent={" + newAssignNode + "}";

		VmolCommand::getInstance()->executeCommand(commandString);
	}

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesRemovePdb(Fl_Widget *w, void *data)
{
	string selectedName;
	string commandString;

	if (VmolGui::getInstance()->variablesPdb_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesPdb_->text(VmolGui::getInstance()->variablesPdb_->value());

	commandString = "remove " + selectedName;
	VmolCommand::getInstance()->executeCommand(commandString);
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackVariablesPdbPathPick(Fl_Widget *w, void *data)
{
	unsigned int i=0;

	Fl_File_Chooser newFileChooser(".", "*.pdb", Fl_File_Chooser::SINGLE, "Open PDB file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->variablesPdbPath_->value(newFileChooser.value());
	}



	if (VmolGui::getInstance()->variablesPdbSphereMesh_->value() == 0)
	{
		for (i=0; i<VmolGui::getInstance()->variablesPdbSphereMesh_->size(); i++)
		{
			if (((string) VmolGui::getInstance()->variablesPdbSphereMesh_->text(i)) == ((string) "sphere"))
			{
				VmolGui::getInstance()->variablesPdbSphereMesh_->value(i);
				break;
			}
		}
	}

	if (VmolGui::getInstance()->variablesPdbStickMesh_->value() == 0)
	{
		for (i=0; i<VmolGui::getInstance()->variablesPdbStickMesh_->size(); i++)
		{
			if (((string) VmolGui::getInstance()->variablesPdbStickMesh_->text(i)) == ((string) "stick"))
			{
				VmolGui::getInstance()->variablesPdbStickMesh_->value(i);
				break;
			}
		}
	}

	if (VmolGui::getInstance()->variablesPdbAssignNode_->size() > 1)
	{
		if (VmolGui::getInstance()->variablesPdbAssignNode_->value() == 0)
			VmolGui::getInstance()->variablesPdbAssignNode_->value(1);
	}

	if (VmolGui::getInstance()->variablesPdbNodeMode_->size() > 1)
	{
		if (VmolGui::getInstance()->variablesPdbNodeMode_->value() == 0)
			VmolGui::getInstance()->variablesPdbNodeMode_->value(1);
	}

}

void VmolGui::callbackVariablesPdbCreateMs(Fl_Widget *w, void *data)
{
	char tempChar1[200], tempChar2[200], tempChar3[200], tempChar4[200];
	string parentName;
	string selectedName, path;
	string commandString;

	if (VmolGui::getInstance()->variablesPdb_->value() < 1)
	{
		return;
	}

	selectedName = VmolGui::getInstance()->variablesPdb_->text(VmolGui::getInstance()->variablesPdb_->value());
	sprintf (tempChar4, "data/ms/ms%s", selectedName.c_str());
	path = tempChar4;



	sprintf (tempChar3, "nodeModeMs%s%d", selectedName.c_str(), VmolCommand::getInstance()->getULongLongIntList().size());
	commandString = "create variable name={" + ((string) tempChar3) + "} type={ulonglong} value={0x0001000000001105}";
	VmolCommand::getInstance()->executeCommand(commandString);

	commandString = "create ms name={" + selectedName + "} path={" + path + "} value={" + ((string) tempChar3) + "}";
	VmolCommand::getInstance()->executeCommand(commandString);

	sprintf (tempChar1, "meshMs%s%d", selectedName.c_str(), VmolCommand::getInstance()->getPdbList().size());
	commandString = "create mesh name={" + ((string) tempChar1) + "} type={ms} path={" + path + ".atc} center={false} autoScale={0.0}";
	VmolCommand::getInstance()->executeCommand(commandString);

	if (VmolGui::getInstance()->variablesPdbAssignNode_->value() > 0)
	{
		parentName = VmolGui::getInstance()->variablesPdbAssignNode_->text(VmolGui::getInstance()->variablesPdbAssignNode_->value());

		sprintf (tempChar2, "nodeMs%s%d", selectedName.c_str(), VmolCommand::getInstance()->getNodeList().size());

		commandString = "create node name={" + ((string) tempChar2) + "} nodeType={mesh} nodeParams={" + ((string) tempChar1) + " " + ((string) tempChar3) + "} parent={" + parentName + "}";
		VmolCommand::getInstance()->executeCommand(commandString);
	}

	VmolGui::getInstance()->refreshGui();
}
