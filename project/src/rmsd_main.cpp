/*
 * evaluate_scores.cpp
 *
 *  Created on: Mar 31, 2010
 *      Author: ivan
 */


#include "rmsd/rmsd_test.h"

using namespace std;



int main(int argc, char **argv)
{
	RMSDTestDrive rmsd;

	if (argc < 2)
		rmsd.rmsdRun("config.txt");
//		configuration.init("config.txt");
	else
		rmsd.rmsdRun(argv[1]);
//		configuration.init(argv[1]);

	return 0;
}
