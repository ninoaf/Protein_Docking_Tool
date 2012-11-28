/*
 * guicallbackspdt.cpp
 *
 *  Created on: Jun 8, 2010
 *      Author: ivan
 */

#include "vmolgui.h"
#include "../command/vmolcommand.h"
#include "../predocking/predocking_test.h"
#include "../docking/docking_test.h"
#include "../docking/docking.h"
#include "../math/evaluatescores.h"
#include "../pdbwriter/pdbwriter.h"
#include "../math/axisalignment.h"
#include "../math/evaluatescores.h"

using namespace std;



void VmolGui::callbackPdtConfigPathPick(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Open config file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->pdtConfigPath_->value(newFileChooser.value());

//		VmolGui::getInstance()->pdtLoadProteinCoefficients_->do_callback();
	}
}

void VmolGui::callbackPdtPredocking(Fl_Widget *w, void *data)
{
	PredockingTestDrive predocking;

	predocking.predockingRun(((string) (VmolGui::getInstance()->pdtConfigPath_->value())));
}

void VmolGui::callbackPdtDocking(Fl_Widget *w, void *data)
{
	DockingTestDrive docking(((string) (VmolGui::getInstance()->pdtConfigPath_->value())));
}

void VmolGui::callbackPdtCalculateCoefficients(Fl_Widget *w, void *data)
{
}

void VmolGui::callbackPdtScoreConformation(Fl_Widget *w, void *data)
{
	char currentScoreChar[100];
	int rInt=0;
	double r=0.0f, betaReceptor=0.0f, gammaReceptor=0.0f, alphaLigand=0.0f, betaLigand=0.0f, gammaLigand=0.0f;
	double currentScore=0.0f;
	double piover180=3.141592653f/180.0f;
	string currentScoreString;
	string translationName, receptorRotationName, ligandRotationName;
	Vector3 *translation;
	EulerVector3 *receptorRotation=NULL, *ligandRotation=NULL;

	if (VmolGui::getInstance()->pdtActiveReceptor_->value()<=0 || VmolGui::getInstance()->pdtActiveLigand_->value()<=0 ||
		VmolGui::getInstance()->pdtLigandTranslation_->value()<=0 || VmolGui::getInstance()->pdtReceptorRotation_->value()<=0 ||
		VmolGui::getInstance()->pdtLigandRotation_->value()<=0)
		return;

	translationName = VmolGui::getInstance()->pdtLigandTranslation_->text(VmolGui::getInstance()->pdtLigandTranslation_->value());
	receptorRotationName = VmolGui::getInstance()->pdtReceptorRotation_->text(VmolGui::getInstance()->pdtReceptorRotation_->value());
	ligandRotationName = VmolGui::getInstance()->pdtLigandRotation_->text(VmolGui::getInstance()->pdtLigandRotation_->value());

	translation = (Vector3 *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_VECTOR3, translationName);
	receptorRotation = (EulerVector3 *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_EULER_VECTOR3, receptorRotationName);
	ligandRotation = (EulerVector3 *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_EULER_VECTOR3, ligandRotationName);

	r = translation->z;
	rInt = (int) r;
	if ((r - rInt) < 0.25)
		r = rInt;
	else if ((r - rInt) > 0.75)
		r = rInt + 1.0f;
	else
		r = rInt + 0.5f;

	if (r > 50.0f)
	{
		printf ("Radius is greater than maximal allowed (r = %.1f)! Radius of 50 angstrems will be used.\n", r);
		r = 50.0f;
	}
	else if (r < 0.0f)
	{
		printf ("Radius is smaller than minimal allowed (r = %.1f)! Radius of 0 angstrems will be used.\n", r);
		r = 0.0f;
	}

//	printf ("r = %f\n");

	betaReceptor = receptorRotation->beta * piover180;
	gammaReceptor = receptorRotation->gamma * piover180;
	alphaLigand = ligandRotation->alpha * piover180;
	betaLigand = ligandRotation->beta * piover180;
	gammaLigand = ligandRotation->gamma * piover180;

//	ScoreConfiguration scoreConfiguration(r, betaReceptor, gammaReceptor, alphaLigand, betaLigand, gammaLigand);
	currentScore = VmolGui::getInstance()->docking_->scoreIt(r, betaReceptor, gammaReceptor, alphaLigand, betaLigand, gammaLigand);

	sprintf (currentScoreChar, "%.2lf", currentScore);
	VmolGui::getInstance()->currentScore_ = currentScoreChar;
	VmolGui::getInstance()->pdtCurrentScore_->label(VmolGui::getInstance()->currentScore_.c_str());

	printf ("score = %.2lf\n", currentScore);



//	DockingTestDrive docking(config);

/*
	Configuration dockingConfig;
	docking_config.init("data/scoreit_config.txt");
	docking = new Docking(dockingConfig);

	double r=0.0f, betaReceptor=0.0f, gammaReceptor=0.0f, alphaLigand=0.0f, betaLigand=0.0f, gammaLigand=0.0f;

	ScoreConfiguration score_configuration(r, betaReceptor, gammaReceptor, alphaLigand, betaLigand, gammaLigand);
	current_score = docking->scoreIt(score_configuration);
*/

}

void VmolGui::callbackPdtLoadScoresFile(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Open config file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolCommand::getInstance()->getScoresData().init();
		VmolCommand::getInstance()->getScoresData().loadScoresFromFile((string) newFileChooser.value());
	}
}

