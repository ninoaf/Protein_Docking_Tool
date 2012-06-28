/*
 * grid.h
 *
 *      Author: IC
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>

#include <vector>
#include <string>

#include "../structures/structures.h"
#include "../coefficients/coefficients.h"
#include "../msmswrapper/msmswrapper.h"
#include "../basefunctions/basefunctions.h"

class Coefficients;

class Grid
{
	friend class Coefficients;

public:
	Grid(double gridSize, double gridCellCize);
	Grid(const std::string& inputFile);
	~Grid();
	Grid();

	int exportToFile(const std::string& outputFile) const;
	int dump(const std::string& outputFile) const;
	int importFromFile(const std::string& inputFile);
	int importFromOldFile(const std::string& inputFile);
	int generateTestCube (double cubeSize, double cubeWidth, double offset);
	int generateFromCoefficients(const Coefficients& coefficients);
	int generateSurfaceGrid(const MSMSWrapper& surface, double microDelta, double delta, double radius);
	int inflateGrid();
	void generateTestCharge (double q);
	int generateFromETOCoefficients(const Coefficients& coefficients);
	void exportToFileZaxis(const std::string& outputFile, int x, int y) const;
	void exportToFileXaxis(const std::string& outputFile, int x, int y, const Coefficients& coefficients );	
	std::vector <GridValue> getGrid();
	double getGridCellSize();
	double getGridSize();
	void operator= (Grid& op1);

private:
	std::vector <GridValue> grid_;
	double gridCellSize_, gridSize_;

	bool generateGridOffsets(std::vector<GridValue> &offsets, double const microDelta, double const sphereRadius);
};


#endif /* GRID_H_ */
