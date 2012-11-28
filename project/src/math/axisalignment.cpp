/*
 * axisalignment.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: ivan
 */

#include "axisalignment.h"



/*
void alignByZAxis(Coordinates &receptorCenter, double *retMatrix)
{
	double matrixRxz[16], matrixRxz2z[16];

/**
	Rxz = [ a b 0 0;
			c d 0 0;
			0 0 1 0;
			0 0 0 1;]

transponirano:
	Rxz = [ a c 0 0;
			b d 0 0;
			0 0 1 0;
			0 0 0 1;]

	Rxz2z = [ a1 0 b1 0;
			  0  1 0  0;
			  c1 0 d1 0;
			  0  0  0 1;]

transponirano:
	Rxz2z = [ a1 0 c1 0;
			  0  1 0  0;
			  b1 0 d1 0;
			  0  0  0 1;]



	double u = receptorCenter.x;
	double v = receptorCenter.y;
	double w = receptorCenter.z;

	for (int i=0; i<16; i++)
	{
		matrixRxz[i] = matrixRxz2z[i] = 0.0f;
	}

	matrixRxz[0] = u / sqrt (u*u + v*v);
	matrixRxz[4] = v / sqrt (u*u + v*v);
	matrixRxz[1] = -v / sqrt (u*u + v*v);
	matrixRxz[5] = u / sqrt (u*u + v*v);
	matrixRxz[10] = 1.0f;
	matrixRxz[15] = 1.0f;

	matrixRxz2z[0] = w / sqrt(u*u + v*v + w*w);
	matrixRxz2z[8] = -sqrt(u*u + v*v) / sqrt(u*u + v*v + w*w);
	matrixRxz2z[5] = 1.0f;
	matrixRxz2z[2] = sqrt(u*u + v*v) / sqrt(u*u + v*v + w*w);
	matrixRxz2z[10] = w / sqrt(u*u + v*v + w*w);
	matrixRxz2z[15] = 1.0f;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<4; k++)
				retMatrix[i*4+j] += matrixRxz[i*4+k] * matrixRxz2z[k*4+j];
}

int centerAlignment(PdbFile &receptor, PdbFile &ligand)
{
	unsigned long int i=0;
	double transformMatrix[16];
	Coordinates receptorCenter, ligandCenter;

	receptor.findCenters();
	ligand.findCenters();

	receptorCenter.x = receptor.getPdbMassCenter().x - ligand.getPdbMassCenter().x;
	receptorCenter.y = receptor.getPdbMassCenter().y - ligand.getPdbMassCenter().y;
	receptorCenter.z = receptor.getPdbMassCenter().z - ligand.getPdbMassCenter().z;

	ligandCenter.x = ligand.getPdbMassCenter().x;
	ligandCenter.y = ligand.getPdbMassCenter().y;
	ligandCenter.z = ligand.getPdbMassCenter().z;

	alignByZAxis(receptorCenter, transformMatrix);

	for (i=0; i<receptor.getAtomList().size(); i++)
	{
		receptor.getAtomList()[i].x -= ligand.getPdbMassCenter().x;
		receptor.getAtomList()[i].y -= ligand.getPdbMassCenter().y;
		receptor.getAtomList()[i].z -= ligand.getPdbMassCenter().z;

		receptor.getAtomList()[i].transformCoordinates(transformMatrix, ' ');
	}

	for (i=0; i<ligand.getAtomList().size(); i++)
	{
		ligand.getAtomList()[i].x -= ligand.getPdbMassCenter().x;
		ligand.getAtomList()[i].y -= ligand.getPdbMassCenter().y;
		ligand.getAtomList()[i].z -= ligand.getPdbMassCenter().z;

		ligand.getAtomList()[i].transformCoordinates(transformMatrix, ' ');
	}

	return 0;
}

*/

