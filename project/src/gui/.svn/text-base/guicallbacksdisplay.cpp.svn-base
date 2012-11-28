/*
 * guicallbacksdisplay.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: ivan
 */

#include "vmolgui.h"
#include "glwindow.h"
#include "../command/vmolcommand.h"

using namespace std;



// #include <FL/Fl_Tree.H>

void VmolGui::callbackDisplayViewList(Fl_Widget *w, void *data)
{
	unsigned int i=0;
	string viewName;
	VmolView *view;

	if (VmolGui::getInstance()->displayViewList_->value() < 1)
		return;

	viewName = VmolGui::getInstance()->displayViewList_->text(VmolGui::getInstance()->displayViewList_->value());

	view = (VmolView *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_VIEW, viewName);

	VmolGui::getInstance()->displayName_->value(view->getName().c_str());

	for (i=0; i<VmolGui::getInstance()->displayRootNode_->size(); i++)
	{
		if (((string) VmolGui::getInstance()->displayRootNode_->text(i)) == view->getSceneRootNode()->getName())
		{
			VmolGui::getInstance()->displayRootNode_->value(i);
			break;
		}
	}

//	VmolGui::getInstance()->displayBackgroundColor_->value("(not yet implemented)");
}

void VmolGui::callbackDisplayChange(Fl_Widget *w, void *data)
{
	string viewName, newName, newRootNode;
	string commandString;

	if (VmolGui::getInstance()->displayViewList_->value() < 1)
		return;

	viewName = VmolGui::getInstance()->displayViewList_->text(VmolGui::getInstance()->displayViewList_->value());

	newName = VmolGui::getInstance()->displayName_->value();
	newRootNode = VmolGui::getInstance()->displayRootNode_->text(VmolGui::getInstance()->displayRootNode_->value());

	commandString = "change " + viewName + " name={" + newName + "} nodeParams={" + newRootNode + "}";
	VmolCommand::getInstance()->executeCommand(commandString);

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackDisplayCreate(Fl_Widget *w, void *data)
{
	string newName, newRootNode;
	string commandString;

	newName = VmolGui::getInstance()->displayName_->value();
	newRootNode = VmolGui::getInstance()->displayRootNode_->text(VmolGui::getInstance()->displayRootNode_->value());

	commandString = "create view name={" + newName + "} nodeParams={" + newRootNode + "}";
//	printf ("commandString = %s\n", commandString.c_str());

	VmolCommand::getInstance()->executeCommand(commandString);

	VmolGui::getInstance()->refreshGui();

	VmolGui::getInstance()->mainWindow->redraw();
	VmolGui::getInstance()->mainWindow->end();
}

void VmolGui::callbackDisplayRemove(Fl_Widget *w, void *data)
{
	string viewName;
	string commandString;

	if (VmolGui::getInstance()->displayViewList_->value() < 1)
		return;

	viewName = VmolGui::getInstance()->displayViewList_->text(VmolGui::getInstance()->displayViewList_->value());

	commandString = "remove " + viewName;
	VmolCommand::getInstance()->executeCommand(commandString);

	VmolGui::getInstance()->refreshGui();
}
