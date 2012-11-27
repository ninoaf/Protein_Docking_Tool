/*
 * coeffs.cpp
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#include "coefficients.h"
//#include "../../src/structures/structures.h"

Coefficients::Coefficients(int order)
{
	init(order);
}

Coefficients::Coefficients(int order, const Grid& grid)
{
	init(order);
	this->calculateFromGrid(grid);
}

Coefficients::Coefficients()
{
	init(-1);
}

void Coefficients::init(int order)
{
	order_ = order;
	if (order_ != -1)
	{
		coeffSize_ = getNumberOfCoefficients();
		coefficients_.resize(coeffSize_); // zasto !!!! treba reserve
	}
}

Coefficients::Coefficients(const string& fname)
{
	importFromFile(fname);
}

Coefficients::Coefficients(const Coefficients& source)
{
	order_         =  source.order_;
	coeffSize_     =  source.coeffSize_;
	coefficients_  = source.coefficients_;
}

Coefficients::~Coefficients()
{

}

int Coefficients::exportToFile(const string& fname) const
{

	if (this->coefficients_.size() == 0)
	{
		return -1;
	}

	FILE *fp;
	fp = fopen(fname.c_str(), "wb");
	if (fp == 0)
	{
		return -1;
	}

	int ret = 0;
	ret += fwrite(&(this->order_), sizeof(this->order_), 1, fp);

	CoeffValue coeffValue;
	int sizeCoeffValueCord =  sizeof(coeffValue.coeffCoord.n);
	int sizeCoeffValue = sizeof(coeffValue.value);
	for( int i= 0 ; i < (this->coeffSize_) ; ++i )
	{
		coeffValue = this->coefficients_[i];
		ret += fwrite(&(coeffValue.coeffCoord.n), sizeCoeffValueCord, 1, fp);
		ret += fwrite(&(coeffValue.coeffCoord.l), sizeCoeffValueCord, 1, fp);
		ret += fwrite(&(coeffValue.coeffCoord.m), sizeCoeffValueCord, 1, fp);
		ret += fwrite(&(coeffValue.value), sizeCoeffValue, 1, fp);
	}

	fclose(fp);
	return ret;
}


void Coefficients::dump(const string& fname) const
{
	printf("Writing coefficients to txt file %s\n", fname.c_str());

	FILE *fp;
	fp = fopen(fname.c_str(), "wb");
	if (fp == 0)
	{
		printf("nevalja nesto!\n");
		exit(1);
	}

	fprintf(fp, "%d\n", this->order_);

	CoeffValue coeffValue;
	for( int i= 0 ; i < (this->coeffSize_) ; ++i )
	{
		coeffValue = this->coefficients_[i];
		fprintf(fp, "(%d %d %d) -> %lf\n", coeffValue.coeffCoord.n, coeffValue.coeffCoord.l, coeffValue.coeffCoord.m, coeffValue.value);
	}

	fclose(fp);
}


int Coefficients::importFromFile(const string& fname)
{
	FILE *fp = fopen(fname.c_str(), "rb");

	//Log_Append(pdt_log_file, "...Loading coefficients from file %s...", fname);
	if (fp == 0)
	{
        fprintf(stderr, "Can't open file %s\nExiting...\n", fname.c_str());
        exit(1);
	}

	int ret = fread (&order_, sizeof(order_), 1, fp) ;

	if (order_ == 0)
	{
		return -1;
	}

	this->coeffSize_ = this->getNumberOfCoefficients();
	this->coefficients_.resize(this->coeffSize_);

	for (unsigned int i= 0; i < coefficients_.size(); ++i )
	{
		ret += fread ( &(coefficients_[i].coeffCoord.n), sizeof(int), 1, fp );
		ret += fread ( &(coefficients_[i].coeffCoord.l), sizeof(int), 1, fp );
		ret += fread ( &(coefficients_[i].coeffCoord.m), sizeof(int), 1, fp );
		ret += fread ( &(coefficients_[i].value), sizeof(double), 1, fp );
	}

	fclose(fp);

	return ret;
}

// imports coefficients from "old" file format [ order, (n,l,m,coeff) ... ]
// return value is number of loaded elements
int Coefficients::importFromOldFile(const string& fname)
{
	FILE *fp;

	//Log_Append(pdt_log_file, "...Loading coefficients from file %s...", fname);
	if ( (fp = fopen(fname.c_str(), "rb")) == 0 )
	{
		return -1;
	}

	int ret = 0;
	long long gridSize; // canadijevi koeficijenti (8 bajtova grid_size)

	ret += fread (&gridSize, sizeof(gridSize), 1, fp);

	for (order_ = 5; order_*(order_+1)*(2*order_+1) < 6*gridSize; ++order_);

	this->coeffSize_ = this->getNumberOfCoefficients();
	this->coefficients_.reserve( this->coeffSize_ );

	if (this->coeffSize_ != gridSize) {
		return -1;
	}

	CoeffValue coeffValue;
	for( int i= 0 ; i < (this->coeffSize_) ; ++i )
	{
		double _n, _m, _l;

		ret += fread ( &(_n), 8, 1, fp );
		ret += fread ( &(_l), 8, 1, fp );
		ret += fread ( &(_m), 8, 1, fp );
		ret += fread ( &(coeffValue.value), 8, 1, fp );

		coeffValue.coeffCoord.n = (int)(_n+1e-7);
		coeffValue.coeffCoord.l = (int)(_l+1e-7);
		coeffValue.coeffCoord.m = (int)(_m+1e-7);

		this->coefficients_.push_back( coeffValue );
	}

	fclose(fp);
	return ret;
}



bool Coefficients::calculateFromGrid(const Grid& grid)
{
	printf("Calculating coefficients from a given grid (order %d)...\n", order_);

	double grid_cell_volume = pow(grid.gridCellSize_ , 3);

	BaseFunctions* bf = BaseFunctions::instance();

	Coordinates coordinate;
	//GridValue gridValue;
	double sum = 0.0;
	int iCoef = 0;

	printf("Coefficients calculation started...\n");
	for (int n = 1; n <= order_; ++n)
	{
		printf("\r\tCurrent order: %d/%d", n, order_);
		fflush(stdout);

		for (int l = 0; l <= n-1; ++l)
		{

			for (int m = -l; m <= l; ++m)
			{
				coefficients_[iCoef].coeffCoord = CoeffCoordinates(n, l, m);
				sum = 0.0;

				for (unsigned int i = 0; i < grid.grid_.size(); ++i)
				{
					GridValue gridValue = grid.grid_[i];
					if (gridValue.value > cutoffValue_)
					{
						coordinate.x = gridValue.coord.x * grid.gridCellSize_;
						coordinate.y = gridValue.coord.y * grid.gridCellSize_;
						coordinate.z = gridValue.coord.z * grid.gridCellSize_;
						SphericalCoordinates sc(coordinate);

						sum += gridValue.value * bf->baseFunction(coefficients_[iCoef].coeffCoord, sc);

						//sum += Radial_Function(n, l, sc.radius) *
						//	Legendre_Polynomial_Spherical(l, abs(m), cos(sc.elevation)) *
						//		Phi(m, sc.azimuth) * gridValue.value;
					}
				}

				coefficients_[iCoef++].value = grid_cell_volume * sum;
			}
		}
	}

//	printf("\r\tCurrent order: %d/%d\n", order_, order_);
	printf("...OK! (calculateFromGrid finished successfully)\n");

	return true;
}
bool Coefficients::calculateChargeCoeffsFromGrid(const Grid& grid)
{
	printf("Calculating Charge density coefficients from a given grid (order %d)...\n", order_);

	double grid_cell_volume = pow(grid.gridCellSize_ , 3);

	BaseFunctions* bf = BaseFunctions::instance();

	Coordinates coordinate;
	//GridValue gridValue;
	double sum = 0.0;
	int iCoef = 0;

	printf("Coefficients calculation started\n");
	for (int n = 1; n <= order_; ++n)
	{
		printf("%d\n", n);
		for (int l = 0; l <= n-1; ++l)
		{

			for (int m = -l; m <= l; ++m)
			{
				coefficients_[iCoef].coeffCoord = CoeffCoordinates(n, l, m);
				sum = 0.0;

				for (unsigned int i = 0; i < grid.grid_.size(); ++i)
				{
					GridValue gridValue = grid.grid_[i];
					coordinate.x = gridValue.coord.x * grid.gridCellSize_; /// zasto pitam ?
					coordinate.y = gridValue.coord.y * grid.gridCellSize_;
					coordinate.z = gridValue.coord.z * grid.gridCellSize_;
					SphericalCoordinates sc(coordinate);

					sum += gridValue.value * bf->ETOradialFunction(n, l, sc.radius)* 
						bf->legendrePolynomialSpherical(l, abs(m), cos(sc.elevation)) * 
						bf->phi(m, sc.azimuth);	
				}

				coefficients_[iCoef++].value = grid_cell_volume * sum;
			}
		}
	}

	printf("...OK! (calculateFromGrid finished successfully)\n");

	return true;
}


/** Number of coefficients for a given order.
 */