void alignByZAxis(Coordinates &receptorCenter, double *retMatrix)
{
	double matrixRxz[16], matrixRxz2z[16];

/*
	Rxz = [ a b 0 0;
			c d 0 0;
			0 0 1 0;
			0 0 0 1;]

transponirano:
	Rxz = [ a c 0 0;
			b d 0 0;
			0 0 1 0;
			0 0 0 1;]

	Rxz2z = [ a1 0 b1 0;
			  0  1 0  0;
			  c1 0 d1 0;
			  0  0  0 1;]

transponirano:
	Rxz2z = [ a1 0 c1 0;
			  0  1 0  0;
			  b1 0 d1 0;
			  0  0  0 1;]

*/

	double u = receptorCenter.x;
	double v = receptorCenter.y;
	double w = receptorCenter.z;

	for (int i=0; i<16; i++)
	{
		retMatrix[i] = 0.0f;

/*
		if ((i % 5) == 0)
			retMatrix[i] = 1.0f;
*/

		matrixRxz[i] = matrixRxz2z[i] = 0.0f;
	}

	matrixRxz[0] = u / sqrt (u*u + v*v);
	matrixRxz[4] = v / sqrt (u*u + v*v);
	matrixRxz[1] = -v / sqrt (u*u + v*v);
	matrixRxz[5] = u / sqrt (u*u + v*v);
	matrixRxz[10] = 1.0f;
	matrixRxz[15] = 1.0f;

	matrixRxz2z[0] = w / sqrt(u*u + v*v + w*w);
	matrixRxz2z[8] = -sqrt(u*u + v*v) / sqrt(u*u + v*v + w*w);
	matrixRxz2z[5] = 1.0f;
	matrixRxz2z[2] = sqrt(u*u + v*v) / sqrt(u*u + v*v + w*w);
	matrixRxz2z[10] = w / sqrt(u*u + v*v + w*w);
	matrixRxz2z[15] = 1.0f;

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			for(int k=0; k<4; k++)
				retMatrix[i*4+j] += matrixRxz[i*4+k] * matrixRxz2z[k*4+j];

/*
	for (int i=0; i<16; i++)
		retMatrix[i] = matrixRxz[i];
*/
}

int centerWithAlignment(PdbFile &receptor, PdbFile &ligand)
{
	unsigned long int i=0;
	double transformMatrix[16], rotationMatrix[16];
	Coordinates receptorCenter, ligandCenter;

	receptor.findCenters();
	ligand.findCenters();

//	printf ("ligand: %lf\t%lf\t%lf\n", ligand.getPdbMassCenter().x, ligand.getPdbMassCenter().y, ligand.getPdbMassCenter().z);
//	printf ("receptor: %lf\t%lf\t%lf\n", receptor.getPdbMassCenter().x, receptor.getPdbMassCenter().y, receptor.getPdbMassCenter().z);

	receptorCenter.x = receptor.getPdbMassCenter().x - ligand.getPdbMassCenter().x;
	receptorCenter.y = receptor.getPdbMassCenter().y - ligand.getPdbMassCenter().y;
	receptorCenter.z = receptor.getPdbMassCenter().z - ligand.getPdbMassCenter().z;

//	printf ("receptor: %lf\t%lf\t%lf\n", receptorCenter.x, receptorCenter.y, receptorCenter.z);

	ligandCenter.x = ligand.getPdbMassCenter().x;
	ligandCenter.y = ligand.getPdbMassCenter().y;
	ligandCenter.z = ligand.getPdbMassCenter().z;

	alignByZAxis(receptorCenter, transformMatrix);

	double angle=0.0f;
	angle = 180.0f * 3.141592654l / 180.0f;
	for (i=0; i<16; i++)
		rotationMatrix[i] = 0.0f;
	rotationMatrix[0] = rotationMatrix[15] = 1.0f;
	rotationMatrix[5] = rotationMatrix[10] = cos(angle);
	rotationMatrix[6] = sin(angle);
	rotationMatrix[9] = -sin(angle);

	rotationMatrix[0] = rotationMatrix[15] = 1.0f;
	rotationMatrix[5] = rotationMatrix[10] = -1.0f;
	rotationMatrix[6] = 0.0f;
	rotationMatrix[9] = 0.0f;

	for (i=0; i<receptor.getAtomList().size(); i++)
	{
		receptor.getAtomList()[i].x -= ligand.getPdbMassCenter().x;
		receptor.getAtomList()[i].y -= ligand.getPdbMassCenter().y;
		receptor.getAtomList()[i].z -= ligand.getPdbMassCenter().z;

		receptor.getAtomList()[i] = receptor.getAtomList()[i].transformCoordinates(transformMatrix, ' ');
//		receptor.getAtomList()[i] = receptor.getAtomList()[i].transformCoordinates(rotationMatrix, ' ');
	}

	for (i=0; i<ligand.getAtomList().size(); i++)
	{
		ligand.getAtomList()[i].x -= ligand.getPdbMassCenter().x;
		ligand.getAtomList()[i].y -= ligand.getPdbMassCenter().y;
		ligand.getAtomList()[i].z -= ligand.getPdbMassCenter().z;

		ligand.getAtomList()[i] = ligand.getAtomList()[i].transformCoordinates(transformMatrix, ' ');
		ligand.getAtomList()[i] = ligand.getAtomList()[i].transformCoordinates(rotationMatrix, ' ');
	}



	receptor.findCenters();
	receptor.centerAtomsByMass();

	for (i=0; i<receptor.getAtomList().size(); i++)
	{
		receptor.getAtomList()[i] = receptor.getAtomList()[i].transformCoordinates(rotationMatrix, ' ');
	}

	return 0;
}
