/*
 * protein.cpp
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#include "protein.h"


Protein::Protein(const Coefficients& inner, const Coefficients& outer)
{
	this->inner_ = inner;
	this->outer_ = outer;
	this->qProteinState_ = false;

	checkOrders();
}

Protein::Protein(const string& fnameInner, const string& fnameOuter)
{
	inner_.importFromFile(fnameInner);
	outer_.importFromFile(fnameOuter);
	this->qProteinState_ = false;

	checkOrders();
}

Protein::Protein()
{
	this->qProteinState_ = false;
}

Protein::~Protein()
{

}

void Protein::SetInnerSkinName(string str)
{
	  innerSkinName_ = str;
}

void Protein::SetOuterSkinName(string str)
{
	  outerSkinName_ = str;
}

string Protein::GetInnerSkinName() const
{
	  return innerSkinName_;
}

string Protein::GetOuterSkinName() const
{
	  return outerSkinName_;
}

void Protein::checkOrders() const
{
	if (inner_.getOrder() != outer_.getOrder())
	{
		fprintf(stderr, "Order of coefficients for inner & outer skin differ.\n");
		exit(1);
	}
}

void Protein::setInnerSkin(const Coefficients& coefficients)
{
	inner_ = coefficients;

	checkOrders();
}

void Protein::setOuterSkin(const Coefficients& coefficients)
{
	outer_ = coefficients;

	checkOrders();
}

Coefficients& Protein::getInnerSkin()
{
	return inner_;
}

Coefficients& Protein::getOuterSkin()
{
	return outer_;
}

void Protein::rotate(const RotationMatrix& rotationMatrix)
{
	inner_.rotate(rotationMatrix);
	outer_.rotate(rotationMatrix);

}

void Protein::rotateTo(Protein& destination, const RotationMatrix& rotationMatrix) const
{
	inner_.rotateTo(destination.inner_, rotationMatrix);
	outer_.rotateTo(destination.outer_, rotationMatrix);
}
  
void Protein::qRotateTo(Protein& destination, const RotationMatrix& rotationMatrix, double Q) const
{
	// Redoslijed bitan ako radimo samo rotate na isti, jer se inner promijeni
	outer_.qRotateTo( destination.outer_, inner_, Q, rotationMatrix);
	inner_.rotateTo( destination.inner_, rotationMatrix);
	destination.qProteinState_ = true;
}

void Protein::qTransition(double Q)
{
	outer_.qTransition( inner_, Q );
	qProteinState_ = true;
}
void Protein::rotate(const double alpha)
{
	inner_.rotate(alpha);
	outer_.rotate(alpha);
}

void Protein::rotateTo(Protein& destination, const double alpha) const
{
	inner_.rotateTo(destination.inner_, alpha);
	outer_.rotateTo(destination.outer_, alpha);
}

void Protein::translate(const TranslationMatrix& translationmatrix)
{
	inner_.translate(translationmatrix);
	outer_.translate(translationmatrix);
}
void Protein::translate(const TranslationMatrix& translationmatrix, vector<int>& translationIndexes)
{
	inner_.translate(translationmatrix, translationIndexes);
	outer_.translate(translationmatrix, translationIndexes);
}
void Protein::translateTo(Protein& destination, const TranslationMatrix& translationmatrix) const
{
	inner_.translateTo(destination.inner_, translationmatrix);
	outer_.translateTo(destination.outer_, translationmatrix);
}

void Protein::translateTo(Protein& destination, const TranslationMatrix& translationmatrix, vector<int>& translationIndexes) const
{
	inner_.translateTo(destination.inner_, translationmatrix, translationIndexes);
	outer_.translateTo(destination.outer_, translationmatrix, translationIndexes);
}
void Protein::calculateTranslationIndexes( vector<int>& translationIndexes ) const
{
	inner_.calulateTranslationIndexes( translationIndexes );
}
int Protein::getOrder() const
{
	return inner_.getOrder();
}
