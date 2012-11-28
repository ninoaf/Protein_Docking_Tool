/*
 * guicallbacksmenu.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: ivan
 */


#include "vmolgui.h"
#include "glwindow.h"
#include "../command/vmolcommand.h"

using namespace std;



void VmolGui::callbackMenuFileImportPdb(Fl_Widget *w, void *data)
{
	char tempChar1[200], tempChar2[200], tempChar3[200];
	string commandString, parentName;

	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::SINGLE, "Load pdb...");
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		sprintf (tempChar1, "pdb%d", VmolCommand::getInstance()->getPdbList().size());
		commandString = "create pdb name={" + ((string) tempChar1) + "} path={" + ((string) + newFileChooser.value()) + "}  radiusPath={data/system/atmtypenumbers} radiusType={united} center={false} centerType={mass}";
		VmolCommand::getInstance()->executeCommand(commandString);

		parentName = "";
		if (VmolCommand::getInstance()->getNodeList().size() > 0)
		{
			parentName = VmolCommand::getInstance()->getNodeList()[(VmolCommand::getInstance()->getNodeList().size()-1)]->getName();
		}

		sprintf (tempChar2, "node%d", VmolCommand::getInstance()->getNodeList().size());
		sprintf (tempChar3, "nodeMode%d", VmolCommand::getInstance()->getULongLongIntList().size());

		commandString = "create variable name={" + ((string) tempChar3) + "} type={ulonglong} value={0x0001000000001101}";
		VmolCommand::getInstance()->executeCommand(commandString);

		commandString = "create node name={" + ((string) tempChar2) + "} nodeType={pdb} nodeParams={" + ((string) tempChar1) + " sphere stick " + ((string) tempChar3) + "} parent={" + parentName + "}";
		VmolCommand::getInstance()->executeCommand(commandString);

		VmolGui::getInstance()->refreshGui();
	}
}

void VmolGui::menuLoadMesh(string type, string path)
{
	char tempChar1[200], tempChar2[200], tempChar3[200];
	string commandString, parentName;

	sprintf (tempChar1, "mesh%d", VmolCommand::getInstance()->getPdbList().size());
	commandString = "create mesh name={" + ((string) tempChar1) + "} type={" + type + "} path={" + path + "} center={false} autoScale={0.0} value={true 0.0}";
	VmolCommand::getInstance()->executeCommand(commandString);

	parentName = "";
	if (VmolCommand::getInstance()->getNodeList().size() > 0)
	{
		parentName = VmolCommand::getInstance()->getNodeList()[(VmolCommand::getInstance()->getNodeList().size()-1)]->getName();
	}

	sprintf (tempChar2, "node%d", VmolCommand::getInstance()->getNodeList().size());
	sprintf (tempChar3, "nodeMode%d", VmolCommand::getInstance()->getULongLongIntList().size());

	commandString = "create variable name={" + ((string) tempChar3) + "} type={ulonglong} value={0x0001000000001105}";
	VmolCommand::getInstance()->executeCommand(commandString);

	commandString = "create node name={" + ((string) tempChar2) + "} nodeType={mesh} nodeParams={" + ((string) tempChar1) + " " + ((string) tempChar3) + "} parent={" + parentName + "}";
	VmolCommand::getInstance()->executeCommand(commandString);

	VmolGui::getInstance()->refreshGui();
}

void VmolGui::callbackMenuFileImportMeshDat(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::SINGLE, "Load mesh (dat)...");
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->menuLoadMesh("dat", newFileChooser.value());
	}
}

void VmolGui::callbackMenuFileImportMeshGrid(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::SINGLE, "Load mesh (grid)...");
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->menuLoadMesh("grid", newFileChooser.value());
	}
}

void VmolGui::callbackMenuFileImportMeshMs(Fl_Widget *w, void *data)
{
	unsigned int i=0;
	string path;
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::SINGLE, "Load mesh (ms)...");
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		path = newFileChooser.value();
		for (i=(path.size()-1); i>=0; i--)
		{
			if (path[i] == '.')
			{
				path = path.substr(0, i);
				break;
			}
		}

		VmolGui::getInstance()->menuLoadMesh("ms", path);
	}
}

void VmolGui::callbackMenuFileImportScript(Fl_Widget *w, void *data)
{
	string commandString;

	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::SINGLE, "Load script...");
	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		commandString = "run " + ((string) + newFileChooser.value());
		VmolCommand::getInstance()->executeCommand(commandString);
	}
}

void VmolGui::callbackMenuFileExportWorkspace(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::CREATE, "Export workspace to...");
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

void VmolGui::callbackMenuExit(Fl_Widget *w, void *data)
{
	exit(1);
}

void VmolGui::callbackMenuEditSetDefaultWorkspace(Fl_Widget *w, void *data)
{
	VmolCommand::getInstance()->exportCommandHistory("data/system/defaultWorkspace.vsc");
}

void VmolGui::callbackMenuHelpHelp(Fl_Widget *w, void *data)
{
}

void VmolGui::callbackMenuEditHelpAbout(Fl_Widget *w, void *data)
{
	// '@' is a special character in FLTK...
	fl_message("Author: Ivan Sovic, univ.bacc.ing.eit\nEmail: ivan.sovic@@gmail.com\nPDT Team\nWeb: http://complex.zesoi.fer.hr\nCopyright 2010.");
}

void VmolGui::callbackMenuToolsStartRecordingMacro(Fl_Widget *w, void *data)
{
	VmolGui::getInstance()->macroStart_ = VmolCommand::getInstance()->getCommandHistory().size() - 1;

//	w->deactivate();
}

void VmolGui::callbackMenuToolsStopRecordingMacro(Fl_Widget *w, void *data)
{
	unsigned long int i=0;
	FILE *fp=NULL;
	Fl_File_Chooser newFileChooser(".", NULL, Fl_File_Chooser::CREATE, "Export workspace to...");

	VmolGui::getInstance()->macroEnd_ = VmolCommand::getInstance()->getCommandHistory().size() - 1;

//	w->deactivate();

//	printf ("start = %d\nstop = %d\n", VmolGui::getInstance()->macroStart_, VmolGui::getInstance()->macroEnd_);

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		fp = fopen(newFileChooser.value(), "w");
		if (fp == NULL)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", newFileChooser.value());
			return;
		}

		for (i=VmolGui::getInstance()->macroStart_; i<VmolGui::getInstance()->macroEnd_; i++)
		{
			fprintf (fp, "%s\n", VmolCommand::getInstance()->getCommandHistory()[i].c_str());
		}

		fclose(fp);
	}
}
