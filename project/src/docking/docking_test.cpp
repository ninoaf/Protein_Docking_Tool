/*
 * docking_test.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: canadi
 */

#include "docking_test.h"



using namespace std;

DockingTestDrive::DockingTestDrive(std::string configPath) : Docking(configPath)
{
	Configuration config;

	config.init(configPath);

	vector <pair<double, ScoreConfiguration> > scores;
	dockingSearch(scores);

	string scoresOutputFile;
	config.getParameter("scores_output_file", scoresOutputFile);

	outputScores(scoresOutputFile, "# header...\n", scores);
}

DockingTestDrive::DockingTestDrive(Configuration& config) : Docking(config)
{
}

void DockingTestDrive::dockingRun(std::string configPath)
{
	Configuration config;

	config.init(configPath);

	Docking docking(config);

	vector <pair<double, ScoreConfiguration> > scores;
	docking.dockingSearch(scores);

	string scoresOutputFile;
	config.getParameter("scores_output_file", scoresOutputFile);

    docking.outputScores(scoresOutputFile, "# header...\n", scores);
}

/*
/*
 * vraca score konfiguracije i 2 scorea dobivena sa scoreIt-om na razlicitim orderima
 *
void DockingTestDrive::stericScanResearch(vector<pair<pair<double,double>, ScoreConfiguration> >& scores)
{
	vector<ScoreConfiguration> inputConfigurations;
	vector <pair<double, ScoreConfiguration> > tmpScores;

	fprintf(stderr, "Starting research version of steric scan...\n");
	fprintf(stderr, "Generating configurations...\n");

	generateConfigurations(inputConfigurations);

	fprintf(stderr, "Starting steric scan...\n");
	fprintf(stderr, "Starting prescan on order %d...\n", preOrder_);
	dockingSearch(preOrder_, stericPenalty_, inputConfigurations, tmpScores, (int)((double)inputConfigurations.size() * (survivalPercentage_ / 100.0)));

	fprintf(stderr, "Done... Eliminating configurations. Limiting to %u configurations..\n", (unsigned int)tmpScores.size());
	inputConfigurations.resize(tmpScores.size());

	map <ScoreConfiguration, double> scoresMap;

	for (unsigned int i = 0; i < tmpScores.size(); ++i)
	{
		tmpScores[i].second.alphaLigand = 0.0;
		inputConfigurations[i] = tmpScores[i].second;
		scoresMap[tmpScores[i].second] = tmpScores[i].first;
	}

	fprintf(stderr, "Starting real docking search on order %d...\n", order_);
	dockingSearch(order_, penalty_, inputConfigurations, tmpScores, scoresSize_);

	scores.resize(tmpScores.size());
	for (unsigned int i = 0; i < tmpScores.size(); ++i)
	{
		tmpScores[i].second.alphaLigand = 0.0;
		scores[i] = make_pair (make_pair(tmpScores[i].first, scoresMap[tmpScores[i].second]), tmpScores[i].second);
	}

	fprintf(stderr, "Finished research steric scan...\n");
}
*/
