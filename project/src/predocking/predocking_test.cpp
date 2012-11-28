/*
 * predocking_test.cpp
 *
 *  Created on: Mar 9, 2010
 *      Author: canadi
 */

#include "predocking_test.h"



void PredockingTestDrive::backToGrid(std::string configPath)
{
	Configuration config(configPath);

	Predocking predockLigand(config, CALCULATE), predockReceptor(config, CALCULATE);

	string ligandPDB, receptorPDB;
	Protein ligand, receptor;
	string ligandInner, ligandOuter;
	string receptorInner, receptorOuter;
	int order;

	config.getParameter("ligand", ligandPDB);
	config.getParameter("receptor", receptorPDB);
	config.getParameter("order_sh", order);

	fprintf(stderr, "Calculating Ligand skins...\n");
	predockLigand.calculateSkins(ligandPDB);
	fprintf(stderr, "Calculating Receptor skins...\n");
	predockReceptor.calculateSkins(receptorPDB);

	predockLigand.getProtein(order, ligand);
	predockReceptor.getProtein(order, receptor);

	Grid testGrid(60,1);

	testGrid.generateFromCoefficients(ligand.getOuterSkin());
	testGrid.exportToFile("data/grid/testligand_outer.grid");

	testGrid.generateFromCoefficients(ligand.getInnerSkin());
	testGrid.exportToFile("data/grid/testligand_inner.grid");

	testGrid.generateFromCoefficients(receptor.getOuterSkin());
	testGrid.exportToFile("data/grid/testreceptor_outer.grid");

	testGrid.generateFromCoefficients(receptor.getInnerSkin());
	testGrid.exportToFile("data/grid/testreceptor_inner.grid");
}
/* predockingRun test
 *
 * ovaj test ucitava podatke o PDB fajlovima i parametre iz config.txt,
 * izracunava koeficijente skinova, i vraca ih u fajlove prema config.txt-u
 * */
void PredockingTestDrive::predockingRun(std::string configPath)
{
	Configuration config(configPath);

	Predocking predockLigand(config, CALCULATE), predockReceptor(config, CALCULATE);

	string ligandPDB, receptorPDB;
	Protein ligand, receptor;
	string ligandInner, ligandOuter;
	string receptorInner, receptorOuter;
	int order;

	config.getParameter("ligand", ligandPDB);
	config.getParameter("receptor", receptorPDB);
	config.getParameter("order_sh", order);

	fprintf(stderr, "Calculating Ligand skins...\n");
	predockLigand.calculateSkins(ligandPDB);
	fprintf(stderr, "Calculating Receptor skins...\n");
	predockReceptor.calculateSkins(receptorPDB);

	predockLigand.getProtein(order, ligand);
	predockReceptor.getProtein(order, receptor);

	string tmp;
	config.getParameter("ligand_outer_skin_coeffs", tmp);
	ligand.getOuterSkin().exportToFile(tmp);
	config.getParameter("ligand_inner_skin_coeffs", tmp);
	ligand.getInnerSkin().exportToFile(tmp);
	config.getParameter("receptor_outer_skin_coeffs", tmp);
	receptor.getOuterSkin().exportToFile(tmp);
	config.getParameter("receptor_inner_skin_coeffs", tmp);
	receptor.getInnerSkin().exportToFile(tmp);
}

