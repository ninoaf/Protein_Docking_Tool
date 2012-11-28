/*
 * guitabs.cpp
 *
 *  Created on: May 31, 2010
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
#include "../command/vmolcommand.h"



/*
void callBackChoiceViewNum(Fl_Widget *, void *data)
{
//    Fl_Choice *in=(Fl_Choice *)data;
//    fprintf(stderr, "Value='%s'\n", (const char*)in->value());
//	printf ("Vrijednost %d!\n", ((int) data));
	VmolCommand::getInstance()->executeCommand("");
}

Fl_Menu_Item choiceViewNumValues[] = {	{"one", 0, callBackChoiceViewNum, (void *) 1},
										{"two", 0, callBackChoiceViewNum, (void *) 2},
										{"three", 0, callBackChoiceViewNum, (void *) 3},
										{"four", 0, callBackChoiceViewNum, (void *) 4},
										{0}
};
*/


void VmolGui::setupTabs()
{
	Fl_Tabs *newTab=NULL;
	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

	setupTabDisplay();
	setupTabOptions();
	setupTabNodes();
	setupTabVariables();
//	setupTabInfo();
	setupTabPDT();

//	newTab->forms_end();
	newTab->end();
	tabList_.push_back(newTab);
}

double VmolGui::tabGridX(unsigned int index)
{
	return (tabMenuPosition_.x + index*5);
}

double VmolGui::tabGridY(unsigned int index)
{
	return (tabMenuPosition_.y + index*5);
}

void VmolGui::setupTabDisplay()
{
//				tabDisplay_ = new Fl_Tabs(940, 55, 225, 775, "Display");

/*
	Fl_Input_Choice *displayViewNumber;
	displayViewNumber = new Fl_Input_Choice(tabMenuPosition_.x + 20, 80, 100, 28, "Views #:");
	displayViewNumber->callback(input_choice_cb, (void*) displayViewNumber);
	displayViewNumber->add("one");
	displayViewNumber->add("two");
	displayViewNumber->add("three");
	displayViewNumber->value(0);
*/

/*
	Fl_Choice *c = new Fl_Choice(tabGridX(30), tabGridY(15), 100, 25);
	c->menu(choiceViewNumValues);
	c->align(FL_ALIGN_RIGHT);

	Fl_Box *b;
	b = new Fl_Box(tabGridX(1), tabGridY(15), 0, 25, "Number of views:");
	b->align(FL_ALIGN_RIGHT);
*/

/*
	Fl_Choice *c2 = new Fl_Choice(tabMenuPosition_.x + 105, 105, 200, 25);
	c2->menu(choiceViewNumValues);
	c2->align(FL_ALIGN_RIGHT);
*/

/*
// korisno za konzolu
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
	Fl_Text_Display *disp = new Fl_Text_Display(tabMenuPosition_.x + 80, 200, 200, 100, "Display");
	disp->buffer(buff);
	buff->text("line 0\nline 1\nline 2\n"
	"line 3\nline 4\nline 5\n"
	"line 6\nline 7\nline 8\n"
	"line 9\nline 10\nline 11\n"
	"line 12\nline 13\nline 14\n"
	"line 15\nline 16\nline 17\n"
	"line 18\nline 19\nline 20\n"
	"line 21\nline 22\nline 23\n");
*/

/*
	b = new Fl_Box(tabMenuPosition_.x + 80, 250, 0, 25,"Ovo je samo proba!");
	b->align(FL_ALIGN_RIGHT);
*/

/*
	int widths[] = { 100, 50, 50, 70, 70, 40, 40, 70, 70, 50, 0 };               // widths for each column
    ColResizeBrowser *colResizeBrowser = new ColResizeBrowser(tabGridX(1), tabGridY(30), tabMenuPosition_.width, 200);
    colResizeBrowser->column_widths(widths);
    colResizeBrowser->showcolsep(1);
    //colResizeBrowser->colsepcolor(FL_RED);
    colResizeBrowser->column_char('\t');                                                       // tabs as column delimiters
    colResizeBrowser->type(FL_MULTI_BROWSER);

    //// SIMPLE UN-COLORED HEADING
    ////  colResizeBrowser->add("USER\tPID\t%CPU\t%MEM\tVSZ\tRSS\tTTY\tSTAT\tSTART\tTIME\tCOMMAND");

    // NICER COLORED HEADING
    colResizeBrowser->add("@B12@C7@b@.USER\t@B12@C7@b@.PID\t@B12@C7@b@.%CPU\t"                 // tab delimited columns with colors
           "@B12@C7@b@.%MEM\t@B12@C7@b@.VSZ\t@B12@C7@b@.RSS\t"
           "@B12@C7@b@.TTY\t@B12@C7@b@.STAT\t@B12@C7@b@.START\t"
           "@B12@C7@b@.TIME\t@B12@C7@b@.COMMAND");

    // COLUMNS OF DATA
    colResizeBrowser->add("root\t2888\t0.0\t0.0\t1352\t0\ttty3\tSW\tAug15\t0:00\t@b@f/sbin/mingetty tty3");
    colResizeBrowser->add("erco\t2889\t0.0\t13.0\t221352\t0\ttty3\tR\tAug15\t1:34\t@b@f/usr/local/bin/render a35 0004");
    colResizeBrowser->add("uucp\t2892\t0.0\t0.0\t1352\t0\tttyS0\tSW\tAug15\t0:00\t@b@f/sbin/agetty -h 19200 ttyS0 vt100");
    colResizeBrowser->add("root\t13115\t0.0\t0.0\t1352\t0\ttty2\tSW\tAug30\t0:00\t@b@f/sbin/mingetty tty2");
    colResizeBrowser->add("root\t13464\t0.0\t0.0\t1352\t0\ttty1\tSW\tAug30\t0:00\t@b@f/sbin/mingetty tty1 --noclear");

    colResizeBrowser->redraw();
*/
	unsigned int refY=0;
	TextInput *newTextInput=NULL;
	Fl_Box *newFlBox=NULL;
	Fl_Hold_Browser *newBrowser=NULL;
	Fl_Button *newButton=NULL;
	Fl_Choice *newChoice=NULL;
	Fl_Tabs *newTab=NULL;

	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "Display");

	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

	refY = 15;

	newFlBox = new Fl_Box(tabGridX(2), tabGridY(refY - 5), 0, 5*5, "List of available views:");
	newFlBox->align(FL_ALIGN_RIGHT);

	newBrowser = new Fl_Hold_Browser(tabGridX(2), tabGridY(refY), tabMenuPosition_.width*2/3+5*12, 5*30);
	newBrowser->clear();
