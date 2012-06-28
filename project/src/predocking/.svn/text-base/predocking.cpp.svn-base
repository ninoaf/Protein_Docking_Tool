/*
 * predocking.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: ivan
 */

#include "predocking.h"



Predocking::Predocking()
{

}

Predocking::~Predocking()
{

}

void Predocking::Init()
{

}



bool Predocking::parsePDB(PdbFile *pdbFile, char *sourcePath, char *destinationPath, char *radiiPath)
{
//	string log_message;

	pdbFile->Init(sourcePath);

	if (!pdbFile->LoadAtmtypenumbers((char *) radiiPath))
	{
/*
		log_message="PDB ";
		log_message += source_path;
		log_message += " was NOT SUCCESSFULLY loaded and parsed! Could not find the radius description file.";
		Error_Report(pdt_log_file, log_message, "ERROR");
*/

		return false;
	}

	pdbFile->UseUnitedRadius();
	pdbFile->Import();

	if (!pdbFile->SaveCoords(destinationPath))
	{
/*
		log_message="PDB ";
		log_message += source_path;
		log_message += " was NOT SUCCESSFULLY loaded and parsed! Could not save atom coordinates to a file.";
		Error_Report(pdt_log_file, log_message, "ERROR");
*/

		return false;
	}

/*
	log_message="PDB ";
	log_message += source_path;
	log_message += " was successfully loaded and parsed.";
	Log_Append(pdt_log_file, log_message);
*/

	return true;
}

bool Predocking::getMolecularSurface(MSMSWrapper *wrapper, string path)
{
	wrapper->init();
	return wrapper->load((char *) path.c_str());
}

bool Predocking::getSurfaceSkin(Grid *skin, MSMSWrapper *wrapper, double microDelta, double delta, double radius, string skinPath)
{
	skin->generateSurfaceGrid(*wrapper, microDelta, delta, radius);
	return (skin->exportToFile(skinPath) > 0);
}

bool Predocking::getCoefficients(Coefficients *coeff, Grid *skin, int order, string path)
{
	coeff->init(order);
	coeff->calculateFromGrid(*skin);
	return (coeff->exportToFile(path) > 0);
}

