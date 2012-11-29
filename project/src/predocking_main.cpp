/*
 * predocking_main.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: ivan
 */

// #include "predocking/predocking.h"
#include "predocking/predocking_test.h"
// #include "math/axisalignment.h"



int main(int argc, char **argv)
{
	PredockingTestDrive testDrive;

	if (argc < 2)
	{
		testDrive.predockingRun("config.txt");
	}
	else
	{
		testDrive.predockingRun(argv[1]);
	}

/*
	PredockingTestDrive testDrive;

	testDrive.backToGrid();

	return 0;
*/



/*
	Configuration config;

	if (argc < 2)
	{
		config.init("config.txt");
	}
	else
	{
		config.init(argv[1]);
	}

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

	predockLigand.parsePDB(ligandPDB.c_str(), ".tmpParsedLigand");
	predockReceptor.parsePDB(receptorPDB.c_str(), ".tmpParsedReceptor");

	if (center == 3)
	{
		centerWithAlignment(predockReceptor.getPdbFile(), predockLigand.getPdbFile());
	}

//	parsedLigand = "." + ligandPDB + ".parsed";
//	parsedReceptor = "." + receptorPDB + ".parsed";
//	predockLigand.calculateSurface(ligandPDB, parsedLigand.c_str());
//	predockReceptor.calculateSurface(receptorPDB, parsedReceptor.c_str());

	predockLigand.calculateSurface(ligandPDB, "data/adb/tmpParsedLigand.adb");
	predockReceptor.calculateSurface(receptorPDB, "data/adb/tmpParsedReceptor.adb");

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
*/

	return 0;
}