/*
	newBrowser->add("One");
	newBrowser->add("Two");
	newBrowser->add("Threeeeeeeeeeeeeeeeee");
	newBrowser->add("Three");
	newBrowser->select(1);
*/
	newBrowser->callback(callbackDisplayViewList, (void *) newBrowser);
	displayViewList_ = newBrowser;

	newFlBox = new Fl_Box(tabGridX(2), tabGridY(refY + 32), 0, 5*5, "Name:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), tabGridY(refY + 32), tabMenuPosition_.width*2/3-5*6, 5*5);
	displayName_ = newTextInput;

/*
	newFlBox = new Fl_Box(tabGridX(2), tabGridY(refY + 37), 0, 5*5, "Root node:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), tabGridY(refY + 37), tabMenuPosition_.width*2/3-5*14, 5*5);
	displayRootNode_ = newTextInput;
	newButton = new Fl_Button(tabGridX(20)+displayRootNode_->w()+5*1, tabGridY(refY + 37), 35, 25, "Pick");
	displayPickNode_ = newButton;
*/

	newFlBox = new Fl_Box(tabGridX(2), tabGridY(refY + 37), 0, 5*5, "Root node:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newChoice = new Fl_Choice(tabGridX(20), tabGridY(refY + 37), tabMenuPosition_.width*2/3-5*6, 5*5);
	displayRootNode_ = newChoice;

/*
	newFlBox = new Fl_Box(tabGridX(2), tabGridY(refY + 42), 0, 5*5, "Back color:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), tabGridY(refY + 42), tabMenuPosition_.width*2/3-5*6, 5*5);
	displayBackgroundColor_ = newTextInput;
*/

	newButton = new Fl_Button(tabGridX(8), tabGridY(refY + 44), tabMenuPosition_.width/3, 20, "Change");
	newButton->callback(callbackDisplayChange, (void *) newButton);
	displayChange_ = newButton;

	newButton = new Fl_Button(tabGridX(32), tabGridY(refY + 44), tabMenuPosition_.width/3, 20, "Create");
	newButton->callback(callbackDisplayCreate, (void *) newButton);
	displayCreate_ = newButton;

	newButton = new Fl_Button(tabGridX(32), tabGridY(refY + 49), tabMenuPosition_.width/3, 20, "Remove");
	newButton->callback(callbackDisplayRemove, (void *) newButton);
	displayRemove_ = newButton;

//	  newTextInput->activate();
//	  newGroupText->end();

//	  newGroupText = new Fl_Group((tabMenuPosition_.width/2 + 5), tabGridy(30), 25, (tabMenuPosition_.width/2 - 5));
//	  newTextInput = new Fl_Input((tabMenuPosition_.width/2 + 5), tabGridy(30), 25, (tabMenuPosition_.width/2 - 5));



//	g->resizable(c);
//	g->forms_end();
	newGroup->end();

//	newTab->forms_end();
	newTab->hide();
	newTab->end();

	tabList_.push_back(newTab);
	groupList_.push_back(newGroup);
}

void VmolGui::setupTabOptions()
{
	Fl_Box *newFlBox=NULL;
	TextInput *newTextInput=NULL;
	Fl_Button *newButton=NULL;
	Fl_Text_Buffer *newTextBuffer=NULL;
	Fl_Text_Display *newTextDisplay=NULL;
	Fl_Choice *newChoice=NULL;
	Fl_Tabs *newTab=NULL;

//	newTab = new Fl_Tabs(tabMenuPosition_.x+25, tabMenuPosition_.y+25, tabMenuPosition_.width-25, tabMenuPosition_.height-25, "Options");
	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "Options");
	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

	newTextBuffer = new Fl_Text_Buffer();
	newTextDisplay = new Fl_Text_Display(tabGridX(2), tabGridY(15), tabMenuPosition_.width-5*2, tabMenuPosition_.height/2, "Console output:");
	newTextDisplay->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newTextDisplay->buffer(newTextBuffer);
	optionsConsole_ = newTextDisplay;

/*
	newTextBuffer->text("line 0\nline 1\nline 2\n"
	"line 3\nline 4\nline 5\n"
	"line 6\nline 7\nline 8\n"
	"line 9\nline 10\nline 11\n"
	"line 12\nline 13\nline 14\n"
	"line 15\nline 16\nline 17\n"
	"line 18\nline 19\nline 20\n"
	"line 21\nline 22\nline 23\n");
*/

//	printf ("text = %s\n", newTextBuffer->text());
	optionsConsoleTextBuffer_ = newTextBuffer;

	newButton = new Fl_Button(optionsConsole_->x(), optionsConsole_->y()+optionsConsole_->h()+5*2, tabMenuPosition_.width/3, 35, "Run .vsc script");
	newButton->callback(callbackOptionsRunScript, (void *) newButton);
	optionsRunScript_ = newButton;

	newButton = new Fl_Button(optionsConsole_->x()+optionsConsole_->w()-tabMenuPosition_.width/2, optionsConsole_->y()+optionsConsole_->h()+5*2, tabMenuPosition_.width/2, 35, "Export workspace");
	newButton->callback(callbackOptionsExportWorkspace, (void *) newButton);
	optionsExportWorkspace_ = newButton;

	newFlBox = new Fl_Box(optionsRunScript_->x(), optionsRunScript_->y()+optionsRunScript_->h()+5*2, 0, 5*5, "Options for view:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newChoice = new Fl_Choice(newFlBox->x(), newFlBox->y()+newFlBox->h()+5*2, optionsConsole_->w(), 25);
	newChoice->callback(callbackOptionsView, (void *) newChoice);
	newChoice->value(0);
	optionsView_ = newChoice;

	newFlBox = new Fl_Box(optionsView_->x(), optionsView_->y()+optionsView_->h()+5*2, 0, 5*5, "Bind mouse to variable:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newChoice = new Fl_Choice(newFlBox->x(), newFlBox->y()+newFlBox->h()+5*2, optionsConsole_->w()/3, 25);
	newChoice->add("Left button");
	newChoice->add("Left + Shortcut1");
	newChoice->add("Left + Shortcut2");
	newChoice->add("Middle button");
	newChoice->add("Middle + Shortcut1");
	newChoice->add("Middle + Shortcut2");
	newChoice->add("Right button");
	newChoice->add("Right + Shortcut1");
	newChoice->add("Right + Shortcut2");
	newChoice->value(0);
	newChoice->callback(callbackOptionsMouseButton, (void *) newChoice);
	optionsMouseButton_ = newChoice;
	newChoice = new Fl_Choice(optionsMouseButton_->x()+optionsMouseButton_->w(), newFlBox->y()+newFlBox->h()+5*2, optionsConsole_->w()/3, 25);
	newChoice->add("Left - Right");
	newChoice->add("Up - Down");
	newChoice->value(0);
	newChoice->callback(callbackOptionsMouseAction, (void *) newChoice);
	optionsMouseAction_ = newChoice;
	newChoice = new Fl_Choice(optionsMouseAction_->x()+optionsMouseAction_->w(), newFlBox->y()+newFlBox->h()+5*2, optionsConsole_->w()/3, 25);
	newChoice->callback(callbackOptionsMouseBinds, (void *) newChoice);
	optionsMouseBinds_ = newChoice;

//	newChoice->menu(choiceViewNumValues);
//	newChoice->add("prvi");
//	newChoice->replace(1, "drugi");
//	newChoice->value(0);

//	newChoice->align(FL_ALIGN_RIGHT);

	newFlBox = new Fl_Box(optionsRunScript_->x(), newChoice->y()+newChoice->h()+5*2, 0, 5*5, "Mouse sensitivity X:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(32), newFlBox->y(), optionsConsole_->w()-5*32, 5*5);
	optionsMouseSensitivityX_ = newTextInput;

	newFlBox = new Fl_Box(optionsRunScript_->x(), optionsMouseSensitivityX_->y()+optionsMouseSensitivityX_->h()+5*1, 0, 5*5, "Mouse sensitivity Y:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(32), newFlBox->y(), optionsConsole_->w()-5*32, 5*5);
	optionsMouseSensitivityY_ = newTextInput;

	newFlBox = new Fl_Box(optionsRunScript_->x(), optionsMouseSensitivityY_->y()+optionsMouseSensitivityY_->h()+5*1, 0, 5*5, "Shortcut 1:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(32), newFlBox->y(), optionsConsole_->w()-5*32, 5*5);
	optionsShortcut1_ = newTextInput;

	newFlBox = new Fl_Box(optionsRunScript_->x(), optionsShortcut1_->y()+optionsShortcut1_->h()+5*1, 0, 5*5, "Shortcut 2:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(32), newFlBox->y(), optionsConsole_->w()-5*32, 5*5);
	optionsShortcut2_ = newTextInput;

	newButton = new Fl_Button(optionsRunScript_->x()+5*5, optionsShortcut2_->y()+optionsShortcut2_->h()+5*1, tabMenuPosition_.width-5*10, 25, "Change");
	newButton->callback(callbackOptionsChange, (void *) newButton);
	optionsChange_= newButton;



	newGroup->end();
	newTab->hide();
	newTab->end();
	tabList_.push_back(newTab);
}

void VmolGui::setupTabInfo()
{
	Fl_Tabs *newTab=NULL;

	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "Info");
	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height-25);

	newTab->hide();
	newTab->end();
	tabList_.push_back(newTab);
}

void VmolGui::setupTabPDT()
{
	Fl_Box *newFlBox=NULL;
	TextInput *newTextInput=NULL;
	Fl_Button *newButton=NULL;
	Fl_Check_Button *newCheckButton=NULL;
	Fl_Hold_Browser *newBrowser=NULL;
	Fl_Choice *newChoice=NULL;
	Fl_Tabs *newTab=NULL;
//	newTab = new Fl_Tabs(tabMenuPosition_.x+25, tabMenuPosition_.y+25, tabMenuPosition_.width-25, tabMenuPosition_.height-25, "PDT");

	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "PDT");
	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

	newChoice = new Fl_Choice(tabGridX(2), tabGridY(15), (tabMenuPosition_.width-5*4)/2, 5*5, "Active receptor:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtActiveReceptor_ = newChoice;

	newChoice = new Fl_Choice(pdtActiveReceptor_->x(), pdtActiveReceptor_->y()+pdtActiveReceptor_->h()+5*5, pdtActiveReceptor_->w(), 5*5, "Receptor rotation:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtReceptorRotation_ = newChoice;

	newChoice = new Fl_Choice(pdtActiveReceptor_->x()+pdtActiveReceptor_->w(), pdtReceptorRotation_->y()+pdtReceptorRotation_->h()+5*5, pdtActiveReceptor_->w(), 5*5, "Ligand translation:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtLigandTranslation_ = newChoice;

	newChoice = new Fl_Choice(pdtActiveReceptor_->x()+pdtActiveReceptor_->w(), pdtActiveReceptor_->y(), pdtActiveReceptor_->w(), 5*5, "Active ligand:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtActiveLigand_ = newChoice;

	newChoice = new Fl_Choice(pdtActiveLigand_->x(), pdtActiveLigand_->y()+pdtActiveLigand_->h()+5*5, pdtActiveLigand_->w(), 5*5, "Ligand rotation:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtLigandRotation_ = newChoice;

/*
	newTextInput = new TextInput(tabGridX(2), pdtReceptorTranslation_->y()+pdtReceptorTranslation_->h()+5*10, (tabMenuPosition_.width-5*2)/2, 5*5, "Grid size:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_CENTER);
	newTextInput->value("60");
	pdtGridSize_ = newTextInput;

	newTextInput = new TextInput(tabGridX(2), pdtGridSize_->y()+pdtGridSize_->h()+5*5, pdtGridSize_->w(), 5*5, "Grid cell size:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_CENTER);
	newTextInput->value("1");
	pdtGridCellSize_ = newTextInput;

	newButton = new Fl_Button(pdtGridSize_->x()+pdtGridSize_->w()+5*1, pdtGridSize_->y(), (tabMenuPosition_.width-5*6)/2, pdtGridCellSize_->y()+pdtGridCellSize_->h()-pdtGridSize_->y(), "Calculate Coeffs");
	newButton->callback(callbackPdtCalculateCoefficients, (void *) newButton);
	pdtCalculateCoeffs_ = newButton;
*/

//	newTextInput = new TextInput(tabGridX(15), newFlBox->y(), (tabMenuPosition_.width-5*3)/2, 5*5);
//	pdtCurrentScore_ = newTextInput;

	newButton = new Fl_Button(tabGridX(2), pdtLigandTranslation_->y()+pdtLigandTranslation_->h()+5*1, (tabMenuPosition_.width-5*3), 5*5, "Local -> Global Z-axis");
	newButton->callback(callbackPdtLocalToGlobal, (void *) newButton);
	pdtLocalToGlobal_ = newButton;



	newFlBox = new Fl_Box(tabGridX(2), pdtLocalToGlobal_->y()+pdtLocalToGlobal_->h()+5*5, 0, 5*5, "Config file:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), newFlBox->y(), (tabMenuPosition_.width-5*22-5*6), 5*5);
	pdtConfigPath_ = newTextInput;
	newButton = new Fl_Button(pdtConfigPath_->x()+pdtConfigPath_->w(), pdtConfigPath_->y(), 5*6, 5*5, "Pick");
	newButton->callback(callbackPdtConfigPathPick, (void *) newButton);
	pdtPickConfigFile_ = newButton;

	newButton = new Fl_Button(tabGridX(2), pdtPickConfigFile_->y()+pdtPickConfigFile_->h()+5*2, (tabMenuPosition_.width-5*3)/2, 5*5, "Predocking");
	newButton->callback(callbackPdtPredocking, (void *) newButton);
	pdtRunPredocking_ = newButton;

	newButton = new Fl_Button(pdtRunPredocking_->x()+pdtRunPredocking_->w(), pdtRunPredocking_->y(), (tabMenuPosition_.width-5*3)/2, 5*5, "Docking");
	newButton->callback(callbackPdtDocking, (void *) newButton);
	pdtRunDocking_ = newButton;

	newButton = new Fl_Button(tabGridX(2), pdtRunDocking_->y()+pdtRunDocking_->h(), (tabMenuPosition_.width-5*3), 5*5, "Load protein coefficients");
	newButton->callback(callbackPdtLoadProteinCoefficients, (void *) newButton);
	pdtLoadProteinCoefficients_ = newButton;

	newButton = new Fl_Button(tabGridX(2), pdtLoadProteinCoefficients_->y()+pdtLoadProteinCoefficients_->h(), (tabMenuPosition_.width-5*3), 5*5, "Load scores file");
	newButton->callback(callbackPdtLoadScoresFile, (void *) newButton);
	pdtLoadScoresFile_ = newButton;

	newChoice = new Fl_Choice(tabGridX(2), pdtLoadScoresFile_->y()+pdtLoadScoresFile_->h()+5*10, (tabMenuPosition_.width-5*3)/3, 5*5, "Complex:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	pdtCorrectComplex_ = newChoice;

	newTextInput = new TextInput(pdtCorrectComplex_->x()+pdtCorrectComplex_->w(), pdtCorrectComplex_->y(), (tabMenuPosition_.width-5*3)/3, 5*5, "Start score:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_CENTER);
	newTextInput->value("0");
	pdtStartingScore_ = newTextInput;

	newTextInput = new TextInput(pdtStartingScore_->x()+pdtStartingScore_->w(), pdtCorrectComplex_->y(), (tabMenuPosition_.width-5*3)/3, 5*5, "Num. scores:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_CENTER);
	newTextInput->value("1");
	pdtNumberOfScores_ = newTextInput;

	newFlBox = new Fl_Box(tabGridX(2), pdtCorrectComplex_->y()+pdtCorrectComplex_->h()+5*1, 0, 5*5, "Eval output:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), newFlBox->y(), (tabMenuPosition_.width-5*22-5*6), 5*5);
	newTextInput->value("data/rmsd/default.rmsd");
	pdtEvaluationPath_ = newTextInput;
	newButton = new Fl_Button(pdtEvaluationPath_->x()+pdtEvaluationPath_->w(), pdtEvaluationPath_->y(), 5*6, 5*5, "Pick");
	newButton->callback(callbackPdtEvaluationPathPick, (void *) newButton);
	pdtPickEvaluationPath_ = newButton;

	newButton = new Fl_Button(tabGridX(2), pdtEvaluationPath_->y()+pdtEvaluationPath_->h()+5*1, (tabMenuPosition_.width-5*3), 5*5, "Evaluate scores");
	newButton->callback(callbackPdtEvaluateScores, (void *) newButton);
	pdtEvaluateScores_ = newButton;



	newFlBox = new Fl_Box(tabGridX(2), pdtEvaluateScores_->y()+pdtEvaluateScores_->h()+5*2, 0, 5*5, "Output PDB:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(20), newFlBox->y(), (tabMenuPosition_.width-5*22-5*6), 5*5);
	newTextInput->value("data/pdbOutput/outPdb.pdb");
	pdtOutputPdbPath_ = newTextInput;
	newButton = new Fl_Button(pdtOutputPdbPath_->x()+pdtOutputPdbPath_->w(), pdtOutputPdbPath_->y(), 5*6, 5*5, "Pick");
	newButton->callback(callbackPdtPickOutputPdbPath, (void *) newButton);
	pdtPickOutputPdbPath_ = newButton;

	newButton = new Fl_Button(tabGridX(2), pdtPickOutputPdbPath_->y()+pdtPickOutputPdbPath_->h()+5*1, (tabMenuPosition_.width-5*3), 5*5, "Generate output PDB");
	newButton->callback(callbackPdtGeneratePdb, (void *) newButton);
	pdtGenerateOutputPdb_ = newButton;



	newButton = new Fl_Button(tabGridX(2), pdtGenerateOutputPdb_->y()+pdtGenerateOutputPdb_->h()+5*5, (tabMenuPosition_.width-5*3), 5*5, "Score the conformation");
	newButton->callback(callbackPdtScoreConformation, (void *) newButton);
	pdtScoreConformation_ = newButton;

	newCheckButton = new Fl_Check_Button(pdtScoreConformation_->x(), pdtScoreConformation_->y()+pdtScoreConformation_->h(), (tabMenuPosition_.width-5*3), 5*5, "Automatic evaluation");
//	newCheckButton->callback(callbackVariablesChangeScalar, (void *) newButton);
	pdtAutomaticScoring_ = newCheckButton;

	newFlBox = new Fl_Box(tabGridX(2), pdtAutomaticScoring_->y()+pdtAutomaticScoring_->h()+5*1, 0, 5*5, "Score:");
	newFlBox->align(FL_ALIGN_RIGHT);
	pdtCurrentScore_ = new Fl_Box(tabGridX(18), newFlBox->y(), (tabMenuPosition_.width-5*3)/2, 5*5, "0.0");
//	pdtCurrentScore_->align(FL_ALIGN_RIGHT);



//	newTab->hide();
	newTab->end();
	tabList_.push_back(newTab);
}

void VmolGui::setupTabNodes()
{
	Fl_Button *newButton=NULL;
	Fl_Choice *newChoice=NULL;
	Fl_Box *newFlBox=NULL;
	Fl_Check_Button *newCheckButton=NULL;
	TextInput *newTextInput=NULL;
	Fl_Tree *newTree=NULL;
	Fl_Tabs *newTab=NULL;
//	newTab = new Fl_Tabs(tabMenuPosition_.x+25, tabMenuPosition_.y+25, tabMenuPosition_.width-25, tabMenuPosition_.height-25, "Nodes");

	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "Nodes");
	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

//	OVDJE SAM STAO!!!
//	TREBA PROUCITI Fl_Tree...

	newTree = new Fl_Tree(tabGridX(2), tabGridY(15), tabMenuPosition_.width-5*4, tabMenuPosition_.height/4, "Scene graph:");
	newTree->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newTree->clear();
	newTree->callback(callbackNodesNodeTree, (void *) newTree);
	nodesNodeTree_ = newTree;

	newTextInput = new TextInput(nodesNodeTree_->x(), nodesNodeTree_->y()+nodesNodeTree_->h()+5*4, nodesNodeTree_->w()/3, 5*5, "Name:");
	newTextInput->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	nodesName_ = newTextInput;

	newChoice = new Fl_Choice(nodesName_->x()+nodesName_->w(), nodesName_->y(), nodesNodeTree_->w()/3, 5*5, "Type:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	newChoice->add("nop");
	newChoice->add("mesh");
	newChoice->add("pdb");
	newChoice->add("color");
	newChoice->add("lookat");
	newChoice->add("translation");
	newChoice->add("rotationx");
	newChoice->add("rotationy");
	newChoice->add("rotationz");
	newChoice->add("rotationeuler");
	newChoice->add("scale");
	newChoice->add("script");
	newChoice->value(0);
	newChoice->callback(callbackNodesType, (void *) newChoice);
	nodesType_ = newChoice;

	newChoice = new Fl_Choice(nodesType_->x()+nodesType_->w(), nodesType_->y(), nodesNodeTree_->w()/3, 5*5, "Parent:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	nodesParent_ = newChoice;

	newChoice = new Fl_Choice(nodesNodeTree_->x(), nodesName_->y()+nodesName_->h()+5*4, nodesNodeTree_->w()/4, 5*5, "Param1:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	newChoice->hide();
	nodesParameter1_ = newChoice;

	newChoice = new Fl_Choice(nodesParameter1_->x()+nodesParameter1_->w(), nodesParameter1_->y(), nodesNodeTree_->w()/4, 5*5, "Param2:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	newChoice->hide();
	nodesParameter2_ = newChoice;

	newChoice = new Fl_Choice(nodesParameter2_->x()+nodesParameter2_->w(), nodesParameter1_->y(), nodesNodeTree_->w()/4, 5*5, "Param3:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	newChoice->hide();
	nodesParameter3_ = newChoice;

	newChoice = new Fl_Choice(nodesParameter3_->x()+nodesParameter3_->w(), nodesParameter1_->y(), nodesNodeTree_->w()/4, 5*5, "Param4:");
	newChoice->align(FL_ALIGN_CENTER | FL_ALIGN_TOP);
	newChoice->hide();
	nodesParameter4_ = newChoice;

	newButton = new Fl_Button(nodesNodeTree_->x(), nodesParameter1_->y()+nodesParameter1_->h()+5*1, nodesNodeTree_->w()/3, 25, "Change");
	newButton->callback(callbackNodesChange, (void *) newButton);
	nodesChangeNode_ = newButton;

	newButton = new Fl_Button(nodesChangeNode_->x()+nodesChangeNode_->w(), nodesChangeNode_->y(), nodesNodeTree_->w()/3, 25, "Create");
	newButton->callback(callbackNodesCreate, (void *) newButton);
	nodesCreateNode_ = newButton;

	newButton = new Fl_Button(nodesCreateNode_->x()+nodesCreateNode_->w(), nodesChangeNode_->y(), nodesNodeTree_->w()/3, 25, "Remove");
	newButton->callback(callbackNodesRemove, (void *) newButton);
	nodesRemoveNode_ = newButton;



	newChoice = new Fl_Choice(nodesNodeTree_->x(), nodesChangeNode_->y()+nodesChangeNode_->h()+5*10, nodesNodeTree_->w()/2, 5*5, "Options for node mode:");
	newChoice->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newChoice->callback(callbackNodesOptionsNodeMode, (void *) newChoice);
	nodesOptionsNodeMode_ = newChoice;

	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x(), nodesOptionsNodeMode_->y()+nodesOptionsNodeMode_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "Geometry");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeGeometry_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeGeometry_->y(), nodesNodeTree_->w()/4, 5*5, "Colors");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeColors_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*2/4, nodesModeGeometry_->y(), nodesNodeTree_->w()/4, 5*5, "Normals");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeNormals_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*3/4, nodesModeGeometry_->y(), nodesNodeTree_->w()/4+5*10, 5*5, "Tex. coords");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeTextureCoords_ = newCheckButton;

	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x(), nodesModeGeometry_->y()+nodesModeGeometry_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "Textures");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeTextures_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeTextures_->y(), nodesNodeTree_->w()/4, 5*5, "Lighting");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeLighting_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*2/4, nodesModeTextures_->y(), nodesNodeTree_->w()/4, 5*5, "Wireframe");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeWireframe_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*3/4, nodesModeTextures_->y(), nodesNodeTree_->w()/4+5*10, 5*5, "Transpar.");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeTransparent_ = newCheckButton;

	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x(), nodesModeTransparent_->y()+nodesModeTransparent_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "Callote");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeCallote_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeCallote_->y(), nodesNodeTree_->w()/4, 5*5, "Sticks");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeSticks_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*2/4, nodesModeCallote_->y(), nodesNodeTree_->w()/4, 5*5, "Sticks&Balls");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeSticksBalls_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*3/4, nodesModeCallote_->y(), nodesNodeTree_->w()/4+5*10, 5*5, "Wire");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeWire_ = newCheckButton;

	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x(), nodesModeWire_->y()+nodesModeWire_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "Col. Atom");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeColorAtom_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeColorAtom_->y(), nodesNodeTree_->w()/4, 5*5, "Col. Amino");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeColorAmino_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*2/4, nodesModeColorAtom_->y(), nodesNodeTree_->w()/4, 5*5, "Col. Chain");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeColorChain_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*3/4, nodesModeColorAtom_->y(), nodesNodeTree_->w()/4+5*10, 5*5, "Undefined");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeColorUndefined1_ = newCheckButton;

	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x(), nodesModeColorUndefined1_->y()+nodesModeColorUndefined1_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "Center");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeObjectCenter_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeObjectCenter_->y(), nodesNodeTree_->w()/4, 5*5, "Bounds");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeObjectBounds_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*2/4, nodesModeObjectCenter_->y(), nodesNodeTree_->w()/4, 5*5, "Undefined");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeObjectUndefined_ = newCheckButton;
	newCheckButton = new Fl_Check_Button(nodesNodeTree_->x()+nodesNodeTree_->w()*3/4, nodesModeObjectCenter_->y(), nodesNodeTree_->w()/4+5*10, 5*5, "Defaults");
	newCheckButton->callback(callbackNodesChecksNodeMode, (void *) newCheckButton);
	nodesModeUseDefault_ = newCheckButton;

	newFlBox = new Fl_Box(nodesNodeTree_->x(), nodesModeObjectCenter_->y()+nodesModeObjectCenter_->h()+5*5, 0, 5*5, "Model #:");
	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(tabGridX(16), newFlBox->y(), (nodesNodeTree_->w()-5*18-5*6), 5*5);
	newTextInput->value("65535");
	nodesModeModel_ = newTextInput;
	newButton = new Fl_Button(nodesModeModel_->x()+nodesModeModel_->w(), nodesModeModel_->y(), 5*6, 5*5, "Set");
	newButton->callback(callbackNodesModeModelSet, (void *) newButton);
	nodesModeModelSet_ = newButton;

	newButton = new Fl_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeModel_->y()+nodesModeModel_->h()+5*2, nodesNodeTree_->w()/4, 5*5, "None");
	newButton->callback(callbackNodesModeModelNone, (void *) newButton);
	newButton->align(FL_ALIGN_CENTER);
	nodesModeModelNone_ = newButton;
	newButton = new Fl_Button(nodesModeModelNone_->x()+nodesModeModelNone_->w(), nodesModeModelNone_->y(), nodesNodeTree_->w()/4, 5*5, "Next");
	newButton->callback(callbackNodesModeModelNext, (void *) newButton);
	newButton->align(FL_ALIGN_CENTER);
	nodesModeModelNext_ = newButton;
	newButton = new Fl_Button(nodesNodeTree_->x()+nodesNodeTree_->w()/4, nodesModeModelNone_->y()+nodesModeModelNone_->h(), nodesNodeTree_->w()/4, 5*5, "All");
	newButton->callback(callbackNodesModeModelAll, (void *) newButton);
	newButton->align(FL_ALIGN_CENTER);
	nodesModeModelAll_ = newButton;
	newButton = new Fl_Button(nodesModeModelAll_->x()+nodesModeModelAll_->w(), nodesModeModelNone_->y()+nodesModeModelNone_->h(), nodesNodeTree_->w()/4, 5*5, "Previous");
	newButton->callback(callbackNodesModeModelPrevious, (void *) newButton);
	newButton->align(FL_ALIGN_CENTER);
	nodesModeModelPrevious_ = newButton;



