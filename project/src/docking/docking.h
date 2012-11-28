/*
 * docking.h
 *
 *  Created on: Sep 29, 2009
 *      Author: canadi
 */

#ifndef DOCKING_H_
#define DOCKING_H_

#include "../coefficients/coefficients.h"
#include "../translationmatrix/translationmatrix.h"
#include "../rotationmatrix/rotationmatrix.h"
#include "../protein/protein.h"
#include "../math/math_pdt.h"
#include "../configuration/configuration.h"
#include "../predocking/predocking.h"
//#include "../pdbparser/pdbparser.h"
#include <math.h>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <list>
#include <time.h>
using namespace std;

class ScoreConfiguration
{
public:
	double R, alpha, beta1, gamma1, beta2, gamma2;

	ScoreConfiguration();
	ScoreConfiguration(double _R, double _alpha, double _beta1, double _gamma1, double _beta2, double _gamma2);

	bool operator < (const ScoreConfiguration& a) const;
};

class Docking
{
public:
	//Docking(const pair<string&, string&> receptorFile, const pair<string&, string&> ligandFile);
	Docking(const pair<string, string>& receptorFile, const pair<string, string>& ligandFile);
	Docking(const Grid& receptorInner, const Grid& receptorOuter, const Grid& ligandInner, const Grid& ligandOuter, int order);
	Docking(Configuration &config);
	Docking(std::string configPath);
	~Docking();

	double scoreIt(Protein& receptor, Protein& ligand, double Q);
	double scoreIt(double R, double betaReceptor, double gammaReceptor, double alphaLigand, double betaLigand, double gammaLigand);
	void dockingSearch(vector <pair<double, ScoreConfiguration> >& scores);
	void calculateProteinCoefficients(int order);

	void preDockingCalculateRotations(void);
	void preDockingCalculateQRotations(void);
	void freeMemory(void);
	void dockingSearch(vector <pair<double, ScoreConfiguration> >& scores, vector<double> RadiusSet, vector<double>& MaxScoresRadius);
	void dockingQsearch(vector <pair<double, ScoreConfiguration> >& scores, vector<double> RadiusSet, vector<double>& MaxScoresRadius);
	int outputScores(const string& outputFile, const string& header, vector <pair<double, ScoreConfiguration> > scores) const;
	void outputToGrid(const ScoreConfiguration& scoreconfiguration, const pair<string, string> receptorFile, const pair<string, string> ligandFile, double gridSize, double gridCellSize);
    
	void dockingSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2, vector <pair<double, ScoreConfiguration> >& scores);
	void dockingQsearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores);
	void dockingQoriginalSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores);
	void dockingQmSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores);

	void trigonometricCash();
    double scoreIt(const ScoreConfiguration& scoreConfiguration);
    void setConfiguration(const ScoreConfiguration& scoreConfiguration, Protein &newReceptor, Protein &newLigand) const;
    void setConfiguration(double R, double betaReceptor, double gammaReceptor, double alphaLigand, double betaLigand, double gammaLigand, Protein &newReceptor, Protein &newLigand) const;

	void calculateCoeffMapping( );
	void calculateQcoeffPlusPlus(vector<double>& qCoeffPlusPlus, vector<double>& qCoeffPlus, Protein& transReceptor, Protein& qRotLigand );
	void calculateQcoeffMinusMinus(vector<double>& qCoeffMinusMinus,vector<double> &qCoeffMinus, Protein& transReceptor, Protein& qRotLigand );
	void calculateQcoeffs(vector<double>& qCoeffPlusPlus, vector<double>& qCoeffPlus,vector<double>& qCoeffMinusMinus,vector<double> &qCoeffMinus,Protein& transReceptor, Protein& qRotLigand);

	void dumpParameters(FILE *fp)const;
private:
	void checkOrders();

	void setDefaultParameters();
	void loadParametersFromConfiguration(Configuration &config);

	Predocking ligandPredocking_;
	Predocking receptorPredocking_;

	Protein receptor_;
	Protein ligand_;

	RotationAngle *rotationAngles_;
	Protein *rotReceptor_;
	Protein *rotLigand_;
	Protein *qRotLigand_;
	bool rotatationsCalculated_;

	vector<double> *cosValue_;
	vector<double> *sinValue_;
	bool trigonometricCalculated_;

	vector<list<int> > coeffMappingNLM_;
	vector<list<int> > coeffMappingNLMcrt_;
	bool coeffMappingNLMCalculated_;
		 
	int tessellationOrder_, alphaSize_;
	int scoresSize_;
	double penalty_, radiusStart_, radiusEnd_;
	string translationPath_;
	string ligandPath_;
	string receptorPath_;
	string radiiPath_;
};


#endif /* DOCKING_H_ */
