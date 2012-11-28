/*
 * grid.cpp
 *
 *  Created on: Sep 11, 2009
 *      Author: IC
 */

#include "grid.h"

Grid::Grid(double gridSize, double gridCellSize)
{
	gridSize_ = gridSize;
	gridCellSize_ = gridCellSize;
}



Grid::~Grid()
{
	;
}


Grid::Grid()
{
	gridCellSize_ = gridSize_ = -1.0;
}

Grid::Grid(const std::string& inputFile)
{
	importFromFile(inputFile);
}

int Grid::size() const
{
	return grid_.size();
}



// Exports grid to file. Returns number of written elements.
int Grid::exportToFile(const std::string& outputFile) const
{
	printf("Exporting grid to file %s\n", outputFile.c_str());

	FILE *fp;
	fp = fopen(outputFile.c_str(), "wb");
	if (fp == 0)
	{
		printf("Unable to open file %s for writing in function Export_From_File(...)!\n", outputFile.c_str());
		return -1;
	}

	unsigned int nGrid = grid_.size();
	int ret = 0;
	ret += fwrite(&nGrid, sizeof(nGrid), 1, fp);
	ret += fwrite(&gridSize_, sizeof(gridSize_), 1, fp);
	ret += fwrite(&gridCellSize_, sizeof(gridCellSize_), 1, fp);

	for (unsigned int i = 0; i < nGrid; ++i){
		ret += fwrite(&grid_[i].coord.x, sizeof(grid_[i].coord.x), 1, fp);
		ret += fwrite(&grid_[i].coord.y, sizeof(grid_[i].coord.y), 1, fp);
		ret += fwrite(&grid_[i].coord.z, sizeof(grid_[i].coord.z), 1, fp);
		ret += fwrite(&grid_[i].value, sizeof(grid_[i].value), 1, fp);
	}

	fclose(fp);

	printf("Grid exported to file: %s (%d bytes written)\n", outputFile.c_str(), ret);

	return ret;
}

// Dumps grid's values to text file. For debugging purposes only.
int Grid::dump(const std::string& outputFile) const
{
	printf("dumping grid to txt file %s\n", outputFile.c_str());

	FILE *fp;
	fp = fopen(outputFile.c_str(), "wt");
	if (fp == 0)
	{
//		Error_Report("ERROR", "Unable to open file %s for writing in function Export_From_File(...)!", output_path.c_str());
		return -1;
	}

	unsigned int nGrid = grid_.size();
	int ret = 0;
	ret += fprintf(fp, "%u\n", nGrid);
	ret += fprintf(fp, "%lf\n", gridSize_);
	ret += fprintf(fp, "%lf\n", gridCellSize_);

	for (unsigned int i = 0; i < nGrid; ++i){
		ret += fprintf(fp, "(%lf, %lf, %lf) -> %lf\n", grid_[i].coord.x, grid_[i].coord.y, grid_[i].coord.z, grid_[i].value);
	}

	fclose(fp);

	return ret;
}

// Imports grid from file. Returns number of read elements.
int Grid::importFromFile(const std::string& inputFile)
{
	printf("Importing grid from file %s\n", inputFile.c_str());

	FILE *fp;
	fp = fopen(inputFile.c_str(), "rb");
	if (fp == 0)
	{
		printf("Unable to open file %s for reading in function Import_From_File(...)!\n", inputFile.c_str());
		return -1;
	}

	unsigned int nGrid;
	int ret = 0;

	ret += fread(&nGrid, sizeof(nGrid), 1, fp);
	ret += fread(&gridSize_, sizeof(gridSize_), 1, fp);
	ret += fread(&gridCellSize_, sizeof(gridCellSize_), 1, fp);
	grid_.resize(nGrid);

	gridWidth_ = (unsigned long int) pow(nGrid, 1.0f/3.0f);

	for (unsigned int i = 0; i < nGrid; ++i){
		ret += fread(&grid_[i].coord.x, sizeof(grid_[i].coord.x), 1, fp);
		ret += fread(&grid_[i].coord.y, sizeof(grid_[i].coord.y), 1, fp);
		ret += fread(&grid_[i].coord.z, sizeof(grid_[i].coord.z), 1, fp);
		ret += fread(&grid_[i].value, sizeof(grid_[i].value), 1, fp);
	}

	fclose(fp);

	printf("Grid imported from file %s (%d elements read)\n", inputFile.c_str(), ret);

	return ret;
}

