/*
 * scoreloader.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: ivan
 */

#include "scoreloader.h"

using namespace std;



ScoreLoader::ScoreLoader()
{
	init();
}

ScoreLoader::ScoreLoader(string path)
{
	loadScoresFromFile(path);
}

ScoreLoader::~ScoreLoader()
{
	init();
}

void ScoreLoader::init()
{
	scoreLine_.clear();
	scores.clear();
}

bool ScoreLoader::loadScoresFromFile(string path)
{
	string buffer, tempLine;
	ifstream input(path.c_str());

	init();

	if (input == NULL)
		return false;

	while(getline(input, buffer))
	{
		int hashSign = buffer.find("#");

		if (hashSign >= 0)
		{
			tempLine = buffer.substr(0, hashSign);
			if (tempLine.length() > 0)
			{
				addScore(tempLine);
			}

		}
		else
//			scoreLine_.push_back(buffer);
			addScore(buffer);
	}

	return true;
}

/*
bool ScoreLoader::parseScore(unsigned int scoreIndex, double &score, double &radius, double &betaR, double &gammaR, double &alphaL, double &betaL, double &gammaL)
{
	int tempIndex=0;
	double tempScore=0.0f, tempRadius=0.0f, tempBetaR=0.0f, tempGammaR=0.0f, tempAlphaL=0.0f, tempBetaL=0.0f, tempGammaL=0.0f;

	if (score_line.size() > scoreIndex)
	{
		sscanf(score_line[scoreIndex].c_str(), "%d %lf %lf %lf %lf %lf %lf %lf", &tempIndex, &tempScore, &tempRadius, &tempBetaR, &tempGammaR, &tempAlphaL, &tempBetaL, &tempGammaL);

		score = tempScore;
		radius = tempRadius;
		betaR = tempBetaR;
		gammaR = tempGammaR;
		alphaL = tempAlphaL;
		betaL = tempBetaL;
		gammaL = tempGammaL;

		return true;
	}

	return false;
}
*/

void ScoreLoader::addScore(string scoreLine)
{
	int tempIndex=0;
	SingleScore score;

//	double tempScore=0.0f, tempRadius=0.0f, tempBetaR=0.0f, tempGammaR=0.0f, tempAlphaL=0.0f, tempBetaL=0.0f, tempGammaL=0.0f;
//	sscanf(scoreLine.c_str(), "%d %lf %lf %lf %lf %lf %lf %lf", &tempIndex, &tempScore, &tempRadius, &tempBetaR, &tempGammaR, &tempAlphaL, &tempBetaL, &tempGammaL);
	sscanf(scoreLine.c_str(), "%d %lf %lf %lf %lf %lf %lf %lf", &tempIndex, &(score.score), &(score.radius), &(score.betaReceptor), &(score.gammaReceptor), &(score.alphaLigand), &(score.betaLigand), &(score.gammaLigand));

	scores.push_back(score);

/*
	score_.score.push_back(tempScore);
	score_.radius.push_back(tempRadius);
	score_.betaReceptor.push_back(tempBetaR);
	score_.gammaReceptor.push_back(tempGammaR);
	score_.alphaLigand.push_back(tempAlphaL);
	score_.betaLigand.push_back(tempBetaL);
	score_.gammaLigand.push_back(tempGammaL);
*/

}
