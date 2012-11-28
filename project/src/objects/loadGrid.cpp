#include "mesh.h"
#include "marchingcubes.h"



int Mesh::loadGrid(std::string path, bool centerMesh, bool automaticIsosurface, double isoValue)
{
	unsigned long int size=0, gridWidth=0;
	double gridSize=0.0f, gridCellSize=0.0f;
	FILE *fp=NULL;
	Grid grid;

	clear();

/*
	fp = fopen(path.c_str(), "rb");
	if (fp == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_OPENING_FILE, "Failed to load file %s!", path.c_str());
		return 1;
	}

	fread(&size, sizeof(unsigned long int), 1, fp);
	gridWidth = (unsigned long int) pow(size, 1.0f/3.0f);

	fread(&gridSize, sizeof(double), 1, fp);
	fread(&gridCellSize, sizeof(double), 1, fp);
*/

	grid.importFromFile(path);

//	printf ("Tu sam 1!\n");

	if (automaticIsosurface == true)
		isoValue = calculateIsovalue(&grid);

	gridIsoValue_ = isoValue;

//	printf ("Tu sam 2!\n");

	marchingCubes(&grid, isoValue);

//	printf ("Tu sam 3!\n");

	findCenter();

    if (centerMesh == true)
    {
    	center();
    }

//    printf ("size = %d\n", vertices_.size());
    setMeshType("grid");
    setPath(path);
    setAutoIsoValue(automaticIsosurface);
    setGridIsoValue(isoValue);

	return 0;
}

double Mesh::fGetOffset(double fValue1, double fValue2, double fValueDesired)
{
        double fDelta = fValue2 - fValue1;

        if(fDelta == 0.0)
                return 0.5;
        return (fValueDesired - fValue1)/fDelta;
}

void Mesh::marchingCubes(Grid *grid, double isoSurface)
{
	unsigned long int i=0, j=0, k=0, width=0;
	Color newColor;

	width = grid->getGridWidth();

    for (i=0; i<(width-1); i++)
    {
        for (j=0; j<(width-1); j++)
        {
            for (k=0; k<(width-1); k++)
            {
                marchingCube(grid, i, j, k, isoSurface);
            }
        }
    }

/*
    newColor.r = newColor.g = newColor.b = newColor.a = 255;

    for (i=0; i<vertices_.size(); i++)
    {
    	colors_.push_back(newColor);
    }
*/

}

void Mesh::marchingCube(Grid *grid, unsigned long int indexI, unsigned long int indexJ, unsigned long int indexK, double isoValue)
{
		int i=0;
		long int iCorner, vertexIndex, vertexIndexTest, iEdge, iTriangle, iFlagIndex, iEdgeFlags;
		unsigned long int width=0;
		double fOffset;
		double cubeValues[8];
		Vector3 edgeVertex[12];
		Vector3 edgeNormal[12];
		GridValue *currentCube[8];
		unsigned long int vertexIndex1=0, vertexIndex2=0, vertexIndex3=0;
		unsigned long int cellIndex=0;
		Color newColor;
		Vector3 newNormal;
		Face3 newFace;

		width = grid->getGridWidth();

		for (i=0; i<8; i++)
		{
			cellIndex = (unsigned long int) ((indexI + a2fVertexOffset[i][0])*1 + (indexJ + a2fVertexOffset[i][1])*width + (indexK + a2fVertexOffset[i][2])*width*width);
			currentCube[i] = &(grid->getGrid()[cellIndex]);
			cubeValues[i] = currentCube[i]->value;
		}

		iFlagIndex = 0;
		for(i=0; i<8; i++)
		{
			if(cubeValues[i] <= isoValue)
				iFlagIndex |= 1<<i;
		}

		iEdgeFlags = aiCubeEdgeFlags[iFlagIndex];

		if(iEdgeFlags == 0)
			return;

		for(iEdge = 0; iEdge < 12; iEdge++)
		{
                if(iEdgeFlags & (1<<iEdge))
                {
                        fOffset = fGetOffset(cubeValues[ a2iEdgeConnection[iEdge][0] ],
                                                     cubeValues[ a2iEdgeConnection[iEdge][1] ], isoValue);

                        edgeVertex[iEdge].z = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][0]  +  fOffset * a2fEdgeDirection[iEdge][0]);
                        edgeVertex[iEdge].y = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][1]  +  fOffset * a2fEdgeDirection[iEdge][1]);
                        edgeVertex[iEdge].x = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][2]  +  fOffset * a2fEdgeDirection[iEdge][2]);

                        edgeVertex[iEdge].z += indexI;     edgeVertex[iEdge].y += indexJ;     edgeVertex[iEdge].x += indexK;
                }
        }

		newColor.r = newColor.g = newColor.b = newColor.a = 255;

        for(iTriangle = 0; iTriangle < 5; iTriangle++)
        {
                if(a2iTriangleConnectionTable[iFlagIndex][3*iTriangle] < 0)
                        break;

                vertexIndex3 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+0];
                vertexIndex2 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+1];
                vertexIndex1 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+2];

                vertices_.push_back(edgeVertex[vertexIndex1]);
                vertices_.push_back(edgeVertex[vertexIndex2]);
                vertices_.push_back(edgeVertex[vertexIndex3]);

                colors_.push_back(newColor);
                colors_.push_back(newColor);
                colors_.push_back(newColor);

                newNormal.calculateNormal(edgeVertex[vertexIndex1], edgeVertex[vertexIndex2], edgeVertex[vertexIndex3]);
                newNormal.normalize();
                normals_.push_back(newNormal);
                normals_.push_back(newNormal);
                normals_.push_back(newNormal);

                newFace.index[0] = vertices_.size() - 3;
                newFace.index[1] = vertices_.size() - 2;
                newFace.index[2] = vertices_.size() - 1;
                faces_.push_back(newFace);
        }
}

