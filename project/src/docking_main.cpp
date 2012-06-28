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
        vector<double> radius_subset;
	radius_subset.push_back( 30.5 );
	vector<double> MaxScoresRadius;

	string scoresOutputFileFFT;
        configuration.getParameter("scores_output_file", scoresOutputFileFFT);
	scoresOutputFileFFT += "_FFT.scr";

	string scoresOutputFileNonFFT;
	configuration.getParameter("scores_output_file", scoresOutputFileNonFFT);
        scoresOutputFileNonFFT += "_NonFFT.scr";

	if (1){

	docking.dockingSearch( scoresNonFFT, radius_subset, MaxScoresRadius);
	printf("DockingSearch finished...\n");
	

	}else{	
	
	docking.dockingQsearch( scoresFFT, radius_subset, MaxScoresRadius);
	printf("DockingQSearch finished...\n");
	
	

	//docking.outputScores( scoresOutputFileFFT, "# MPI worker...\n", scoresFFT );
	}

	//--------------------
	//Testiranje S(alfa_2)
	//--------------------
	//docking.dockingQsearchTest( 26.0, 0.0, 0.0, 0.0, 0.0, scores);
	//docking.dockingQsearchTest( 26.0, 0.0, 0.0, 0.0, 0.0, scores);
	//docking.dockingSearchTest( 26.0, 0.0, 0.0, 0.0, 0.0, scores);
	//docking.dockingQoriginalSearchTest(0,0,0,0,0, scores);
	//docking.dockingQmSearchTest(29.500000, 2.634373, 5.138709, 2.219089, 5.521052, scores);

	//string scoresOutputFile;
	//configuration.getParameter("scores_output_file", scoresOutputFile);

    	//docking.outputScores(scoresOutputFile, "# header...\n", scores);
	
        /* Testiranje eksportanja na os	
	Protein *receptor = new Protein( docking.receptor_.inner_, docking.receptor_.outer_);
	Protein *ligand =  new Protein( docking.ligand_.inner_, docking.ligand_.outer_);
	
	char buffer[100];
	sprintf(buffer, "%s/%d/%.6lf.dat", docking.translationPath_.c_str(), 20, 33.5);
	TranslationMatrix translationmatrix(buffer);
	//receptor->translate(translationmatrix);

		
	Grid *gridReceptorInner = new Grid (51, 1);
	Grid *gridReceptorOuter = new Grid (51, 1);
	Grid *gridLigandInner = new Grid (51, 1);
	Grid *gridLigandOuter = new Grid (51, 1);
	
	gridLigandInner->exportToFileXaxis("LigandInnerDenisty.txt", 0,0, ligand->inner_);
	gridLigandOuter->exportToFileXaxis("LigandOuterDenisty.txt", 0,0, ligand->outer_);
	gridReceptorInner->exportToFileXaxis("ReceptorInnerDenisty.txt", 0,0, receptor->inner_);
	gridReceptorOuter->exportToFileXaxis("ReceptorOuterDenisty.txt", 0,0, receptor->outer_);	
	*/

	return 0;
}

/*
    	double t;
	double radiusStart, radiusEnd;
	configuration.getParameter("radius_search_start", t);
	for (radiusStart = 0.0; radiusStart +0.5 < t+1e-9; radiusStart += 0.5); // calibration to known radius

	configuration.getParameter("radius_search_end", radiusEnd);

	vector<double> radius_set;
	for (double R = radiusStart; R < radiusEnd; R += 0.5){
		radius_set.push_back(R);
	}

	printf("Radiusi: \n");
	for(unsigned int i = 0; i< radius_set.size(); ++i){

		printf(" %lf ",radius_set[i]);
	}
	printf("\n");

	vector<double> MaxScoresRadius;
	docking.dockingQsearch(scores, radius_set, MaxScoresRadius);

	string scoresOutputFile;
	configuration.getParameter("scores_output_file", scoresOutputFile);

    docking.outputScores(scoresOutputFile, "# header...\n", scores);
    */