void Predocking::runPredocking(Configuration &config)
{
	int order=0;
	double gridSize=0.0f, gridCellSize=0.0f;
	double microDelta=0.0f, delta=0.0f, innerRadius=0.0f, outerRadius=0.0f;
	string ligandPath, parsedLigandPath, radiiPath, receptorPath, parsedReceptorPath;
	string ligandInnerSkinPath, ligandOuterSkinPath, receptorInnerSkinPath, receptorOuterSkinPath;
	string ligandInflatedInnerPath, ligandInflatedOuterPath, receptorInflatedInnerPath, receptorInflatedOuterPath;
	string ligandInnerSkinCoeffPath, ligandOuterSkinCoeffPath, receptorInnerSkinCoeffPath, receptorOuterSkinCoeffPath;
	PdbFile ligand, receptor;
	MSMSWrapper wrapperLigand, wrapperReceptor;
	Coefficients coeffLigandInner, coeffLigandOuter, coeffReceptorInner, coeffReceptorOuter;

	config.getParameter("stranica_grida", gridSize);
	config.getParameter("stranica_celije", gridCellSize);

	Grid skinLigandInner(gridSize, gridCellSize), skinLigandOuter(gridSize, gridCellSize), skinReceptorInner(gridSize, gridCellSize), skinReceptorOuter(gridSize, gridCellSize);
	Grid inflatedSkinLigandInner(gridSize, gridCellSize), inflatedSkinLigandOuter(gridSize, gridCellSize), inflatedSkinReceptorInner(gridSize, gridCellSize), inflatedSkinReceptorOuter(gridSize, gridCellSize);

///////////////////////////////////////////////////////
////////////// PARSING PDB FILES //////////////////////
///////////////////////////////////////////////////////
	config.getParameter("ligand", ligandPath);
	config.getParameter("parsed_ligand", parsedLigandPath);
	config.getParameter("radii_path", radiiPath);
	printf ("Loading ligand %s...", ligandPath.c_str());
	if ((parsePDB(&ligand, (char *) ligandPath.c_str(), (char *) parsedLigandPath.c_str(), (char *) radiiPath.c_str())))
		printf ("success!\n");
	else
		printf ("FAILED!\n");

	config.getParameter("receptor", receptorPath);
	config.getParameter("parsed_receptor", parsedReceptorPath);
	config.getParameter("radii_path", radiiPath);
	printf ("Loading receptor %s...", receptorPath.c_str());
	if ((parsePDB(&receptor, (char *) receptorPath.c_str(), (char *) parsedReceptorPath.c_str(), (char *) radiiPath.c_str())))
		printf ("success!\n");
	else
		printf ("FAILED!\n");

///////////////////////////////////////////////////////
////////////// MOLECULAR SURFACE //////////////////////
///////////////////////////////////////////////////////

	printf ("Molecular surface...\n");
	config.getParameter("parsed_ligand", parsedLigandPath);
	config.getParameter("parsed_receptor", parsedReceptorPath);
	getMolecularSurface(&wrapperLigand, parsedLigandPath);
	getMolecularSurface(&wrapperReceptor, parsedReceptorPath);

//	wrapperLigand.init();
//	wrapperReceptor.init();
//	wrapperLigand.load((char *) t1.c_str());
//	wrapperReceptor.load((char *) t2.c_str());
	printf ("...OK.\n");

///////////////////////////////////////////////////////
////////////// SKIN GRID //////////////////////////////
///////////////////////////////////////////////////////
	config.getParameter("microdelta", microDelta);
	config.getParameter("delta", delta);
	config.getParameter("inner_radius", innerRadius);
	config.getParameter("outer_radius", outerRadius);

	printf ("Generating skins - ligand...\n");
	config.getParameter("ligand_inner_skin", ligandInnerSkinPath);
	config.getParameter("ligand_outer_skin", ligandOuterSkinPath);
	getSurfaceSkin(&skinLigandInner, &wrapperLigand, microDelta, delta, innerRadius, ligandInnerSkinPath);
	getSurfaceSkin(&skinLigandOuter, &wrapperLigand, microDelta, delta, outerRadius, ligandOuterSkinPath);

//	skinLigandInner.generateSurfaceGrid(wrapperLigand, microDelta, delta, innerRadius);
//	skinLigandInner.exportToFile(ligandInnerSkinPath);
//	skinLigandOuter.generateSurfaceGrid(wrapperLigand, microDelta, delta, outerRadius);
//	skinLigandOuter.exportToFile(ligandOuterSkinPath);
	printf ("...OK.\n");

	printf ("Generating skins - receptor...\n");
	config.getParameter("receptor_inner_skin", receptorInnerSkinPath);
	config.getParameter("receptor_outer_skin", receptorOuterSkinPath);
	getSurfaceSkin(&skinReceptorInner, &wrapperReceptor, microDelta, delta, innerRadius, receptorInnerSkinPath);
	getSurfaceSkin(&skinReceptorOuter, &wrapperReceptor, microDelta, delta, outerRadius, receptorOuterSkinPath);

//	skinReceptorInner.generateSurfaceGrid(wrapperReceptor, microDelta, delta, innerRadius);
//	skinReceptorInner.exportToFile(receptorInnerSkinPath);
//	skinReceptorOuter.generateSurfaceGrid(wrapperReceptor, microDelta, delta, outerRadius);
//	skinReceptorOuter.exportToFile(receptorOuterSkinPath);
	printf ("...OK.\n");





	inflatedSkinLigandInner = skinLigandInner;
	inflatedSkinLigandOuter = skinLigandOuter;
	inflatedSkinReceptorInner = skinReceptorInner;
	inflatedSkinReceptorOuter = skinReceptorOuter;

	config.getParameter("ligand_inflated_inner_skin", ligandInflatedInnerPath);
	config.getParameter("ligand_inflated_outer_skin", ligandInflatedOuterPath);
	inflatedSkinLigandInner.inflateGrid();
	inflatedSkinLigandInner.exportToFile(ligandInflatedInnerPath);
	inflatedSkinLigandOuter.inflateGrid();
	inflatedSkinLigandOuter.exportToFile(ligandInflatedOuterPath);

	config.getParameter("receptor_inflated_inner_skin", receptorInflatedInnerPath);
	config.getParameter("receptor_inflated_outer_skin", receptorInflatedOuterPath);
	inflatedSkinReceptorInner.inflateGrid();
	inflatedSkinReceptorInner.exportToFile(receptorInflatedInnerPath);
	inflatedSkinReceptorOuter.inflateGrid();
	inflatedSkinReceptorOuter.exportToFile(receptorInflatedOuterPath);

///////////////////////////////////////////////////////
////////////// CALCULATING COEFFICIENTS ///////////////
///////////////////////////////////////////////////////
	config.getParameter("red_sf_harmonika", order);

	printf ("Calculating coefficients - ligand inner...\n");
	config.getParameter("ligand_inner_skin_coeffs", ligandInnerSkinCoeffPath);
	getCoefficients(&coeffLigandInner, &skinLigandInner, order, ligandInnerSkinCoeffPath);
//	coeffLigandInner.init(order);
//	coeffLigandInner.calculateFromGrid(skinLigandInner);
//	coeffLigandInner.exportToFile(ligandInnerSkinCoeffPath);
	printf ("...OK.\n");
	printf ("Calculating coefficients - ligand outer...\n");
	config.getParameter("ligand_outer_skin_coeffs", ligandOuterSkinCoeffPath);
	getCoefficients(&coeffLigandOuter, &skinLigandOuter, order, ligandOuterSkinCoeffPath);
//	coeffLigandOuter.init(order);
//	coeffLigandOuter.calculateFromGrid(skinLigandOuter);
//	coeffLigandOuter.exportToFile(ligandOuterSkinCoeffPath);
	printf ("...OK.\n");

	printf ("Calculating coefficients - Receptor inner...\n");
	config.getParameter("receptor_inner_skin_coeffs", receptorInnerSkinCoeffPath);
	getCoefficients(&coeffReceptorInner, &skinReceptorInner, order, receptorInnerSkinCoeffPath);
//	coeffReceptorInner.init(order);
//	coeffReceptorInner.calculateFromGrid(skinReceptorInner);
//	coeffReceptorInner.exportToFile(receptorInnerSkinCoeffPath);
	printf ("...OK.\n");
	printf ("Calculating coefficients - Receptor outer...\n");
	config.getParameter("receptor_outer_skin_coeffs", receptorOuterSkinCoeffPath);
	getCoefficients(&coeffReceptorOuter, &skinReceptorOuter, order, receptorOuterSkinCoeffPath);
//	coeffReceptorOuter.init(order);
//	coeffReceptorOuter.calculateFromGrid(skinReceptorOuter);
//	coeffReceptorOuter.exportToFile(receptorOuterSkinCoeffPath);
	printf ("...OK.\n");

	printf ("\nFinished predocking!\n");

    /*
    Grid temp(60.0, 1.0);
    temp.generateFromCoefficients(coeffLigandInner);
    temp.exportToFile("data/grid/predock_umjetni_ligand_inner.grid");
    temp.generateFromCoefficients(coeffLigandOuter);
    temp.exportToFile("data/grid/predock_umjetni_ligand_outer.grid");
    temp.generateFromCoefficients(coeffReceptorInner);
    temp.exportToFile("data/grid/predock_umjetni_receptor_inner.grid");
    temp.generateFromCoefficients(coeffReceptorOuter);
    temp.exportToFile("data/grid/predock_umjetni_receptor_outer.grid");
    */
/*
	config.getParameter("stranica_grida", d1);
	config.getParameter("stranica_celije", d2);
	Grid test_grid(d1, d2);
	test_grid.generateFromCoefficients(coeffLigandOuter);
	test_grid.exportToFile("test_protein_grid_igor.grid");
	test_grid.dump("test_protein_grid_igor.grid.txt");
*/
}
