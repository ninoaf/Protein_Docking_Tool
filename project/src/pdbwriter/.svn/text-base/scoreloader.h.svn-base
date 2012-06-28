/*
 * scoreloader.h
 *
 *  Created on: Mar 20, 2010
 *      Author: ivan
 */

#ifndef SCORELOADER_H_
#define SCORELOADER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>



class SingleScore
{
public:
	double score, radius, betaReceptor, gammaReceptor, alphaLigand, betaLigand, gammaLigand;

	SingleScore()
	{
		score = radius = betaReceptor = gammaReceptor = alphaLigand = betaLigand = gammaLigand = 0.0f;
	}
};

class ScoreLoader
{
public:
	std::vector<SingleScore> scores;

	ScoreLoader();
	ScoreLoader(std::string path);
	~ScoreLoader();

	void init();

	bool loadScoresFromFile(std::string path);
	void addScore(std::string scoreLine);

private:
	std::vector<std::string> scoreLine_;
};

#endif /* SCORELOADER_H_ */