// Imports grid from grid file with old format (PDT_v2). Returns number of read elements.
int Grid::importFromOldFile(const std::string& inputFile)
{
//	Log_Append("Importing grid from file %s", input_path.c_str());

	FILE *fp;
	fp = fopen(inputFile.c_str(), "rb");
	if (fp == 0)
	{
//		Error_Report("ERROR", "Unable to open file %s for reading in function Import_From_File(...)!", input_path.c_str());
		return -1;
	}

	unsigned long int nGrid;
	int ret = 0;

	ret += fread(&nGrid, sizeof(nGrid), 1, fp);
	grid_.resize(nGrid);

	// hard coded
	gridSize_ = 100.0;
	gridCellSize_ = 1.0;

	for (unsigned int i = 0; i < nGrid; ++i){
		ret += fread(&grid_[i].coord.x, sizeof(grid_[i].coord.x), 1, fp);
		ret += fread(&grid_[i].coord.y, sizeof(grid_[i].coord.y), 1, fp);
		ret += fread(&grid_[i].coord.z, sizeof(grid_[i].coord.z), 1, fp);
		ret += fread(&grid_[i].value, sizeof(grid_[i].value), 1, fp);
	}

	fclose(fp);

//	Log_Append("Grid imported from file %s (%d bytes read)", input_path.c_str(), ret);

	return ret;
}

// Generate Grid from Coefficients. Returns -1 in case of an error.
int Grid::generateFromCoefficients(const Coefficients& coefficients)
{
	double q = (gridSize_ - gridCellSize_) / 2.0;

	BaseFunctions* bf = BaseFunctions::instance();

//	Log_Append(pdt_log_file, "Calculating grid values out of a set of spherical coefficients...");
//	Log_Append(pdt_log_file, "..Coeff_To_Grid: grid_size = %lf .", grid_size);
//	Log_Append(pdt_log_file, "..Coeff_To_Grid: grid_cell_size = %lf .", grid_cell_size);
//	Log_Append(pdt_log_file, "..Coeff_To_Grid: q = %lf .", q);

	grid_.clear();

	printf("Gridsize %lf \n", gridSize_);
	printf("GridCelsize %lf \n", gridCellSize_);
	printf("q size total: %lf \n", q);

	for (double i = -q; i < q+1e-7; i += gridCellSize_)
	{
		printf("%lf\n", i);
		for (double j = -q; j < q+1e-7; j += gridCellSize_)
		{
			for (double k = -q; k < q+1e-7; k += gridCellSize_)
			{
				GridValue tmpGrid(i, j, k, 0.0);
				SphericalCoordinates sc(tmpGrid.coord);

				for (int iCoef = 0; iCoef < (int)coefficients.coefficients_.size(); ++iCoef)
				{
					tmpGrid.value += coefficients.coefficients_[iCoef].value * bf->baseFunction(coefficients.coefficients_[iCoef].coeffCoord, sc);
				}

				grid_.push_back(tmpGrid);
			}
		}
	}

//	Log_Append(pdt_log_file, "...OK! (Coeff_To_Grid finished successfully)");

	return 0;
}



// Creates a test cube for performing system check by generating the test cube grid. Returns -1 on error.
int Grid::generateTestCube (double cubeSize, double cubeWidth, double offset)
{
	double Q = (gridSize_ - gridCellSize_) / 2.0;
    double q = (cubeSize - gridCellSize_) / 2.0;
    double z = q - static_cast<double>(cubeWidth/gridCellSize_ + 1.0) * gridCellSize_;

    grid_.clear();

//    Log_Append(pdt_log_file, "Generating test cube...");
//    Log_Append(pdt_log_file, "..Test_Cube: cube_size = %lf .", cube_size);
//    Log_Append(pdt_log_file, "..Test_Cube: grid_cell_size = %lf .", grid_cell_size);
//    Log_Append(pdt_log_file, "..Test_Cube: q = %lf .", q);

    for (double i = -Q; i <= Q; i += gridCellSize_)
    {
        for (double j = -Q; j <= Q; j += gridCellSize_)
        {
            for (double k = -Q; k <= Q; k += gridCellSize_)
            {
            	if ((i*i <= q*q && j*j <= q*q && k*k <= q*q) && (i*i >= z*z || j*j >= z*z || k*k >= z*z))
            	{
            		grid_.push_back(GridValue(i, j, k+offset, 1.0));
            	}
             }
          }
      }

//      Log_Append(pdt_log_file, "...OK! (generating test cube finished successfully)");

      return 0;
}