int Coefficients::getNumberOfCoefficients() const
{
  // order_ = -1 indicates that no coefficients are loaded (return value is zero)
	return (order_ * (2*order_ + 1) * (order_+1)) / 6;
}

int Coefficients::getOrder() const
{
  return order_;
}

// For coordinates (n, l, m) returns their index in coefficients_.
int Coefficients::getIndex(int n, int l, int m) const
{
	return ((n-1) * n * (2*n-1))/6 + l*l + l + m;
}

void Coefficients::testGetIndex() const
{
	printf("Testiram funkciju getIndex...\n");
	for (unsigned int i = 0; i < coefficients_.size(); ++i)
	{
		if (getIndex(coefficients_[i].coeffCoord.n, coefficients_[i].coeffCoord.l, coefficients_[i].coeffCoord.m) != (int)i)
		{
			printf("Greska %d %d!\n", getIndex(coefficients_[i].coeffCoord.n, coefficients_[i].coeffCoord.l, coefficients_[i].coeffCoord.m), i);
		}
	}
	printf("Gotov test\n");
}

double Coefficients::getValue(int n, int l, int m) const
{
	return coefficients_[getIndex(n, l, m)].value;
}
double Coefficients::getValue(int index) const
{
	return coefficients_[index].value;
}

/** Rotating the coefficients for a given rotation angle, the angles of rotation are
 *  stored in angle_array[angle_index].
*/
void Coefficients::rotate(const RotationMatrix& rotationMatrix)
{
	Coefficients* newTmp = new Coefficients(*this);
	newTmp->rotateTo(*this, rotationMatrix);
	delete newTmp;
}

