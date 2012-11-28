//============================================================================
// Name        : longview_main.cpp
// Author      : Ivan Sovic
// Version     :
// Copyright   : Copyright Ivan Sovic, 2010.
// Description : Longview is THE visualizing tool, most powerfull of them all. Built as a part of the Protein Docking Tool system.
//============================================================================

#include <iostream>
#include "gui/glwindow.h"
#include "gui/vmolgui.h"
#include "command/vmolcommand.h"
#include "log/log.h"
#include "structures/structures.h"

#include "pdbwriter/pdbwriter.h"

#include "math/evaluatescores.h"

#include "math/axisalignment.h"
#include "pdbparser/pdbparser.h"

#include <ctime>
#include <sys/times.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

using namespace std;



int main(int argc, char **argv)
{
	bool runOnce=true;
	unsigned int currentScore=0;
	int limitFps=50;
	long int microseconds=0;
	clock_t oldTime, newTime;
	tms oldCpu, newCpu;
	string defaultScriptPath;

	Log::getInstance()->clearLog();

	defaultScriptPath = "data/system/defaultWorkspace.vsc";

	if (argc > 1)
	{
		defaultScriptPath = argv[1];
	}

//	printf ("1!\n");

	VmolGui::getInstance()->createGui();
//	VmolCommand::getInstance()->loadScript("data/scripts/scoreEvalDebug.vsc");

//	VmolCommand::getInstance()->loadScript("data/scripts/eulerRotation1.vsc");
//	printf ("2!\n");
	VmolCommand::getInstance()->loadScript(defaultScriptPath);
//	VmolCommand::getInstance()->loadScript("data/scripts/testScriptSceneGraph.vsc");

//	printf ("3!\n");

//	VmolCommand::getInstance()->loadScript("data/scripts/exportWorkspacea1.vsc");
//	VmolCommand::getInstance()->loadScript("data/scripts/emptyNodes.vsc");
//	VmolCommand::getInstance()->loadScript("data/scripts/testScript1.vsc");
/*
	ScoreLoader scoresData;



	string scorePath = (string) "data/scr/3hfl_umjetni1.scr";
	scorePath = "data/scr/3hfl_36_alfa_53/outputMPI.scr";

	if (scoresData.loadScoresFromFile(scorePath) == false)
	{
		printf ("Could not open scores file %s!\n", scorePath.c_str());
		return 1;
	}
*/

//	Fl::run();
/*
	PdbFile *complex=NULL, *ligand=NULL, *receptor=NULL;
	PdbFile complexCopy, ligandCopy, receptorCopy;



/*
*
	complex = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, "complex");
	ligand = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, "ligand");
	receptor = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, "receptor");

//	VmolGui::getInstance()->globalLigand = ligand;
//	VmolGui::getInstance()->globalReceptor = receptor;

//	centerAlignment1(*receptor, *ligand);
//	centerWithAlignment(*receptor, *ligand);

	complexCopy = *complex;
	ligandCopy = *ligand;
	receptorCopy = *receptor;
*/

/*
*/

//	double pi1=180.0f/3.14159f;
//	printf ("%.2f %.2f %.2f %.2f %.2f\n", 2.219089*pi1, 5.521052*pi1, 2.792527*pi1, 2.634373*pi1, 5.138709*pi1);

//	pdbWriter.write(scorePath, receptorPath, ligandPath, radiiPath, outputPath, startingScore, maxNumScores, centerAtoms);
//	PdbWriter pdbWriter;
//	pdbWriter.write(*receptor, *ligand,

//	printf ("Asd 0!\n");

	currentScore = 0;

	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variable[0] = VmolCommand::getInstance()->findVariable(COMMAND_VAR_VECTOR3, "vecLook1");
	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variableType[0] = COMMAND_VAR_VECTOR3;

	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variable[1] = VmolCommand::getInstance()->findVariable(COMMAND_VAR_VECTOR3, "vecLook1");
	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variableType[1] = COMMAND_VAR_VECTOR3;

//	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variable[1] = VmolCommand::getInstance()->findVariable(COMMAND_VAR_COLOR, "colorLigand");
//	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variableType[1] = COMMAND_VAR_COLOR;

	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variable[3] = VmolCommand::getInstance()->findVariable(COMMAND_VAR_COLOR, "colorLigand");
	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variableType[3] = COMMAND_VAR_COLOR;

	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variable[5] = VmolCommand::getInstance()->findVariable(COMMAND_VAR_COLOR, "colorLigand");
	VmolGui::getInstance()->getOglBox()[0]->getMouseEventBinds().variableType[5] = COMMAND_VAR_COLOR;

	VmolGui::getInstance()->refreshGui();



	limitFps = 30;

	for (;;)
	{
		oldTime = times(&oldCpu);

		if (VmolGui::getInstance()->mainWindow->visible())
		{
			if (!Fl::check()) break;
		}
		else
		{
			if (!Fl::wait()) break;
		}

/*
		if (runOnce == true)
		{
//			evaluateScores(complex, ligand, receptor, complexCopy, receptorCopy, ligandCopy, scoresData);
//			evaluateScores(	*complex, *receptor, *ligand, complexCopy, receptorCopy, ligandCopy,
//							(string) "data/rmsd/testScores1.rmsd", scoresData, 861+currentScore, 1);

			currentScore += 1;

//			if (currentScore >= 10)
				runOnce = false;
		}
*/

		VmolGui::getInstance()->refreshScore();
		VmolGui::getInstance()->drawViews(VmolCommand::getInstance()->getViewList());

		newTime = times(&newCpu);
		microseconds = ((1000/limitFps) - (newTime - oldTime)) * 1000;
		oldTime = newTime;

//			printf ("millis = %ld\tmicroSeconds = %ld\n", millis, microSeconds);

		if (microseconds>0 && microseconds<1000000)			// if microseconds<0 then more time than allowed has passed, but we also don't want to wait for more than a second (we probably want the FPS count to be higher than 1)
			usleep(microseconds);
	}

	return 0;
}
