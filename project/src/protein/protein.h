/*
 * protein.h
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#ifndef PROTEIN_H_
#define PROTEIN_H_

#include "../structures/structures.h"
#include "../coefficients/coefficients.h"
#include "../translationmatrix/translationmatrix.h"
#include "../rotationmatrix/rotationmatrix.h"
#include "../grid/grid.h"
#include <string>

using namespace std;

class Coefficients;
class Grid;
class Docking;

class Protein
{
  friend class Coefficients;
  friend class Grid;
  friend class Docking;

public:
  Protein();
  Protein(const Coefficients& inner, const Coefficients& outer);
  Protein(const string& fnameInner, const string& fnameOuter);
  ~Protein();

  // set functions are probably time consuming! -> mpiskorec
  void setInnerSkin(const Coefficients& coefficients);
  void setOuterSkin(const Coefficients& coefficients);

  Coefficients& getInnerSkin();
  Coefficients& getOuterSkin();

  void rotate( const RotationMatrix& rotationMatrix);
  void rotateTo(Protein& destination, const RotationMatrix& rotationMatrix) const;
  void rotate(const double alpha);
  void rotateTo(Protein& destination, const double alpha) const;

  void qRotateTo(Protein& destination, const RotationMatrix& rotationMatrix, double Q) const;
  void qTransition(double Q);

  void translate(const TranslationMatrix& translationmatrix);
  void translate(const TranslationMatrix& translationmatrix, vector<int>& translationIndexes);
  void translateTo(Protein& destination, const TranslationMatrix& translationmatrix) const;
  void translateTo(Protein& destination, const TranslationMatrix& translationmatrix, vector<int>& translationIndexes) const;
  void calculateTranslationIndexes( vector<int>& translationIndexes ) const;

  int getOrder() const;

  void SetInnerSkinName(string str);

  void SetOuterSkinName(string str);

  string GetInnerSkinName() const;

  string GetOuterSkinName() const;

private:
  void checkOrders() const;
  string innerSkinName_ ;
  string outerSkinName_ ;

  Coefficients inner_;
  Coefficients outer_;
  bool qProteinState_;
};

#endif /* PROTEIN_H_ */