void VmolGui::callbackPdtEvaluateScores(Fl_Widget *w, void *data)
{
	int startingScore=0, maxNumScores=0;
	string receptorName, ligandName, complexName, outputPath;
	PdbFile complex, ligand, receptor; // complexCopy, ligandCopy, receptorCopy;
	PdbFile *ligandPointer, *receptorPointer, *complexPointer;

	ligandName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveLigand_->value());
	receptorName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveReceptor_->value());
	complexName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtCorrectComplex_->value());

	ligandPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, ligandName);
	receptorPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, receptorName);
	complexPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, complexName);

	if (ligandPointer==NULL || receptorPointer==NULL || complexPointer==NULL)
	{
		return;
	}

	ligand = *(ligandPointer);
	receptor = *(receptorPointer);
	complex = *(complexPointer);

	if (VmolGui::getInstance()->proteinCopySet_ == false)
	{
		VmolGui::getInstance()->ligandCopy_ = ligand;
		VmolGui::getInstance()->receptorCopy_ = receptor;
		VmolGui::getInstance()->complexCopy_ = complex;

		VmolGui::getInstance()->proteinCopySet_ = true;
	}

	outputPath = VmolGui::getInstance()->pdtEvaluationPath_->value();
	sscanf (VmolGui::getInstance()->pdtStartingScore_->value(), "%d", &startingScore);
	sscanf (VmolGui::getInstance()->pdtNumberOfScores_->value(), "%d", &maxNumScores);

//	evaluateScores(	complex, receptor, ligand, complexCopy, receptorCopy, ligandCopy, outputPath,
//					VmolCommand::getInstance()->getScoresData(), startingScore, maxNumScores);

	evaluateScores(	*(complexPointer), *(receptorPointer), *(ligandPointer), VmolGui::getInstance()->complexCopy_, VmolGui::getInstance()->receptorCopy_, VmolGui::getInstance()->ligandCopy_, outputPath,
					VmolCommand::getInstance()->getScoresData(), startingScore, maxNumScores);
}

void VmolGui::callbackPdtEvaluationPathPick(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Open config file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->pdtEvaluationPath_->value(newFileChooser.value());
	}
}

void VmolGui::callbackPdtLoadProteinCoefficients(Fl_Widget *w, void *data)
{
	int loadCoeffsFromFile=0;

	if (((string) VmolGui::getInstance()->pdtConfigPath_->value()) == "")
		return;

	Configuration config(((string) (VmolGui::getInstance()->pdtConfigPath_->value())));

	if (VmolGui::getInstance()->docking_)
		delete VmolGui::getInstance()->docking_;

	loadCoeffsFromFile = 1;
	config.setParameter("load_coeffs_from_file", loadCoeffsFromFile);

	VmolGui::getInstance()->docking_ = new Docking(config);
	VmolGui::getInstance()->docking_->calculateProteinCoefficients(-1);
}

void VmolGui::callbackPdtPickOutputPdbPath(Fl_Widget *w, void *data)
{
	Fl_File_Chooser newFileChooser(".", "*", Fl_File_Chooser::SINGLE, "Open config file...");

	newFileChooser.show();

	while(newFileChooser.shown())
	{
		Fl::wait();
	}

	if (newFileChooser.value() != NULL)
	{
		VmolGui::getInstance()->pdtOutputPdbPath_->value(newFileChooser.value());
	}
}

void VmolGui::callbackPdtGeneratePdb(Fl_Widget *w, void *data)
{
	int startingScore=0, maxNumScores=0;
	string receptorName, ligandName, complexName, outputPath;
	PdbFile *ligandPointer, *receptorPointer, *complexPointer;
	PdbWriter pdbWriter;

	ligandName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveLigand_->value());
	receptorName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveReceptor_->value());
	complexName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtCorrectComplex_->value());

	ligandPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, ligandName);
	receptorPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, receptorName);
	complexPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, complexName);

	if (ligandPointer==NULL || receptorPointer==NULL || complexPointer==NULL)
	{
		return;
	}

	outputPath = VmolGui::getInstance()->pdtOutputPdbPath_->value();
	sscanf (VmolGui::getInstance()->pdtStartingScore_->value(), "%d", &startingScore);
	sscanf (VmolGui::getInstance()->pdtNumberOfScores_->value(), "%d", &maxNumScores);

//	evaluateScores(	complex, receptor, ligand, complexCopy, receptorCopy, ligandCopy, outputPath,
//					VmolCommand::getInstance()->getScoresData(), startingScore, maxNumScores);

//	evaluateScores(	*(complexPointer), *(receptorPointer), *(ligandPointer), VmolGui::getInstance()->complexCopy_, VmolGui::getInstance()->receptorCopy_, VmolGui::getInstance()->ligandCopy_, outputPath,
//					VmolCommand::getInstance()->getScoresData(), startingScore, maxNumScores);

	pdbWriter.write(*receptorPointer, *ligandPointer, VmolCommand::getInstance()->getScoresData(), outputPath, (int) startingScore, (int) maxNumScores, false);
}

void VmolGui::callbackPdtLocalToGlobal(Fl_Widget *w, void *data)
{
	int startingScore=0, maxNumScores=0;
	string receptorName, ligandName;
	PdbFile *ligandPointer, *receptorPointer, *complexPointer;

	ligandName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveLigand_->value());
	receptorName = VmolGui::getInstance()->pdtActiveLigand_->text(VmolGui::getInstance()->pdtActiveReceptor_->value());

	ligandPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, ligandName);
	receptorPointer = (PdbFile *) VmolCommand::getInstance()->findVariable(COMMAND_VAR_PDB, receptorName);

	if (ligandPointer==NULL || receptorPointer==NULL)
	{
		return;
	}

	centerWithAlignment(*receptorPointer, *ligandPointer);
}
