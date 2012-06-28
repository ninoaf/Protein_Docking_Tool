/*
 * predocking_main.cpp
 *
 *  Created on: Oct 2, 2009
 *      Author: ivan
 */

#include "predocking/predocking.h"



int main(int argc, char **argv)
{
	Configuration config;
	Predocking predock;

	if (argc < 2)
	{
		config.init("config.txt");
	}
	else
	{
		config.init(argv[1]);
	}

//	PdbFile pdb;
//	MSMSWrapper wrapper;

//	predock.parsePDB(&pdb, (char *) "data/pdb/1crn.pdb", (char *) "novi_predocking_test.txt");
//	wrapper.load("novi_predocking_test.txt");

	predock.runPredocking(config);

//	printf("ja sam mali pas\n");

	return 0;
}
