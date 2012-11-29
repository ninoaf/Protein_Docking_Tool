/*
 * docking_test.h
 *
 *  Created on: Jun 8, 2010
 *      Author: ivan
 */

#ifndef DOCKING_TEST_H_
#define DOCKING_TEST_H_


#include "docking.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "../configuration/configuration.h"



class DockingTestDrive : Docking
{
public:
	DockingTestDrive();
	DockingTestDrive(std::string configPath);
	DockingTestDrive(Configuration& config);

	/*
	 * vraca score konfiguracije i 2 scorea dobivena sa scoreIt-om na razlicitim orderima
	 */
//	void stericScanResearch(vector<pair<pair<double,double>, ScoreConfiguration> >& scores);
	void dockingRun(std::string configPath);
};

#endif /* DOCKING_TEST_H_ */
