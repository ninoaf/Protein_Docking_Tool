/*
 * guimenus.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: ivan
 */


#include "vmolgui.h"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Menu_Bar.H>
#include "../command/vmolcommand.h"




void VmolGui::setupMenus()
{
	Fl_Menu_Bar *newMenuBar=NULL;

	newMenuBar = new Fl_Menu_Bar(0, 0, mainWindow->w(), 30);
	newMenuBar->add("&File/Load &PDB", FL_CTRL+'p', callbackMenuFileImportPdb);
	newMenuBar->add("&File/Load &mesh/&dat", FL_CTRL+'d', callbackMenuFileImportMeshDat);
	newMenuBar->add("&File/Load &mesh/&grid", FL_CTRL+'g', callbackMenuFileImportMeshGrid);
	newMenuBar->add("&File/_Load &mesh/&ms", FL_CTRL+'m', callbackMenuFileImportMeshMs);
	newMenuBar->add("&File/_&Run script", FL_CTRL+'r', callbackMenuFileImportScript);
	newMenuBar->add("&File/_&Export Workspace", FL_CTRL+'e', callbackMenuFileExportWorkspace);
	newMenuBar->add("&File/E&xit", FL_CTRL+'x', callbackMenuExit);

	newMenuBar->add("&Edit/&Set default workspace", FL_CTRL+'s', callbackMenuEditSetDefaultWorkspace);

	newMenuBar->add("&Tools/&Start recording macro", FL_CTRL+'s', callbackMenuToolsStartRecordingMacro);
	newMenuBar->add("&Tools/Sto&p recording macro", FL_CTRL+'p', callbackMenuToolsStopRecordingMacro);

//	newMenuBar->add("&Help/&Help", FL_CTRL+'h', callbackMenuHelpHelp);
	newMenuBar->add("&Help/&About", FL_CTRL+'a', callbackMenuEditHelpAbout);
}
