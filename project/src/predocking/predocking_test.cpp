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
/*
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
*/

	Configuration config(configPath);

	Predocking predockLigand(config, CALCULATE), predockReceptor(config, CALCULATE);

	string ligandPDB, receptorPDB;
	string parsedLigand, parsedReceptor;
	Protein ligand, receptor;
	string ligandInner, ligandOuter;
	string receptorInner, receptorOuter;
	int order;
	int center=0;

	config.getParameter("ligand", ligandPDB);
	config.getParameter("receptor", receptorPDB);
	config.getParameter("order_sh", order);

	config.getParameter("ligand_inner_skin_coeffs", ligandInner);
	config.getParameter("ligand_outer_skin_coeffs", ligandOuter);
	config.getParameter("receptor_inner_skin_coeffs", receptorInner);
	config.getParameter("receptor_outer_skin_coeffs", receptorOuter);
	config.getParameter("center", center);

	config.getParameter("parsed_ligand", parsedLigand);
	config.getParameter("parsed_receptor", parsedReceptor);

//	predockLigand.parsePDB(ligandPDB.c_str(), ".tmpParsedLigand");
//	predockReceptor.parsePDB(receptorPDB.c_str(), ".tmpParsedReceptor");
	predockLigand.parsePDB(ligandPDB.c_str(), parsedLigand.c_str());
	predockReceptor.parsePDB(receptorPDB.c_str(), parsedReceptor.c_str());

	if (center == 3)
	{
		centerWithAlignment(predockReceptor.getPdbFile(), predockLigand.getPdbFile());
	}


//	predockLigand.calculateSurface(ligandPDB, "data/adb/tmpParsedLigand.adb");
//	predockReceptor.calculateSurface(receptorPDB, "data/adb/tmpParsedReceptor.adb");
	predockLigand.calculateSurface(ligandPDB, parsedLigand.c_str());
	predockReceptor.calculateSurface(receptorPDB, parsedReceptor.c_str());

	fprintf(stderr, "Calculating Ligand skins...\n");
//	predockLigand.calculateSkins(ligandPDB);
	predockLigand.calculateSkinsWithouthParsing();
	fprintf(stderr, "Calculating Receptor skins...\n");
//	predockReceptor.calculateSkins(receptorPDB);
	predockReceptor.calculateSkinsWithouthParsing();

	fprintf(stderr, "Calculating Ligand coefficients...\n");
	predockLigand.getProtein(order, ligand);
	fprintf(stderr, "Exporting Ligand coefficients to files: '%s', '%s'...\n", ligandInner.c_str(), ligandOuter.c_str());
	ligand.exportToFile(ligandInner, ligandOuter);

	fprintf(stderr, "Calculating Receptor coefficients...\n");
	predockReceptor.getProtein(order, receptor);
	fprintf(stderr, "Exporting Receptor coefficients to files: '%s', '%s'...\n", receptorInner.c_str(), receptorOuter.c_str());
	receptor.exportToFile(receptorInner, receptorOuter);
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




	fprintf(stderr, "Loading ligand and receptor coefficient files...\n");

	string tempPath;
	config.getParameter("ligand_outer_skin_coeffs", tempPath);
	fprintf(stderr, "\tligand_outer_skin_coeffs: '%s'\n", tempPath.c_str());
	ligandOuter.importFromFile(tempPath);
	config.getParameter("ligand_inner_skin_coeffs", tempPath);
	fprintf(stderr, "\tligand_inner_skin_coeffs: '%s'\n", tempPath.c_str());
	ligandInner.importFromFile(tempPath);
	config.getParameter("receptor_outer_skin_coeffs", tempPath);
	fprintf(stderr, "\treceptor_outer_skin_coeffs: '%s'\n", tempPath.c_str());
	receptorOuter.importFromFile(tempPath);
	config.getParameter("receptor_inner_skin_coeffs", tempPath);
	fprintf(stderr, "\treceptor_inner_skin_coeffs: '%s'\n", tempPath.c_str());
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