// Rotates coefficients, and saves the result to destination
void Coefficients::rotateTo(Coefficients& destination, const RotationMatrix& rotationMatrix) const
{
	destination.init(order_);
	int iCoefDest = 0, iCoefSource = 0;

	// triple loop for passing through all of the coefficients
	for (int n = 1; n <= this->order_; n++)
	for (int l = 0; l <= n-1; l++)
	{
		for (int m = -l; m <= l; m++, iCoefDest++)
		{
			destination.coefficients_[iCoefDest].coeffCoord = CoeffCoordinates(n, l, m);
			destination.coefficients_[iCoefDest].value = 0.0;

			// sumation loop that adds all coefficients from -m' to m
			for (int m_crt = -l; m_crt <= l; m_crt++)
			{
				destination.coefficients_[iCoefDest].value += this->coefficients_[iCoefSource + l + m_crt].value * getElement(l, m_crt, m, rotationMatrix.matrix_[l]);
			}
	    }
	    // iCoefSource allways indexes the first element with given l
	    iCoefSource += 2*l+1;
	}
}



// Rotates coefficients, and saves the result to destination
void Coefficients::qRotateTo(Coefficients& destination,const Coefficients& inner, double Q, const RotationMatrix& rotationMatrix) const
{
	destination.init(order_);
	int iCoefDest = 0, iCoefSource = 0;

	// triple loop for passing through all of the coefficients
	for (int n = 1; n <= this->order_; n++)
	for (int l = 0; l <= n-1; l++)
	{
		for (int m = -l; m <= l; m++, iCoefDest++)
		{
			destination.coefficients_[iCoefDest].coeffCoord = CoeffCoordinates(n, l, m);
			destination.coefficients_[iCoefDest].value = 0.0;

			// sumation loop that adds all coefficients from -m' to m
			for (int m_crt = -l; m_crt <= l; m_crt++)
			{
				destination.coefficients_[iCoefDest].value += ( this->coefficients_[iCoefSource + l + m_crt].value - (Q * inner.getValue(iCoefSource + l + m_crt) ) ) * getElement(l, m_crt, m, rotationMatrix.matrix_[l]);
				
			}
	    }
	    // iCoefSource allways indexes the first element with given l
	    iCoefSource += 2*l+1;
	}
}

void Coefficients::qTransition(const Coefficients& inner, double Q)
{
	for (int i = 0; i < coeffSize_; ++i)
	{
		this->coefficients_[i].value -= (Q * inner.coefficients_[i].value);
		
	}

}
void Coefficients::rotate(const double alpha)
{
	Coefficients* newTmp = new Coefficients(*this);
	newTmp->rotateTo(*this, alpha);
	delete newTmp;
}

