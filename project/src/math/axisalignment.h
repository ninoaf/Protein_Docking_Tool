/*
 * axisalignment.h
 *
 *  Created on: Jun 2, 2010
 *      Author: ivan
 */

#ifndef AXISALIGNMENT_H_
#define AXISALIGNMENT_H_

#include "../pdbparser/pdbparser.h"
#include "../structures/structures.h"

void alignByZAxis(Coordinates &receptorCenter, double *retMatrix);
int centerWithAlignment(PdbFile &receptor, PdbFile &ligand);



#endif /* AXISALIGNMENT_H_ */
