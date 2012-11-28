/*
 * evaluatescores.h
 *
 *  Created on: Jun 1, 2010
 *      Author: ivan
 */

#ifndef EVALUATESCORES_H_
#define EVALUATESCORES_H_

#include <iostream>
#include "../gui/glwindow.h"
#include "../gui/vmolgui.h"
#include "../command/vmolcommand.h"
#include "../log/log.h"
#include "../structures/structures.h"
#include "../pdbwriter/pdbwriter.h"



void evaluateScores(PdbFile *complex, PdbFile *ligand, PdbFile *receptor, PdbFile &complexCopy, PdbFile &receptorCopy, PdbFile &ligandCopy, ScoreLoader &scoreData);
void evaluateScores(PdbFile &complexPdb, PdbFile &receptorPdb, PdbFile &ligandPdb, PdbFile &complexCopy, PdbFile &receptorCopy, PdbFile &ligandCopy, std::string outRMSDPath, ScoreLoader &scoresData, int startingScore, int maxNumScores);
void calculateAlignmentMatrix(Coordinates *referencePoints, double *retMatrix);
void transformVectors(Coordinates point1, Coordinates point2, Coordinates point3, double *retMatrix);
void multiplyMatrix(double *firstMatrix, double *secondMatrix, double *retMatrix);
void getTranslationMatrix(double x, double y, double z, double *retMatrix);
void getRotationMatrix(double angle, double x, double y, double z, double *retMatrix);
void printMatrix(double *matrix, char *matrixName);



#endif /* EVALUATESCORES_H_ */
