/*
 * docking_main.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: ivan
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include "docking/docking.h"
#include "configuration/configuration.h"
#include "pdbparser/pdbparser.h"

using namespace std;

int main(int argc, char **argv){
	Configuration configuration;

	if (argc < 2)
	{
		configuration.init("config.txt");
	}else
	{
		configuration.init(argv[1]);
	}

	printf("Importing pqr file ... \n");
	char *strPQR = "3hfl_fv.pqr";
	PdbFile *pdb = new PdbFile(strPQR);
	pdb->Import(true);

	Grid *gridTmp = new Grid (80, 1) ;
	pdb->PutChargesOnGrid(*gridTmp);

	gridTmp->exportToFile("gridCharge.out");


	
	/* //testni naboj
	
	gridTmp->generateTestCharge (+10);

	Coefficients *coeffCharge = new Coefficients(20);
	coeffCharge->calculateChargeCoeffsFromGrid(*gridTmp);

	Grid *gridRecTmp = new Grid ( 51, 1);
	gridRecTmp->generateFromETOCoefficients( *coeffCharge );
	gridRecTmp->exportToFile("gridCharge.out");*/

	
	
	return 0;
}

