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

	Docking docking(configuration);
	vector <pair<double, ScoreConfiguration> > scoresFFT;
	vector <pair<double, ScoreConfiguration> > scoresNonFFT;
	vector <pair<double, ScoreConfiguration> > scores;

	///---------------------------------------------
	///--------Docking search---------------
	///------------------------------------

	double radiusStart, radiusEnd;
    double t;
	configuration.getParameter("radius_search_start", t);
    // calibration to known radius
	for (radiusStart = 0.0; radiusStart +0.5 < t+1e-9; radiusStart += 0.5); 
	configuration.getParameter("radius_search_end", radiusEnd);

	vector<double> radius_set;
	for (double R = radiusStart; R < radiusEnd; R += 0.5){
		radius_set.push_back(R);
	}

	vector<double> MaxScoresRadius;
	docking.dockingQsearch(scores, radius_set, MaxScoresRadius);

	string scoresOutputFile;
	configuration.getParameter("scores_output_file", scoresOutputFile);

    docking.outputScores(scoresOutputFile, "# header...\n", scores);

    return 0;
}
