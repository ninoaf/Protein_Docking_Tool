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
#include "predocking/predocking_test.h"
#include "docking/docking.h"
#include "configuration/configuration.h"
#include "pdbwriter/pdbwriter.h"

using namespace std;



int main(int argc, char **argv)
{
	Configuration configuration;
	string configPath;
	string processParameter;

	configPath = "config.txt";

	if (argc > 1)
	{
		configPath = argv[1];
	}

	configuration.init(configPath);
	configuration.getParameter("process", processParameter);

	if (processParameter == ((string) "predocking"))
	{
		PredockingTestDrive predocking;
		predocking.predockingRun(configPath);
	}
	else if (processParameter == "predocking2grid")
	{
		PredockingTestDrive predocking;
		predocking.predockingToGrid(configPath);
	}
	else if (processParameter == "docking")
	{
		Docking justDoIt(configuration);

		fprintf(stderr, "Starting docking...\n");

		vector <pair<double, ScoreConfiguration> > scores;
		justDoIt.dockingSearch(scores);

		string scoresOutputFile;
		configuration.getParameter("scores_output_file", scoresOutputFile);

		justDoIt.outputScores(scoresOutputFile, "", scores);
	}
	else if (processParameter == "coef2grid")
	{
		PredockingTestDrive predocking;
		predocking.coefToGrid(configPath);
	}

	return 0;
}