void PredockingTestDrive::predockingToGrid(std::string configPath)
{
	Configuration config(configPath);

	Predocking predockLigand(config, CALCULATE), predockReceptor(config, CALCULATE);

	double gridSize=0.0f, gridCellSize=0.0f;
	string ligandPDB, receptorPDB;
	string ligandName, receptorName;
	Protein ligand, receptor;
	string ligandInner, ligandOuter;
	string receptorInner, receptorOuter;
	string gridPath;
	int order;

	config.getParameter("ligand", ligandPDB);
	config.getParameter("receptor", receptorPDB);
	config.getParameter("order_sh", order);
	config.getParameter("grid_size", gridSize);
	config.getParameter("grid_cell_size", gridCellSize);

	fprintf(stderr, "Calculating Ligand skins...\n");
	predockLigand.calculateSkins(ligandPDB);
	fprintf(stderr, "Calculating Receptor skins...\n");
	predockReceptor.calculateSkins(receptorPDB);

	predockLigand.getProtein(order, ligand);
	predockReceptor.getProtein(order, receptor);

	string tmp;
	config.getParameter("ligand_outer_skin_coeffs", tmp);
	ligand.getOuterSkin().exportToFile(tmp);
	config.getParameter("ligand_inner_skin_coeffs", tmp);
	ligand.getInnerSkin().exportToFile(tmp);
	config.getParameter("receptor_outer_skin_coeffs", tmp);
	receptor.getOuterSkin().exportToFile(tmp);
	config.getParameter("receptor_inner_skin_coeffs", tmp);
	receptor.getInnerSkin().exportToFile(tmp);



	if (gridPath[gridPath.size()-1] != '/')
		gridPath = gridPath + "/";

	receptorName = trimFileName(receptorPDB);
	ligandName = trimFileName(ligandPDB);



	Grid grid(gridSize, gridCellSize);

	grid.generateFromCoefficients(ligand.getOuterSkin());
	grid.exportToFile(gridPath + ligandName + "_outer.grid");

	grid.generateFromCoefficients(ligand.getInnerSkin());
	grid.exportToFile(gridPath + ligandName + "_inner.grid");

	grid.generateFromCoefficients(receptor.getOuterSkin());
	grid.exportToFile(gridPath + receptorName + "_outer.grid");

	grid.generateFromCoefficients(receptor.getInnerSkin());
	grid.exportToFile(gridPath + receptorName + "_inner.grid");
}

void PredockingTestDrive::coefToGrid(std::string configPath)
{
	Configuration config(configPath);

	Predocking predockLigand(config, CALCULATE), predockReceptor(config, CALCULATE);

	double gridSize=0.0f, gridCellSize=0.0f;
	string ligandPDB, receptorPDB;
	string ligandName, receptorName;
	Coefficients ligandInner, ligandOuter, receptorInner, receptorOuter;
	string gridPath;
	int order;

	config.getParameter("ligand", ligandPDB);
	config.getParameter("receptor", receptorPDB);
	config.getParameter("order_sh", order);
	config.getParameter("grid_size", gridSize);
	config.getParameter("grid_cell_size", gridCellSize);



	string tempPath;
	config.getParameter("ligand_outer_skin_coeffs", tempPath);
	ligandOuter.importFromFile(tempPath);
	config.getParameter("ligand_inner_skin_coeffs", tempPath);
	ligandInner.importFromFile(tempPath);
	config.getParameter("receptor_outer_skin_coeffs", tempPath);
	receptorOuter.importFromFile(tempPath);
	config.getParameter("receptor_inner_skin_coeffs", tempPath);
	receptorInner.importFromFile(tempPath);



	if (gridPath[gridPath.size()-1] != '/')
		gridPath = gridPath + "/";

	receptorName = trimFileName(receptorPDB);
	ligandName = trimFileName(ligandPDB);



	Grid grid(gridSize, gridCellSize);

	grid.generateFromCoefficients(ligandOuter);
	grid.exportToFile(gridPath + ligandName + "_outer.grid");

	grid.generateFromCoefficients(ligandInner);
	grid.exportToFile(gridPath + ligandName + "_inner.grid");

	grid.generateFromCoefficients(receptorOuter);
	grid.exportToFile(gridPath + receptorName + "_outer.grid");

	grid.generateFromCoefficients(receptorInner);
	grid.exportToFile(gridPath + receptorName + "_inner.grid");
}

string PredockingTestDrive::trimFileName(string path)
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
