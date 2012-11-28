/*
 * pdbwriter.h
 *
 *  Created on: Mar 19, 2010
 *      Author: ivan
 */

#ifndef PDBWRITER_H_
#define PDBWRITER_H_

#include "../pdbparser/pdbparser.h"
#include "../structures/structures.h"
#include "scoreloader.h"

#include <string>
#include <vector>
#include <queue>



class PdbWriter
{
public:
	PdbWriter();
	~PdbWriter();

	void init();
//	void write(string scrPath, string outPdbPath);
//	void Write(vector <pair<double< ScoreConfiguration> > scores, string outPdbPath);
//	int write(vector <pair<double, ScoreConfiguration> > scores, string receptorPath, string ligandPath, string radiiPath, string outPdbPath);
	int write(std::string scorePath, std::string receptorPath, std::string ligandPath, std::string radiiPath, std::string outPdbPath, int startingScore, int maxNumScores, int centerAtoms);
	int write(PdbFile &receptor, PdbFile &ligand, ScoreLoader &scoresData, std::string outPdbPath, int startingScore=0, int maxNumScores=1, bool changeChains=false);

//	int evaluateScores(std::string scorePath, std::string complexPath, std::string receptorPath, std::string ligandPath, std::string radiiPath, std::string outPdbPath, int startingScore, int maxNumScores, bool centerAtoms);
	int evaluateScores(std::string scorePath, std::string complexPath, std::string receptorPath, std::string ligandPath, std::string radiiPath, std::string outEvaluationPath, std::string outPdbPath, std::string outComplexPath, int startingScore, int maxNumScores, int centerAtoms);
	double evaluateRMSD(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, std::vector<int> &complexIndex, std::vector<int> &receptorIndex, std::vector<int> &ligandIndex);
	bool compareAtomLines(AtomPdb *firstAtom, AtomPdb *secondAtom);
	void indexAtoms(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, std::vector<int> &complexIndex, std::vector<int> &receptorIndex, std::vector<int> &ligandIndex);
	void mojGetch();
//	void alignPdbByReceptor(PdbFile &complex, PdbFile &receptor, PdbFile &ligand, vector<int> complexIndex, vector<int> receptorIndex, vector<int> ligandIndex);
	void alignPDB(PdbFile &pdbFile, Coordinates *referencePoints);
};

#endif /* PDBWRITER_H_ */