bool Grid::generateGridOffsets(vector<GridValue> &offsets, double const microDelta, double const sphereRadius)
{
	double l=0.0f, m=0.0f, n=0.0f;
	double nlmStart=0.0f, nlmEnd=0.0f;
	double sphereRadiusSquare=0.0f;
	GridValue temp;

	nlmStart = ceil((0 - sphereRadius) / microDelta) * microDelta;
	nlmEnd = ceil((0 + sphereRadius) / microDelta) * microDelta;
	sphereRadiusSquare = pow(sphereRadius, 2);

	for (l=nlmStart; l<nlmEnd; l+=microDelta)
	{
		for (m=nlmStart; m<nlmEnd; m+=microDelta)
		{
			for (n=nlmStart; n<nlmEnd; n+=microDelta)
			{
				if (pow((l - 0), 2) + pow((m - 0), 2) + pow((n - 0), 2) <= sphereRadiusSquare)
				{
					temp.coord.x = l;
					temp.coord.y = m;
					temp.coord.z = n;
					temp.value = 1;

					offsets.push_back(temp);
				}
			}
		}
	}

	return true;
}

int Grid::generateSurfaceGrid(const MSMSWrapper& surface, double microDelta, double delta, double radius)
{
	unsigned long int i=0, j=0;
	Coordinates tempCoord, c, vn;
	Coordinates sphereCenter;
	GridValue tempGridValue;
	vector<GridValue> offsets;
	map<Coordinates, double, CoordCompare> tempMap;

	if (microDelta<=0.0f || delta<=0.0f) // || radius<=0.0f)
		return false;

	if (generateGridOffsets(offsets, microDelta, abs(radius)) == false)
		return false;

	grid_.clear();

	Coordinates normalizedVector;

	for (i=0; i<surface.numCoords; i++)
	{
		normalizedVector = surface.vertices[i].vector;
		normalizedVector.Normalize();

		/* Calculate sphere centre for inner skin. */
//		sphereCenter.x = surface.vertices[i].coord.x + surface.vertices[i].vector.x * radius;
//		sphereCenter.y = surface.vertices[i].coord.y + surface.vertices[i].vector.y * radius;
//		sphereCenter.z = surface.vertices[i].coord.z + surface.vertices[i].vector.z * radius;

		sphereCenter.x = surface.vertices[i].coord.x + normalizedVector.x * radius;
		sphereCenter.y = surface.vertices[i].coord.y + normalizedVector.y * radius;
		sphereCenter.z = surface.vertices[i].coord.z + normalizedVector.z * radius;

		for (j=0; j<offsets.size(); j++)
		{
			tempCoord = sphereCenter + offsets[j].coord;

			tempGridValue.coord.x = (int) ceil((ceil(tempCoord.x / microDelta) * microDelta) / delta);
			tempGridValue.coord.y = (int) ceil((ceil(tempCoord.y / microDelta) * microDelta) / delta);
			tempGridValue.coord.z = (int) ceil((ceil(tempCoord.z / microDelta) * microDelta) / delta);
			tempGridValue.value = 1;

			if (tempMap.count(tempGridValue.coord) == 0) // ovo nema sanse da radi! implementirat poseban bool operator <
			{
				grid_.push_back(tempGridValue);
				tempMap.insert(make_pair(tempGridValue.coord, tempGridValue.value));
			}
		}
	}

	return true;
}

int Grid::inflateGrid()
{
	unsigned int l=0;
	double Q = (gridSize_) / 2.0;
	GridValue tempGridValue;
	map<Coordinates, double, CoordCompare> tempMap;

	for (l=0; l<grid_.size(); l++)
		tempMap.insert(make_pair(grid_[l].coord, grid_[l].value));

    grid_.clear();

    for (double i = -Q; i <= Q; i += gridCellSize_)
    {
		for (double j = -Q; j <= Q; j += gridCellSize_)
		{
			for (double k = -Q; k <= Q; k += gridCellSize_)
			{
				tempGridValue.coord.x = i;
				tempGridValue.coord.y = j;
				tempGridValue.coord.z = k;

				if (tempMap.count(tempGridValue.coord) == 0)
					tempGridValue.value = 0.0f;
				else
					tempGridValue.value = 1.0f;

				grid_.push_back(tempGridValue);
			}
		}
    }

    tempMap.clear();

    return 1;
}

std::vector<GridValue>& Grid::getGrid()
{
	return grid_;
}

void Grid::setGridSize(double gridSize, double gridCellSize)
{
	gridSize_ = gridSize;
	gridCellSize_ = gridCellSize;
}

double Grid::getGridCellSize()
{
	return gridCellSize_;
}

double Grid::getGridSize()
{
	return gridSize_;
}

unsigned long int Grid::getGridWidth()
{
	return gridWidth_;
}

void Grid::operator= (Grid& op1)
{
 	grid_ = op1.getGrid();
	gridCellSize_ = op1.getGridCellSize();
	gridSize_ = op1.getGridSize();
}
