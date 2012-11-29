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
#include <sstream>
#include "predocking/predocking_test.h"
#include "docking/docking_test.h"
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

	std::stringstream ss(processParameter);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> splitProcesses(begin, end);

	for (unsigned long int i=0; i<splitProcesses.size(); i++)
	{
		printf ("Running process [%ld/%ld]: '%s'...\n", (i+1), splitProcesses.size(), splitProcesses[i].c_str());

		if (splitProcesses[i] == ((string) "predocking"))
		{
			PredockingTestDrive predocking;
			predocking.predockingRun(configPath);
		}
		else if (splitProcesses[i]== "predocking2grid")
		{
			PredockingTestDrive predocking;
			predocking.predockingToGrid(configPath);
		}
		else if (splitProcesses[i] == "docking")
		{
			DockingTestDrive docking;
			docking.dockingRun(configPath);

	/*
			Docking justDoIt(configuration);

			fprintf(stderr, "Starting docking...\n");

			vector <pair<double, ScoreConfiguration> > scores;
			justDoIt.dockingSearch(scores);

			string scoresOutputFile;
			configuration.getParameter("scores_output_file", scoresOutputFile);

			justDoIt.outputScores(scoresOutputFile, "", scores);
	*/
		}
		else if (splitProcesses[i] == "coef2grid")
		{
			PredockingTestDrive predocking;
			predocking.coefToGrid(configPath);
		}

		printf ("...finished process [%ld/%ld]: '%s'!\n\n", (i+1), splitProcesses.size(), splitProcesses[i].c_str());
	}

	return 0;
}
