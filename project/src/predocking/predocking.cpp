/*
 * predocking.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: ivan
 */

#include "predocking.h"



Predocking::Predocking()
{
	// load defaults
    protein_ = NULL;

	centerAtoms_ = 0;
	gridSize_ = 60;
	gridCellSize_ = 1;

	inner_.setGridSize(gridSize_, gridCellSize_);
	outer_.setGridSize(gridSize_, gridCellSize_);

	radiiPath_ = "data/atmtypenumbers";
	delta_ = 1;
	microDelta_ = 0.2;
	innerRadius_ = -1.6;
	outerRadius_ = 1.4;
}

Predocking::Predocking(Configuration &config, LoadFrom source)
{
    protein_ = NULL;
	loadConfig(config, source);
}

Predocking::~Predocking()
{
	if (protein_ != NULL) delete protein_;
}


void Predocking::loadConfig(Configuration &config, LoadFrom source)
{
	if (source != CALCULATE)
	{
		fprintf(stderr, "Loading coefficients from file\n");

		string t1, t2;

		if (source == FILE_LIGAND)
		{
			config.getParameter("ligand_inner_skin_coeffs", t1);
			config.getParameter("ligand_outer_skin_coeffs", t2);
		}
		else
		{
			config.getParameter("receptor_inner_skin_coeffs", t1);
			config.getParameter("receptor_outer_skin_coeffs", t2);
		}

		protein_ = new Protein(t1, t2);

		return;
	}

	int centerParam = 0;
	config.getParameter("center", centerParam);
	centerAtoms_ = centerParam;
	config.getParameter("radii_path", radiiPath_);

	config.getParameter("grid_size", gridSize_);
	config.getParameter("grid_cell_size", gridCellSize_);

	inner_.setGridSize(gridSize_, gridCellSize_);
	outer_.setGridSize(gridSize_, gridCellSize_);

	config.getParameter("microdelta", microDelta_);
	config.getParameter("delta", delta_);
	config.getParameter("inner_radius", innerRadius_);
	config.getParameter("outer_radius", outerRadius_);
}

void Predocking::parsePDB(const char *sourcePath, const char *destinationPath)
{
	pdbFile_.Init(sourcePath);

	if (!pdbFile_.LoadAtmtypenumbers(radiiPath_.c_str()))
	{
		exit(1);
	}

	pdbFile_.UseUnitedRadius();

//	pdbFile.Import(centerAtoms_);
	if (centerAtoms_ == 1)
	{
		pdbFile_.centerAtomsByMass();
		pdbFile_.Import(true);
	}
	else if (centerAtoms_ == 2)
	{
		pdbFile_.centerAtomsArithmetically();
		pdbFile_.Import(true);
	}
	else
	{
		pdbFile_.Import(false);
	}

	if (!pdbFile_.SaveCoords(destinationPath))
	{
		exit(1);
	}
}

void Predocking::getProtein(int order, Protein& protein)
{
	if (protein_ != NULL)
	{
		if (order == -1)
		{
			order = protein_->getOrder();
		}
		if (protein_->getOrder() != order)
		{
			fprintf(stderr, "Wrong order loaded from file (loaded %d, requested %d)\n", protein_->getOrder(), order);
			exit(1);
		}

		protein = (*protein_);

        return;
	}

	if (inner_.size() == 0 || outer_.size() == 0)
	{
		fprintf(stderr, "Skins not initialized\n");
		exit(1);
	}

	protein.setOrder(order);

	protein.getInnerSkin().calculateFromGrid(inner_);
	protein.getOuterSkin().calculateFromGrid(outer_);
}

void Predocking::calculateSkins(const string& PDBFilePath)
{
	if (protein_ != NULL) return;

//	MSMSWrapper msms;

	fprintf(stderr, "Parsing PDB from %s...\n", PDBFilePath.c_str());

	char parsedFilename[] = ".tmpParsed";
	parsePDB(PDBFilePath.c_str(), parsedFilename);

	msms_.init();
	msms_.load(parsedFilename);

	remove(parsedFilename);

	// inner skin calculation
	fprintf(stderr, "Generating inner skin...\n");
	inner_.generateSurfaceGrid(msms_, microDelta_, delta_, innerRadius_);

	// outer skin calculation
	fprintf(stderr, "Generating outer skin...\n");
	outer_.generateSurfaceGrid(msms_, microDelta_, delta_, outerRadius_);
}

void Predocking::calculateSkinsWithouthParsing()
{
	if (protein_ != NULL) return;

	// inner skin calculation
	fprintf(stderr, "Generating inner skin...\n");
	inner_.generateSurfaceGrid(msms_, microDelta_, delta_, innerRadius_);

/*
	Grid inflatedInner;
	string pathInner;
	pathInner = pdbFile_.getFileName();
	pathInner += "_inner.igrid";
	inflatedInner = inner_;
	inflatedInner.inflateGrid();
	inflatedInner.exportToFile(pathInner);
*/

	// outer skin calculation
	fprintf(stderr, "Generating outer skin...\n");
	outer_.generateSurfaceGrid(msms_, microDelta_, delta_, outerRadius_);

/*
	Grid inflatedOuter;
	string pathOuter;
	pathOuter = pdbFile_.getFileName();
	pathOuter += "_outer.igrid";
	inflatedOuter = outer_;
	inflatedOuter.inflateGrid();
	inflatedOuter.exportToFile(pathOuter);
*/
}

void Predocking::calculateSurface(const string& PDBFilePath, const char *parsedPdbPath)
{
	fprintf(stderr, "Calculating surface from %s...\n", PDBFilePath.c_str());

	if (!pdbFile_.SaveCoords(parsedPdbPath))
	{
		exit(1);
	}

	msms_.init();
	msms_.load(parsedPdbPath);
}

PdbFile& Predocking::getPdbFile()
{
	return pdbFile_;
}