/*
	newTree->add("Test1");
	newTree->add("Test2");
	newTree->add("Test1/Test11");
	newTree->add("Test2/Test21");
	newTree->add("Test1/Test12");
*/

	newTab->hide();
	newTab->end();
	tabList_.push_back(newTab);
}

void VmolGui::setupTabVariables()
{
	Fl_Box *newFlBox=NULL;
	TextInput *newTextInput=NULL;
	Fl_Button *newButton=NULL;
	Fl_Hold_Browser *newBrowser=NULL;
	Fl_Choice *newChoice=NULL;
	Fl_Tabs *newTab=NULL;

	newTab = new Fl_Tabs(tabMenuPosition_.x, tabMenuPosition_.y+25, tabMenuPosition_.width, tabMenuPosition_.height-25, "Variables");
	Fl_Group *newGroup = new Fl_Group(tabMenuPosition_.x, tabMenuPosition_.y, tabMenuPosition_.width, tabMenuPosition_.height);

	newBrowser = new Fl_Hold_Browser(tabGridX(2), tabGridY(15), tabMenuPosition_.width*2/5, 5*30, "Scalar variables:");
	newBrowser->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newBrowser->clear();
	newBrowser->callback(callbackVariablesScalar, (void *) newBrowser);
	variablesScalar_ = newBrowser;

//	newFlBox = new Fl_Box(optionsRunScript_->x(), optionsMouseSensitivityX_->y()+optionsMouseSensitivityX_->h()+5*1, 0, 5*5, "Mouse sensitivity Y:");
//	newFlBox->align(FL_ALIGN_RIGHT);
	newTextInput = new TextInput(variablesScalar_->x()+variablesScalar_->w(), variablesScalar_->y(), (tabMenuPosition_.width-variablesScalar_->w()-5*3)/2, 5*5, "Name:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesScalarName_ = newTextInput;
//	newTextInput = new TextInput(variablesScalarName_->x()+variablesScalarName_->w(), variablesScalar_->y(), (tabMenuPosition_.width-variablesScalar_->w()-5*3)/2, 5*5, "Type:");
//	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
//	variablesScalarType_ = newTextInput;
	newChoice = new Fl_Choice(variablesScalarName_->x()+variablesScalarName_->w(), variablesScalar_->y(), (tabMenuPosition_.width-variablesScalar_->w()-5*3)/2, 5*5, "Type:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("char");
	newChoice->add("uchar");
	newChoice->add("long");
	newChoice->add("ulong");
	newChoice->add("ulonglong");
	newChoice->add("float");
	newChoice->add("double");
	newChoice->add("vector3");
	newChoice->add("color");
	newChoice->add("eulervector3");
	variablesScalarType_ = newChoice;
	newTextInput = new TextInput(variablesScalarName_->x(), variablesScalarName_->y()+5*10, variablesScalarName_->w(), 5*5, "Value x:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesValueX_ = newTextInput;
	newTextInput = new TextInput(variablesValueX_->x()+variablesValueX_->w(), variablesValueX_->y(), variablesScalarName_->w(), 5*5, "Value y:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesValueY_ = newTextInput;
	newTextInput = new TextInput(variablesValueX_->x(), variablesValueY_->y()+5*10, variablesScalarName_->w(), 5*5, "Value z:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesValueZ_ = newTextInput;
	newTextInput = new TextInput(variablesValueX_->x()+variablesValueY_->w(), variablesValueZ_->y(), variablesScalarName_->w(), 5*5, "Value w:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesValueW_ = newTextInput;

	newButton = new Fl_Button(variablesScalar_->x(), variablesScalar_->y()+variablesScalar_->h()+5*1, (tabMenuPosition_.width-5*4)/3, 25, "Change");
	newButton->callback(callbackVariablesChangeScalar, (void *) newButton);
	variablesChangeScalar_ = newButton;

	newButton = new Fl_Button(variablesChangeScalar_->x()+variablesChangeScalar_->w()+5*1, variablesChangeScalar_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Create");
	newButton->callback(callbackVariablesCreateScalar, (void *) newButton);
	variablesCreateScalar_ = newButton;

	newButton = new Fl_Button(variablesCreateScalar_->x()+variablesCreateScalar_->w()+5*1, variablesCreateScalar_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Remove");
	newButton->callback(callbackVariablesRemoveScalar, (void *) newButton);
	variablesRemoveScalar_ = newButton;

/////////////////////////////////////////

	newBrowser = new Fl_Hold_Browser(variablesChangeScalar_->x(), variablesChangeScalar_->y()+variablesChangeScalar_->h()+5*10, tabMenuPosition_.width*2/5, 5*45, "Meshes:");
	newBrowser->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newBrowser->clear();
	newBrowser->callback(callbackVariablesMesh, (void *) newBrowser);
	variablesMesh_ = newBrowser;

	newTextInput = new TextInput(variablesMesh_->x()+variablesMesh_->w(), variablesMesh_->y(), (tabMenuPosition_.width-variablesMesh_->w()-5*3)/2, 5*5, "Name:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshName_ = newTextInput;

	newTextInput = new TextInput(variablesMeshName_->x()+variablesMeshName_->w(), variablesMesh_->y(), (tabMenuPosition_.width-variablesMesh_->w()-5*3)/2-5*5, 5*5, "Path:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshPath_ = newTextInput;
	newButton = new Fl_Button(variablesMeshPath_->x()+variablesMeshPath_->w(), variablesMeshPath_->y(), 5*6, 5*5, "Pick");
	newButton->callback(callbackVariablesMeshPathPick, (void *) newButton);
	variablesMeshPathPick_ = newButton;

	newChoice = new Fl_Choice(variablesMeshName_->x(), variablesMeshName_->y()+5*10, variablesMeshName_->w(), 5*5, "Type:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("dat");
	newChoice->add("grid");
	newChoice->add("ms");
	newChoice->value(0);
	variablesMeshType_ = newChoice;

	newChoice = new Fl_Choice(variablesMeshName_->x()+variablesMeshName_->w(), variablesMeshName_->y()+5*10, variablesMeshName_->w(), 5*5, "Center:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("false");
	newChoice->add("true");
	newChoice->value(0);
	variablesMeshCenter_ = newChoice;

	newTextInput = new TextInput(variablesMeshName_->x(), variablesMeshType_->y()+5*10, variablesMeshName_->w(), 5*5, "Autoscale:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshAutoscale_ = newTextInput;

	newChoice = new Fl_Choice(variablesMeshName_->x()+variablesMeshName_->w(), variablesMeshType_->y()+5*10, variablesMeshName_->w(), 5*5, "Auto isovalue:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("false");
	newChoice->add("true");
	newChoice->value(1);
	variablesMeshAutoIsovalue_ = newChoice;

	newTextInput = new TextInput(variablesMeshName_->x(), variablesMeshAutoscale_->y()+5*10, variablesMeshName_->w(), 5*5, "Isovalue:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshIsovalue_ = newTextInput;

	newChoice = new Fl_Choice(variablesMeshName_->x()+variablesMeshName_->w(), variablesMeshAutoscale_->y()+5*10, variablesMeshName_->w(), 5*5, "Assign node:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshAssignNode_ = newChoice;

	newChoice = new Fl_Choice(variablesMeshName_->x(), variablesMeshIsovalue_->y()+5*10, variablesMeshName_->w(), 5*5, "Node mode:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesMeshNodeMode_ = newChoice;



	newButton = new Fl_Button(variablesMesh_->x(), variablesMesh_->y()+variablesMesh_->h()+5*1, (tabMenuPosition_.width-5*4)/3, 25, "Change");
	newButton->callback(callbackVariablesChangeMesh, (void *) newButton);
	variablesChangeMesh_ = newButton;

	newButton = new Fl_Button(variablesChangeMesh_->x()+variablesChangeMesh_->w()+5*1, variablesChangeMesh_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Create");
	newButton->callback(callbackVariablesCreateMesh, (void *) newButton);
	variablesCreateMesh_ = newButton;

	newButton = new Fl_Button(variablesCreateMesh_->x()+variablesCreateMesh_->w()+5*1, variablesCreateMesh_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Remove");
	newButton->callback(callbackVariablesRemoveMesh, (void *) newButton);
	variablesRemoveMesh_ = newButton;

/////////////////////////////////////////

	newBrowser = new Fl_Hold_Browser(variablesChangeMesh_->x(), variablesChangeMesh_->y()+variablesChangeMesh_->h()+5*10, tabMenuPosition_.width*2/5, 5*45, "PDBs:");
	newBrowser->align(FL_ALIGN_LEFT | FL_ALIGN_TOP);
	newBrowser->clear();
	newBrowser->callback(callbackVariablesPdb, (void *) newBrowser);
	variablesPdb_ = newBrowser;

	newTextInput = new TextInput(variablesPdb_->x()+variablesPdb_->w(), variablesPdb_->y(), (tabMenuPosition_.width-variablesPdb_->w()-5*3)/2, 5*5, "Name:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbName_ = newTextInput;

	newTextInput = new TextInput(variablesPdbName_->x()+variablesPdbName_->w(), variablesPdbName_->y(), variablesPdbName_->w()-5*5, 5*5, "Path:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbPath_ = newTextInput;
	newButton = new Fl_Button(variablesPdbPath_->x()+variablesPdbPath_->w(), variablesPdbPath_->y(), 5*6, 5*5, "Pick");
	newButton->callback(callbackVariablesPdbPathPick, (void *) newButton);
	variablesPdbPathPick_ = newButton;

	newTextInput = new TextInput(variablesPdbName_->x(), variablesPdbName_->y()+5*10, variablesPdbName_->w(), 5*5, "Rad. path:");
	newTextInput->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbRadiusPath_ = newTextInput;

	newChoice = new Fl_Choice(variablesPdbRadiusPath_->x()+variablesPdbRadiusPath_->w(), variablesPdbRadiusPath_->y(), variablesPdbRadiusPath_->w(), 5*5, "Rad. type:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("united");
	newChoice->add("explicit");
	variablesPdbRadiusType_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbRadiusPath_->x(), variablesPdbRadiusPath_->y()+5*10, variablesPdbRadiusPath_->w(), 5*5, "Center:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("false");
	newChoice->add("true");
	newChoice->value(1);
	variablesPdbCenter_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbCenter_->x()+variablesPdbCenter_->w(), variablesPdbCenter_->y(), variablesPdbCenter_->w(), 5*5, "Center type:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	newChoice->add("arithmetic");
	newChoice->add("mass");
	newChoice->add("(none)");
	newChoice->value(1);
	variablesPdbCenterType_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbName_->x(), variablesPdbCenter_->y()+5*10, variablesPdbName_->w(), 5*5, "Assign node:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbAssignNode_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbName_->x()+variablesPdbName_->w(), variablesPdbCenter_->y()+5*10, variablesPdbName_->w(), 5*5, "Node mode:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbNodeMode_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbName_->x(), variablesPdbAssignNode_->y()+5*10, variablesPdbName_->w(), 5*5, "Sphere mesh:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbSphereMesh_ = newChoice;

	newChoice = new Fl_Choice(variablesPdbName_->x()+variablesPdbName_->w(), variablesPdbAssignNode_->y()+5*10, variablesPdbName_->w(), 5*5, "Ball mesh:");
	newChoice->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	variablesPdbStickMesh_ = newChoice;



	newButton = new Fl_Button(variablesPdb_->x(), variablesPdb_->y()+variablesPdb_->h()+5*1, (tabMenuPosition_.width-5*4)/3, 25, "Change");
	newButton->callback(callbackVariablesChangePdb, (void *) newButton);
	variablesChangePdb_ = newButton;

	newButton = new Fl_Button(variablesChangePdb_->x()+variablesChangePdb_->w()+5*1, variablesChangePdb_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Create");
	newButton->callback(callbackVariablesCreatePdb, (void *) newButton);
	variablesCreatePdb_ = newButton;

	newButton = new Fl_Button(variablesCreatePdb_->x()+variablesCreatePdb_->w()+5*1, variablesCreatePdb_->y(), (tabMenuPosition_.width-5*4)/3, 25, "Remove");
	newButton->callback(callbackVariablesRemovePdb, (void *) newButton);
	variablesRemovePdb_ = newButton;

	newButton = new Fl_Button(variablesPdb_->x(), variablesChangePdb_->y()+variablesChangePdb_->h()+5*1, (tabMenuPosition_.width-5*4)/3, 25, "Create MS");
	newButton->callback(callbackVariablesPdbCreateMs, (void *) newButton);
	variablesPdbCreateMs_ = newButton;

	newTab->hide();
	newTab->end();
	tabList_.push_back(newTab);
}
