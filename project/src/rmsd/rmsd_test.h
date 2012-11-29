/*
 * rmsd_test.h
 *
 *  Created on: Nov 29, 2012
 *      Author: ivan
 */

#ifndef RMSD_TEST_H_
#define RMSD_TEST_H_

#include <string>
#include <vector>
#include <math.h>
#include "../configuration/configuration.h"
#include "../structures/structures.h"
#include "../pdbwriter/pdbwriter.h"
#include "../pdbparser/pdbparser.h"



class RMSDTestDrive
{
public:
	RMSDTestDrive();

	void rmsdRun(std::string configPath);
};



#endif /* RMSD_TEST_H_ */