double Mesh::calculateIsovalue(Grid *grid)
{
    unsigned int i=0, index=0, mid=0;
    double minValue=0.0f, maxValue=0.0f;

// OVDJE RADIM SAD JOS!!!

    for (i=0; i<grid->getGridWidth(); i++)
    {
        index = i*grid->getGridWidth()*grid->getGridWidth() + i*grid->getGridWidth() + i;

        if (i == 0)
        {
            minValue = grid->getGrid()[index].value;
            maxValue = grid->getGrid()[index].value;
        }
        else
        {
            if (grid->getGrid()[index].value < minValue) minValue = grid->getGrid()[index].value;
            if (grid->getGrid()[index].value > maxValue) maxValue = grid->getGrid()[index].value;
        }
    }

    return minValue + (maxValue - minValue) * 1 / 4;
}



/*
bool Mesh::loadGrid(string gridPath, bool calculateIsovalue)
{
    FILE *fp;
    unsigned long int size=0;
    unsigned int temp_int=0;
    double target_value=0.0f;
	double temp_double=0.0f;

    target_value = isovalue;

    fp = fopen (where_from, "rb");
    if (fp == NULL)
        return false;

	fread(&temp_int, sizeof(unsigned int), 1, fp);
	size = temp_int;
	width = (unsigned long int) pow(size, 1.0f/3.0f);

	fread(&grid_size, sizeof(double), 1, fp);
	fread(&grid_cell_size, sizeof(double), 1, fp);



    if (vertices) { free(vertices); vertices = NULL;    }
    if (colors) { free(colors); colors = NULL;    }
    if (normals) { free(normals); normals = NULL;    }
    if (index) { free(index); index = NULL;    }
    if (grid)	{	free(grid); grid = NULL;	}



    if (grid == NULL)
        grid = (CGrid *) malloc (sizeof(CGrid) * (size+1));
    else
        grid = (CGrid *) realloc (grid, sizeof(CGrid) * (size+1));

    if (grid == NULL)
        return false;

    fread (&grid[0], 1, sizeof(CGrid)*size, fp);
    final_grid_loaded = true;
    fclose(fp);



    if (width > 0)
    {
		int i=0;
		double grid_step=0.0f;
//		grid_step = sqrt((grid[0].x-grid[1].x)*(grid[0].x-grid[1].x) + (grid[0].y-grid[1].y)*(grid[0].y-grid[1].y) + (grid[0].z-grid[1].z)*(grid[0].z-grid[1].z));
		grid_step = grid_cell_size;

		min_width = grid[0].x;
		max_width = grid[0].x;
		for (i=0; i<(width*width*width-1); i++)
		{
			if (grid[i].x < min_width)	min_width = grid[i].x;
			if (grid[i].y < min_width)	min_width = grid[i].y;
			if (grid[i].z < min_width)	min_width = grid[i].z;

			if (grid[i].x > max_width)	max_width = grid[i].x;
			if (grid[i].y > max_width)	max_width = grid[i].y;
			if (grid[i].z > max_width)	max_width = grid[i].z;
		}

		min_width -= grid_step/2.0f;
		max_width += grid_step/2.0f;

//		min_width /= 2;
//		max_width /= 2;


//		scale = (max_width - min_width) / width;


		scale = grid_cell_size;

		is_loaded = true;



		if (isovalue_set == true)
		{
			MarchingCubes(target_value, surface_color);
		}
		else
		{
			Optimal_Isovalue();
			MarchingCubes(isovalue, surface_color);
		}

		return true;
    }

    return false;
}

void Mesh::marchingCube(double fi, double fj, double fk, double fTargetValue, double fX, double fY, double fZ)
{
        long int iCorner, iVertex, iVertexTest, iEdge, iTriangle, iFlagIndex, iEdgeFlags;
        double fOffset;
        CVertex sColor;
        double afCubeValue[8];
        CVertex asEdgeVertex[12];
        CVertex asEdgeNorm[12];
        CGrid *temp_kocka[8];
        int i=0, iVertex1=0, iVertex2=0, iVertex3=0;
        unsigned long int temp_index=0;
        CVertex temp_normal;
        bool temp_bool[3];

        translation.x = fX;     translation.y = fY;     translation.z = fZ;

        for (i=0; i<8; i++)
        {
            temp_index = (unsigned long int) ((fi + a2fVertexOffset[i][0])*1 + (fj + a2fVertexOffset[i][1])*width + (fk + a2fVertexOffset[i][2])*width*width);
            temp_kocka[i] = &grid[temp_index];
             afCubeValue[i] = temp_kocka[i]->I;
        }

        iFlagIndex = 0;
        for(i=0; i<8; i++)
        {
                if(afCubeValue[i] <= fTargetValue) 
                        iFlagIndex |= 1<<i;
        }

        iEdgeFlags = aiCubeEdgeFlags[iFlagIndex];

        if(iEdgeFlags == 0) 
                return;

        for(iEdge = 0; iEdge < 12; iEdge++)
        {
                if(iEdgeFlags & (1<<iEdge))
                {
                        fOffset = fGetOffset(afCubeValue[ a2iEdgeConnection[iEdge][0] ], 
                                                     afCubeValue[ a2iEdgeConnection[iEdge][1] ], fTargetValue);

                        asEdgeVertex[iEdge].z = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][0]  +  fOffset * a2fEdgeDirection[iEdge][0]);
                        asEdgeVertex[iEdge].y = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][1]  +  fOffset * a2fEdgeDirection[iEdge][1]);
                        asEdgeVertex[iEdge].x = (a2fVertexOffset[ a2iEdgeConnection[iEdge][0] ][2]  +  fOffset * a2fEdgeDirection[iEdge][2]);

                        asEdgeVertex[iEdge].z += fi;     asEdgeVertex[iEdge].y += fj;     asEdgeVertex[iEdge].x += fk;
                }
        }

        for(iTriangle = 0; iTriangle < 5; iTriangle++)
        {
                if(a2iTriangleConnectionTable[iFlagIndex][3*iTriangle] < 0)
                        break;

                iVertex3 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+0];
                iVertex2 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+1];
                iVertex1 = a2iTriangleConnectionTable[iFlagIndex][3*iTriangle+2];

                temp_normal = CalculateNormal(asEdgeVertex[iVertex1], asEdgeVertex[iVertex2], asEdgeVertex[iVertex3]);

                Add_Vertex(asEdgeVertex[iVertex1], temp_normal);
                Add_Vertex(asEdgeVertex[iVertex2], temp_normal);
                Add_Vertex(asEdgeVertex[iVertex3], temp_normal);

                Add_Index(num_vertices-3);
                Add_Index(num_vertices-2);
                Add_Index(num_vertices-1);
        }
}

void Mesh::marchingCubes(double target_value, CColor surface_color)
{
    unsigned long int i=0, j=0, k=0;




    for (i=0; i<(width-1); i++)
        for (j=0; j<(width-1); j++)
            for (k=0; k<(width-1); k++)
            {
                MarchingCube(i, j, k, target_value, min_width, min_width, min_width);
            }

    if (colors == NULL)
        colors = (CColor *) calloc((num_vertices+1), sizeof(CColor));
    else
        colors = (CColor *) realloc(colors, sizeof(CColor) * (num_vertices+1));

    for (i=0; i<num_vertices; i++)
    {
		colors[i].r = surface_color.r;
		colors[i].g = surface_color.g;
		colors[i].b = surface_color.b;
		colors[i].a = surface_color.a;
    }
}



void Mesh::optimalIsovalue()
{
    unsigned int i=0, index=0, mid=0;
    double min_I=0.0f, max_I=0.0f;

    for (i=0; i<width; i++)
    {
        index = i*width*width + i*width + i;

        if (i == 0)
        {
            min_I = grid[index].I;
            max_I = grid[index].I;
        }
        else
        {
            if (grid[index].I < min_I) min_I = grid[index].I;
            if (grid[index].I > max_I) max_I = grid[index].I;
        }
    }

    isovalue = min_I + (max_I - min_I) * 1 / 4;
}

*/