void Coefficients::rotateTo(Coefficients& destination, const double alpha) const
{
	int counter = 0;
	destination.init(getOrder());

	TrigonometricCaching* tc = TrigonometricCaching::instance();

	for (int n = 1; n <= order_; ++n)
	for (int l = 0; l <= n-1; ++l)
	for (int m = -l; m <= l; ++m)
	{
		destination.coefficients_[counter].value = coefficients_[counter].value * tc->cosm(m, alpha) +
				coefficients_[counter - 2*m].value * tc->sinm(-m, alpha);
		destination.coefficients_[counter++].coeffCoord = CoeffCoordinates(n, l, m);
	}
}

// Merges two Coefficients
bool Coefficients::merge(const Coefficients& with)
{
	if (with.coefficients_.size() != this->coefficients_.size()) return false;

	for (unsigned int i = 0; i < coefficients_.size(); ++i)
	{
		this->coefficients_[i].value += with.coefficients_[i].value;
	}

	return true;
}

double Coefficients::compareCoefficientsTo(Coefficients& coefficients)
{
  double difference = 0;

  vector<CoeffValue>::size_type coefficientsCount = this->coefficients_.size();

  for (unsigned int i = 0; i < coefficientsCount; i++)
  {
    difference += ( this->coefficients_[i].value - coefficients.coefficients_[i].value ) * ( this->coefficients_[i].value - coefficients.coefficients_[i].value );
  }

  return difference;
}


void Coefficients::translate(const TranslationMatrix& translationmatrix)
{
	
	Coefficients* newTmp = new Coefficients(*this);
	newTmp->translateTo(*this, translationmatrix);
	delete newTmp;
}
void Coefficients::translate(const TranslationMatrix& translationmatrix, vector<int>& translationIndexes)
{
	Coefficients* newTmp = new Coefficients(*this);
	newTmp->translateTo(*this, translationmatrix, translationIndexes);
	delete newTmp;
}
void Coefficients::translateTo(Coefficients& destination, const TranslationMatrix& translationmatrix) const
{
	int iTrans = 0, iCoef = 0;
	destination.init(order_);

	destination.coefficients_.resize(destination.coeffSize_);
	fill(destination.coefficients_.begin(), destination.coefficients_.end(), CoeffValue());

	for (int _n = 1;     _n <= order_;  _n++)
	for (int _l = 0;     _l <= _n-1;    _l++)
	for (int m  = -_l;   m  <= _l;      m ++, iCoef++)
	{
		destination.coefficients_[iCoef].coeffCoord = CoeffCoordinates(_n, _l, m);
		for (int n  = 1;     n  <= order_;  n ++)
		for (int l  = abs(m);     l  <= n-1;     l ++)
		{
			destination.coefficients_[iCoef].value +=  translationmatrix.matrix_[iTrans++] * this->getValue(n, l, m);
		}
	}
}
void Coefficients::translateTo(Coefficients& destination, const TranslationMatrix& translationmatrix, vector<int>& translationIndexes) const
{
	
	int iTrans = 0, iCoef = 0;
	destination.init(order_);

	destination.coefficients_.resize(destination.coeffSize_);
	fill(destination.coefficients_.begin(), destination.coefficients_.end(), CoeffValue());

	for (int _n = 1;     _n <= order_;  _n++)
	for (int _l = 0;     _l <= _n-1;    _l++)
	for (int m  = -_l;   m  <= _l;      m ++, iCoef++)
	{
		destination.coefficients_[iCoef].coeffCoord = CoeffCoordinates(_n, _l, m);
		for (int n  = 1;     n  <= order_;  n ++)
		for (int l  = abs(m);     l  <= n-1;     l ++)
		{
			destination.coefficients_[iCoef].value +=  translationmatrix.matrix_[iTrans] * this->coefficients_[translationIndexes[iTrans]].value;
			iTrans++;
		}
	}
}
void Coefficients::calulateTranslationIndexes( vector<int>& translationIndexes ) const
{
	translationIndexes.resize((order_ * order_ * (order_+1) * (order_+1) * (2*order_+1)) / 12);
	int iTrans = 0;
	for (int _n = 1;     _n <= order_;  _n++)
	for (int _l = 0;     _l <= _n-1;    _l++)
	for (int m  = -_l;   m  <= _l;      m ++)
	{
		for (int n  = 1;     n  <= order_;  n ++)
		for (int l  = abs(m);     l  <= n-1;     l ++)
		{
			translationIndexes[iTrans++] = this->getIndex(n, l, m);
		}
	}

}
