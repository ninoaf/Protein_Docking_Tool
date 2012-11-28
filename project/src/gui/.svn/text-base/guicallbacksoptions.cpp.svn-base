/*
 * guicallbacksoptions.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: ivan
 */

#include "vmolgui.h"
#include "../command/vmolcommand.h"

using namespace std;



void VmolGui::callbackOptionsView(Fl_Widget *w, void *data)
{
/*
	int optionIndex=0;
	void *variablePointer=NULL;
	unsigned long int variableType=0;
	string variableName;
	Fl_Choice *choice=NULL;

	choice = (Fl_Choice *) VmolGui::getInstance()->optionsMouseBinds_;

	variableName = choice->text(choice->value());

	optionIndex = VmolGui::getInstance()->optionsMouseButton_->value() * 2;			// * 2 because there are two actions for every button (left-right and up-down)
	optionIndex += VmolGui::getInstance()->optionsMouseAction_->value();			// increments option index for this value, because value() is equal to 0 or 1 - if it's 0, it already points to the left-right action

	variablePointer = VmolCommand::getInstance()->findVariable(variableName, &variableType);
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->getMouseEventBinds().variable[optionIndex] = variablePointer;
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->getMouseEventBinds().variableType[optionIndex] = variableType;
*/

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackOptionsMouseBinds(Fl_Widget *w, void *data)
{
	int optionIndex=0;
	void *variablePointer=NULL;
	unsigned long int variableType=0;
	string variableName;
	Fl_Choice *choice=NULL;

	choice = (Fl_Choice *) data;

	variableName = choice->text(choice->value());

	optionIndex = VmolGui::getInstance()->optionsMouseButton_->value() * 2;			// * 2 because there are two actions for every button (left-right and up-down)
	optionIndex += VmolGui::getInstance()->optionsMouseAction_->value();			// increments option index for this value, because value() is equal to 0 or 1 - if it's 0, it already points to the left-right action

	variablePointer = VmolCommand::getInstance()->findVariable(variableName, &variableType);
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->getMouseEventBinds().variable[optionIndex] = variablePointer;
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->getMouseEventBinds().variableType[optionIndex] = variableType;
}

void VmolGui::callbackOptionsMouseButton(Fl_Widget *w, void *data)
{
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackOptionsMouseAction(Fl_Widget *w, void *data)
{
	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackOptionsChange(Fl_Widget *w, void *data)
{
	int keyCode1=0, keyCode2=0;
	double sensitivityX=0.0f, sensitivityY=0.0f;

	sscanf(VmolGui::getInstance()->optionsMouseSensitivityX_->value(), "%lf", &sensitivityX);
	sscanf(VmolGui::getInstance()->optionsMouseSensitivityY_->value(), "%lf", &sensitivityY);

	keyCode1 = (int) VmolGui::getInstance()->optionsShortcut1_->value()[0];
	keyCode2 = (int) VmolGui::getInstance()->optionsShortcut2_->value()[0];

	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->setMouseSensitivityX(sensitivityX);
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->setMouseSensitivityY(sensitivityY);

	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->setShortcut1(keyCode1);
	VmolCommand::getInstance()->getViewList()[VmolGui::getInstance()->optionsView_->value()]->setShortcut2(keyCode2);

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackOptionsRunScript(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*.vsc", Fl_File_Chooser::SINGLE, "Run script...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		string commandString;
		commandString = "run type={script} value={";
		commandString += newFileChooser.value();
		commandString += "}";
		VmolCommand::getInstance()->executeCommand(commandString);
	}
}

/*
void VmolGui::callbackOptionsExportWorkspaceDialogCallback(Fl_File_Chooser *w, void *data)
{
//	printf("File selected: %s\n", w->value());
}
*/

void VmolGui::callbackOptionsExportWorkspace(Fl_Widget *w, void *data)
{
//	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Export workspace to...");
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::CREATE, "Export workspace to...");
//	newFileChooser.callback(callbackOptionsExportWorkspaceDialogCallback);

//	newFileChooser.type(1);
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolCommand::getInstance()->exportCommandHistory((string) newFileChooser.value());
	}
}
