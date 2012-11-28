/*
 * docking.cpp
 *
 *  Created on: Sep 29, 2009
 *      Author: canadi
 */

#include "docking.h"

ScoreConfiguration::ScoreConfiguration()
{
	R = 0.0f; alpha = 0.0f; beta1 = 0.0f; gamma1 = 0.0f; beta2 = 0.0f; gamma2 = 0.0f;
}

ScoreConfiguration::ScoreConfiguration(double _R, double _alpha, double _beta1, double _gamma1, double _beta2, double _gamma2)
{
	R = _R; alpha = _alpha; beta1 = _beta1; gamma1 = _gamma1; beta2 = _beta2; gamma2 = _gamma2;
}

bool ScoreConfiguration::operator < (const ScoreConfiguration& a) const
{
    if (this->R != a.R) return this->R < a.R;
    if (this->alpha != a.alpha) return this->alpha < a.alpha;
    if (this->beta1 != a.beta1) return this->beta1 < a.beta1;
    if (this->gamma1 != a.gamma1) return this->gamma1 < a.gamma1;
    if (this->beta2 != a.beta2) return this->beta2 < a.beta2;

	return (this->gamma2) < (a.gamma2);
}

// first -- inner; second -- outer
Docking::Docking(const pair<string, string>& receptorFile, const pair<string, string>& ligandFile)
{
    exit(1);	ligandPath_ = "";
	receptorPath_ = "";
	radiiPath_ = "";
	receptor_.inner_.importFromFile(receptorFile.first);
	receptor_.outer_.importFromFile(receptorFile.second);

	ligand_.inner_.importFromFile(ligandFile.first);
	ligand_.outer_.importFromFile(ligandFile.second);

	setDefaultParameters();
	checkOrders();
	rotatationsCalculated_ = false;
	trigonometricCalculated_ = false;
	coeffMappingNLMCalculated_ = false;

	ligandPath_ = "";
	receptorPath_ = "";
	radiiPath_ = "";
}

Docking::Docking(const Grid& receptorInner, const Grid& receptorOuter, const Grid& ligandInner, const Grid& ligandOuter, int order)
{
    exit(1);
	receptor_.inner_.init(order);
	receptor_.outer_.init(order);
	ligand_.inner_.init(order);
	ligand_.outer_.init(order);

	receptor_.inner_.calculateFromGrid(receptorInner);
	receptor_.outer_.calculateFromGrid(receptorOuter);

	ligand_.inner_.calculateFromGrid(ligandInner);
	ligand_.outer_.calculateFromGrid(ligandOuter);

	setDefaultParameters();
	checkOrders();
	rotatationsCalculated_ = false;
	trigonometricCalculated_ = false;
	coeffMappingNLMCalculated_ = false;

	ligandPath_ = "";
	receptorPath_ = "";
	radiiPath_ = "";
}

Docking::Docking(Configuration &config)
{
	string t;

	config.getParameter("receptor_inner_skin_coeffs", t);
	receptor_.inner_.importFromFile(t);
	receptor_.SetInnerSkinName(t); //For protein recognition

	config.getParameter("receptor_outer_skin_coeffs", t);
	receptor_.outer_.importFromFile(t);
	receptor_.SetOuterSkinName(t);

	config.getParameter("ligand_inner_skin_coeffs", t);
	ligand_.inner_.importFromFile(t);
	ligand_.SetInnerSkinName(t);

	config.getParameter("ligand_outer_skin_coeffs", t);
	ligand_.outer_.importFromFile(t);
	ligand_.SetOuterSkinName(t);

	config.getParameter("ligand", t);
	ligandPath_ = t;
	config.getParameter("receptor", t);
	receptorPath_ = t;
	config.getParameter("radii_path", t);
	radiiPath_ = t;



	int loadFromFile = 0;
	config.getParameter("load_coeffs_from_file", loadFromFile);

	loadParametersFromConfiguration(config);

	ligandPredocking_.loadConfig(config, loadFromFile ? FILE_LIGAND : CALCULATE);
	receptorPredocking_.loadConfig(config, loadFromFile ? FILE_RECEPTOR : CALCULATE);

	if (!loadFromFile)
	{
		ligandPredocking_.calculateSkins(ligandPath_);
		receptorPredocking_.calculateSkins(receptorPath_);
	}

	checkOrders();
	rotatationsCalculated_ = false;
	trigonometricCalculated_ = false;
	coeffMappingNLMCalculated_ = false;
}

Docking::Docking(std::string configPath)
{
	Configuration config;
	string t;

	config.init(configPath);

	config.getParameter("receptor_inner_skin_coeffs", t);
	receptor_.inner_.importFromFile(t);
	receptor_.SetInnerSkinName(t); //For protein recognition

	config.getParameter("receptor_outer_skin_coeffs", t);
	receptor_.outer_.importFromFile(t);
	receptor_.SetOuterSkinName(t);

	config.getParameter("ligand_inner_skin_coeffs", t);
	ligand_.inner_.importFromFile(t);
	ligand_.SetInnerSkinName(t);

	config.getParameter("ligand_outer_skin_coeffs", t);
	ligand_.outer_.importFromFile(t);
	ligand_.SetOuterSkinName(t);

	config.getParameter("ligand", t);
	ligandPath_ = t;
	config.getParameter("receptor", t);
	receptorPath_ = t;
	config.getParameter("radii_path", t);
	radiiPath_ = t;



	int loadFromFile = 0;
	config.getParameter("load_coeffs_from_file", loadFromFile);

	loadParametersFromConfiguration(config);

	ligandPredocking_.loadConfig(config, loadFromFile ? FILE_LIGAND : CALCULATE);
	receptorPredocking_.loadConfig(config, loadFromFile ? FILE_RECEPTOR : CALCULATE);

	if (!loadFromFile)
	{
		ligandPredocking_.calculateSkins(ligandPath_);
		receptorPredocking_.calculateSkins(receptorPath_);
	}

	checkOrders();
	rotatationsCalculated_ = false;
	trigonometricCalculated_ = false;
	coeffMappingNLMCalculated_ = false;
}

Docking::~Docking()
{
	//delete [] rotationAngles_;
	//delete [] rotReceptor_;
	//delete [] rotLigand_;
}
void Docking::setDefaultParameters()
{
	translationPath_ = "data/trans";
	tessellationOrder_ = 2;
	alphaSize_ = 5;
	penalty_ = 15.0;
	scoresSize_ = 100;
	radiusStart_ = 8.0;
	radiusEnd_ = 14.9;
}

void Docking::loadParametersFromConfiguration(Configuration &config)
{
	config.getParameter("translation_matrices_path", translationPath_);
	config.getParameter("tessellation_order", tessellationOrder_);
	config.getParameter("alpha_angles", alphaSize_);
	config.getParameter("penetration_penalty", penalty_);
	config.getParameter("scores_size", scoresSize_);

	double t;
	config.getParameter("radius_search_start", t);
	for (radiusStart_ = 0.0; radiusStart_+0.5 < t+1e-9; radiusStart_ += 0.5); // calibration to known radius

	config.getParameter("radius_search_end", radiusEnd_);
}

void Docking::dumpParameters(FILE *fp) const
{
	fprintf(fp, "# ligand inner skin name: %s\n", ligand_.GetInnerSkinName().c_str());
	fprintf(fp, "# ligand outer skin name: %s\n", ligand_.GetOuterSkinName().c_str());
	fprintf(fp, "# receptor inner skin name: %s\n", receptor_.GetInnerSkinName().c_str());
	fprintf(fp, "# receptor outer skin name: %s\n", receptor_.GetOuterSkinName().c_str());
	fprintf(fp, "# orderOfCoefficients: %d\n", receptor_.getOrder());
	fprintf(fp, "# translationPath: %s\n", translationPath_.c_str());
	fprintf(fp, "# tessellationOrder: %d\n", tessellationOrder_);
	fprintf(fp, "# alphaSize: %d\n", alphaSize_ );
	fprintf(fp, "# penalty: %lf\n", penalty_);
	fprintf(fp, "# scoresSize: %d\n", scoresSize_);
	fprintf(fp, "# radiusStart: %lf\n", radiusStart_);
	fprintf(fp, "# radiusEnd: %lf\n", radiusEnd_ );
}

double Docking::scoreIt(Protein& receptor, Protein& ligand, double Q)
{
	double score = 0.0;

    unsigned int coeffSize = receptor.inner_.coefficients_.size();
	for (unsigned int i = 0; i < coeffSize; ++i)
	{
		score += receptor.inner_.coefficients_[i].value*ligand.outer_.coefficients_[i].value 
            + receptor.outer_.coefficients_[i].value*ligand.inner_.coefficients_[i].value - Q*receptor.inner_.coefficients_[i].value*ligand.inner_.coefficients_[i].value;
	}

	return score;
}

void Docking::calculateProteinCoefficients(int order)
{
	fprintf(stderr, "Calculating Ligand coefficients\n");
	ligandPredocking_.getProtein(order, ligand_);
	fprintf(stderr, "Calculating Receptor coefficients\n");
	receptorPredocking_.getProtein(order, receptor_);
}

void Docking::preDockingCalculateRotations(void)
{
	if (rotatationsCalculated_ == false)
	{
		//printf("Kalkulisem rotacije\n");
		int raSize = 20*(1<<(tessellationOrder_*2))+1;
		rotationAngles_ = new RotationAngle[raSize];

		//printf("Generating Rotational Angles...\n");
		Rotational_Angles(tessellationOrder_, rotationAngles_);
		//printf("Generated Rotational Angles (%d of them)...\n", raSize);

		rotReceptor_ = new Protein[raSize];
		rotLigand_   = new Protein[raSize*alphaSize_];

		RotationMatrix rotationMatrixGamma, rotationMatrixBeta;

		//printf("Rotating receptor & ligand...\n");
		for (int i = 0; i < raSize; ++i)
		{
			rotationMatrixGamma.calculateMatrix(receptor_.getOrder(), RotationAngle(0, rotationAngles_[i].gamma));
			rotationMatrixBeta.calculateMatrix(receptor_.getOrder(), RotationAngle(rotationAngles_[i].beta, 0.0));

			receptor_.rotateTo(rotReceptor_[i],            rotationMatrixGamma);
			rotReceptor_[i].rotate(rotationMatrixBeta);

			ligand_.rotateTo  (rotLigand_  [i*alphaSize_], rotationMatrixGamma);
			rotLigand_[i*alphaSize_].rotate(rotationMatrixBeta);

			// if (i%10 == 0) printf("...receptor %d...ligand %d...\n", i, i*alphaSize_);

			for (int j = 1; j < alphaSize_; ++j)
			{
				rotLigand_[i*alphaSize_].rotateTo(rotLigand_[i*alphaSize_+j], ((2.0*PI)/alphaSize_) * j);
			}
		}
		//printf("Rotated successfully (total %d receptor, %d ligand)...\n", raSize, raSize*alphaSize_);

		rotatationsCalculated_ = true;
	}
}
void Docking::dockingSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores)
{
	RotationMatrix rotationMatrixGamma1, rotationMatrixBeta1;
	RotationMatrix rotationMatrixGamma2, rotationMatrixBeta2;

	rotationMatrixGamma1.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma1) );
	rotationMatrixBeta1.calculateMatrix(receptor_.getOrder(), RotationAngle( beta1, 0.0) );
	rotationMatrixGamma2.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma2) );
	rotationMatrixBeta2.calculateMatrix(receptor_.getOrder(), RotationAngle( beta2, 0.0));
	
	rotReceptor_ = new Protein[1];
	rotLigand_   = new Protein[alphaSize_];

	receptor_.rotateTo(rotReceptor_[0], rotationMatrixGamma1);
	rotReceptor_[0].rotate(rotationMatrixBeta1);
	
	ligand_.rotateTo  (rotLigand_[0], rotationMatrixGamma2);
	rotLigand_[0].rotate(rotationMatrixBeta2);

	Protein *transTmp; 
	if (R > 0)
	{
		transTmp = new Protein;
		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		rotReceptor_[0].translateTo(*transTmp, translationmatrix);
	}else
	{
		transTmp = &rotReceptor_[0];
	}

	set <pair<double, ScoreConfiguration> > bestScores;
	scores.clear();
	double minScore = 10000000.0, maxScore = -10000000.0;
	for (int j = 1; j < alphaSize_; ++j)
	{
		rotLigand_[0].rotateTo(rotLigand_[j], ((2.0*PI)/alphaSize_) * j);
		double tmpScore = scoreIt(*transTmp, rotLigand_[j], penalty_);
		printf("%lf \n", tmpScore);

		bestScores.insert(make_pair(tmpScore,ScoreConfiguration(R, ((2.0*PI)/alphaSize_) * j, beta1, gamma1, beta2, gamma2)));

		minScore = min(minScore, tmpScore);
		maxScore = max(maxScore, tmpScore);
		while ((int)bestScores.size() > scoresSize_)
		{
			bestScores.erase(bestScores.begin());
		}
	}
	printf("For R:%lf min score is %lf; max score is %lf\n",R, minScore, maxScore);
	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	if (R>0) delete transTmp;
}
void Docking::dockingQsearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores)
{
	RotationMatrix rotationMatrixGamma1, rotationMatrixBeta1;
	RotationMatrix rotationMatrixGamma2, rotationMatrixBeta2;

	rotationMatrixGamma1.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma1) );
	rotationMatrixBeta1.calculateMatrix(receptor_.getOrder(), RotationAngle( beta1, 0.0) );
	rotationMatrixGamma2.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma2) );
	rotationMatrixBeta2.calculateMatrix(receptor_.getOrder(), RotationAngle( beta2, 0.0));
	
	rotReceptor_ = new Protein[1];
	qRotLigand_   = new Protein[1];

	receptor_.rotateTo(rotReceptor_[0], rotationMatrixGamma1);
	rotReceptor_[0].rotate(rotationMatrixBeta1);
	
	ligand_.rotateTo  (qRotLigand_[0], rotationMatrixGamma2);
	qRotLigand_[0].rotate(rotationMatrixBeta2);
	qRotLigand_[0].qTransition(penalty_); 

	Protein *transReceptor; 
	if (R > 0)
	{
		transReceptor = new Protein;
		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		vector<int> translationIndexes;
		rotReceptor_[0].calculateTranslationIndexes( translationIndexes );
		rotReceptor_[0].translateTo(*transReceptor, translationmatrix, translationIndexes);	
	}else
	{
		transReceptor = &rotReceptor_[0];
	}

	set <pair<double, ScoreConfiguration> > bestScores;
	scores.clear();
	double minScore = 10000000.0, maxScore = -10000000.0;

	vector<double> qCoeffPlusPlus, qCoeffMinusMinus;
	int order = receptor_.getOrder();
	qCoeffPlusPlus.resize(order, 0.0);
	qCoeffMinusMinus.resize(order, 0.0);

	trigonometricCash();
	calculateCoeffMapping( );

	vector<double> qCoeffPlus;
	qCoeffPlus.resize((2* order - 1), 0.0); 
	vector<double> qCoeffMinus;
	qCoeffMinus.resize((2* order - 1), 0.0);
	//calculateQcoeffPlusPlus(qCoeffPlusPlus, qCoeffPlus ,*transReceptor, qRotLigand_[0] );
	//calculateQcoeffMinusMinus(qCoeffMinusMinus,qCoeffMinus, *transReceptor, qRotLigand_[0] );

	calculateQcoeffs(qCoeffPlusPlus, qCoeffPlus, qCoeffMinusMinus, qCoeffMinus,*transReceptor, qRotLigand_[0]);
	
	printf("Q Coeff plus plus : \n");
	for(int i = 0 ; i < qCoeffPlusPlus.size(); ++i) printf("%lf \n",qCoeffPlusPlus[i]);

	printf("Q Coeff minus minus : \n");
	for(int i = 0 ; i < qCoeffMinusMinus.size(); ++i) printf("%lf \n",qCoeffMinusMinus[i]);

	printf("Alfa function: \n");
	for (int j = 1; j < alphaSize_; ++j)
	{
		double tmpScore = qCoeffPlusPlus[0];
		int index_alfa = j*order;
		for (int m = 1; m <= (order-1); ++m)
		{
			double alfa2angle = j*((2.0*PI)/alphaSize_);
			//tmpScore += (qCoeffPlusPlus[m] * cos(m*alfa2angle) ) + (qCoeffMinusMinus[m] * sin(m*alfa2angle) );
			tmpScore += (qCoeffPlusPlus[m] * cosValue_->at(index_alfa+m) ) + (qCoeffMinusMinus[m] * sinValue_->at(index_alfa+m) );
		}
		printf("%lf \n", tmpScore);

		bestScores.insert(make_pair(tmpScore,ScoreConfiguration(R, ((2.0*PI)/alphaSize_) * j, beta1, gamma1, beta2, gamma2)));

		minScore = min(minScore, tmpScore);
		maxScore = max(maxScore, tmpScore);
		while ((int)bestScores.size() > scoresSize_)
		{
			bestScores.erase(bestScores.begin());
		}
	}

	printf("For R:%lf min score is %lf; max score is %lf\n",R, minScore, maxScore);
	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	if (R>0) delete transReceptor;
}
void Docking::dockingQoriginalSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores)
{
	
	/*RotationMatrix rotationMatrixGamma1, rotationMatrixBeta1;
	RotationMatrix rotationMatrixGamma2, rotationMatrixBeta2;

	rotationMatrixGamma1.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma1) );
	rotationMatrixBeta1.calculateMatrix(receptor_.getOrder(), RotationAngle( beta1, 0.0) );
	rotationMatrixGamma2.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma2) );
	rotationMatrixBeta2.calculateMatrix(receptor_.getOrder(), RotationAngle( beta2, 0.0));
	
	rotReceptor_ = new Protein[1];
	qRotLigand_   = new Protein[alphaSize_];

	receptor_.rotateTo(rotReceptor_[0], rotationMatrixGamma1);
	rotReceptor_[0].rotate(rotationMatrixBeta1);
	
	ligand_.rotateTo  (qRotLigand_[0], rotationMatrixGamma2);
	qRotLigand_[0].rotate(rotationMatrixBeta2);
	qRotLigand_[0].qTransition(penalty_); 

	Protein *transReceptor; 
	if (R > 0)
	{
		transReceptor = new Protein;
		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		rotReceptor_[0].translateTo(*transReceptor, translationmatrix);
	}else
	{
		transReceptor = &rotReceptor_[0];
	}

	
	set <pair<double, ScoreConfiguration> > bestScores;
	scores.clear();
	double minScore = 10000000.0, maxScore = -10000000.0;
	int order = receptor_.getOrder();

	for (int j = 1; j < alphaSize_; ++j)
	{
		
		double alfa2angle = j*((2.0*PI)/alphaSize_);
		qRotLigand_[0].rotateTo(qRotLigand_[j], alfa2angle);

		double tmpScore = 0.0;
		unsigned int coeffSize = receptor_.inner_.coefficients_.size();

		for (unsigned int i = 0; i < coeffSize; ++i)
		{
			double tmpScore1 = transReceptor->outer_.coefficients_[i].value * qRotLigand_[j].inner_.coefficients_[i].value;
			double tmpScore2 = transReceptor->inner_.coefficients_[i].value * qRotLigand_[j].outer_.coefficients_[i].value;
			tmpScore += (tmpScore1 + tmpScore2);
			
		}
		
		printf("%lf \n",tmpScore);
		bestScores.insert(make_pair(tmpScore,ScoreConfiguration(R, ((2.0*PI)/alphaSize_) * j, beta1, gamma1, beta2, gamma2)));

		minScore = min(minScore, tmpScore);
		maxScore = max(maxScore, tmpScore);
		while ((int)bestScores.size() > scoresSize_)
		{
			bestScores.erase(bestScores.begin());
		}
	}

	printf("For R:%lf min score is %lf; max score is %lf\n",R, minScore, maxScore);
	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	if (R>0) delete transReceptor;*/
}
void Docking::dockingQmSearchTest(double R, double beta1, double gamma1, double beta2, double gamma2,vector <pair<double, ScoreConfiguration> >& scores)
{
	/*RotationMatrix rotationMatrixGamma1, rotationMatrixBeta1;
	RotationMatrix rotationMatrixGamma2, rotationMatrixBeta2;

	rotationMatrixGamma1.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma1) );
	rotationMatrixBeta1.calculateMatrix(receptor_.getOrder(), RotationAngle( beta1, 0.0) );
	rotationMatrixGamma2.calculateMatrix(receptor_.getOrder(), RotationAngle( 0, gamma2) );
	rotationMatrixBeta2.calculateMatrix(receptor_.getOrder(), RotationAngle( beta2, 0.0));
	
	rotReceptor_ = new Protein[1];
	qRotLigand_   = new Protein[1];

	receptor_.rotateTo(rotReceptor_[0], rotationMatrixGamma1);
	rotReceptor_[0].rotate(rotationMatrixBeta1);
	
	ligand_.rotateTo  (qRotLigand_[0], rotationMatrixGamma2);
	qRotLigand_[0].rotate(rotationMatrixBeta2);
	qRotLigand_[0].qTransition(penalty_); 

	Protein *transReceptor; 
	if (R > 0)
	{
		transReceptor = new Protein;
		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		rotReceptor_[0].translateTo(*transReceptor, translationmatrix);
	}else
	{
		transReceptor = &rotReceptor_[0];
	}

	
	set <pair<double, ScoreConfiguration> > bestScores;
	scores.clear();
	double minScore = 10000000.0, maxScore = -10000000.0;
	int order = receptor_.getOrder();

	for (int j = 1; j < alphaSize_; ++j)
	{
		double alfa2angle = j*((2.0*PI)/alphaSize_);
		double tmpScore = 0.0;
		for (int m = -(order-1); m <= (order-1); ++m)
		{
			double qmPlusCoeff = 0.0;
			double qmMinusCoeff = 0.0;
			
			for ( int n = 1; n <= order; ++n )
			for ( int l = 0; l <= (order-1); ++l)
			{
				qmPlusCoeff += (transReceptor->outer_.getValue(n,l,m) * qRotLigand_[0].inner_.getValue(n,l,m) ) + (transReceptor->inner_.getValue(n,l,m) * qRotLigand_[0].outer_.getValue(n,l,m));
				qmMinusCoeff += (transReceptor->outer_.getValue(n,l,m) * qRotLigand_[0].inner_.getValue(n,l,-m) ) + (transReceptor->inner_.getValue(n,l,m) * qRotLigand_[0].outer_.getValue(n,l,-m));
			}

			tmpScore += qmPlusCoeff * cos(m*alfa2angle) + qmMinusCoeff * sin ( -m*alfa2angle);

		}

		printf("%lf \n",tmpScore);
		bestScores.insert(make_pair(tmpScore,ScoreConfiguration(R, ((2.0*PI)/alphaSize_) * j, beta1, gamma1, beta2, gamma2)));

		minScore = min(minScore, tmpScore);
		maxScore = max(maxScore, tmpScore);
		while ((int)bestScores.size() > scoresSize_)
		{
			bestScores.erase(bestScores.begin());
		}
	}

	printf("For R:%lf min score is %lf; max score is %lf\n",R, minScore, maxScore);
	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	if (R>0) delete transReceptor;*/
}
void Docking::trigonometricCash()
{
	if ( trigonometricCalculated_ == false )
	{
		//printf("Kalkulisem trigonometrijski kes \n");
		int order = receptor_.getOrder();
		int matrixSize = (order)*(alphaSize_) ;
		cosValue_ = new vector<double>( matrixSize );
		sinValue_ = new vector<double>( matrixSize );
	
		double angle;
		for (int i = 0; i < alphaSize_; ++i)
		{
			if( i == 0 )
			{ 
				angle = 0.0;
			}
			else
			{ 
				angle = i*((2.0*PI)/alphaSize_);
			}

			for (int m = 0 ; m <= (order-1); ++m)
			{
				cosValue_->at( i*order + m ) = cos ( m*angle );
				//printf("%lf ",cosValue_->at( i*alphaSize_ + m ));
				sinValue_->at( i*order + m ) = sin ( m*angle );
				//printf("%lf ",sinValue_->at( i*alphaSize_ + m ));
				
			}
		}
		trigonometricCalculated_ = true;
	}
}
void Docking::preDockingCalculateQRotations(void)
{
	if (rotatationsCalculated_ == false)
	{
		//printf("Kalkulisem Q rotacije\n");
		int raSize = 20*(1<<(tessellationOrder_*2));
		raSize ++; //dodao zbog nultog kuta
		//rotationAngles_ = new RotationAngle[raSize];
		rotationAngles_ = new RotationAngle[raSize]; //dodao zbog (0,0) kuta

		//printf("Generating Rotational Angles...\n");
		Rotational_Angles(tessellationOrder_, rotationAngles_);
		//printf("Generated Rotational Angles (%d of them)...\n", raSize);

		rotReceptor_ = new Protein[raSize];
		qRotLigand_   = new Protein[raSize];

		RotationMatrix rotationMatrixGamma, rotationMatrixBeta;

		//printf("Rotating receptor & ligand...\n");
		for (int i = 0; i < raSize; ++i)
		{

			/*if (  (abs(rotationAngles_[i].beta) < 0.00001) && (abs(rotationAngles_[i].gamma) < 0.00001) ){
				printf("NULA: %lf %lf \n", rotationAngles_[i].beta, rotationAngles_[i].gamma );			
			}*/			

			rotationMatrixGamma.calculateMatrix(receptor_.getOrder(), RotationAngle(0, rotationAngles_[i].gamma));
			rotationMatrixBeta.calculateMatrix(receptor_.getOrder(), RotationAngle(rotationAngles_[i].beta, 0.0));

			receptor_.rotateTo(rotReceptor_[i],            rotationMatrixGamma);
			rotReceptor_[i].rotate(rotationMatrixBeta);

			ligand_.rotateTo  (qRotLigand_[i], rotationMatrixGamma);
			qRotLigand_[i].rotate(rotationMatrixBeta);
			qRotLigand_[i].qTransition(penalty_);

		}
		//printf("Rotated successfully (total %d receptor, %d ligand)...\n", raSize, raSize*alphaSize_);

		rotatationsCalculated_ = true;
	}
}
void Docking::dockingSearch(vector <pair<double, ScoreConfiguration> >& scores, vector<double> RadiusSet, vector<double>& MaxScoresRadius)
{
	int raSize = 20*(1<<(tessellationOrder_*2))+1;

	set <pair<double, ScoreConfiguration> > bestScores;

	preDockingCalculateRotations();
	//precalculation of all rotations

	Protein *transTmp = new Protein;

	//printf("Starting docking search...\n");
	//scores.clear();
	

	for (unsigned int radiusIndex = 0; radiusIndex < RadiusSet.size(); ++radiusIndex)
	{
		double R = RadiusSet[radiusIndex];
		double minScore = 10000000.0, maxScore = -10000000.0;


		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		for (int i = 0; i < raSize; ++i)
		{
			rotReceptor_[i].translateTo(*transTmp, translationmatrix);
			for (int j = 0; j < raSize*alphaSize_; ++j)
			{
				double tmpScore = scoreIt(*transTmp, rotLigand_[j], penalty_);
				bestScores.insert(make_pair(tmpScore,
						ScoreConfiguration(R, (j%alphaSize_) * (2.0*PI/alphaSize_), rotationAngles_[i].beta,
								rotationAngles_[i].gamma, rotationAngles_[j/alphaSize_].beta, rotationAngles_[j/alphaSize_].gamma)));

				minScore = min(minScore, tmpScore);
				maxScore = max(maxScore, tmpScore);
			}
			while ((int)bestScores.size() > scoresSize_)
			{
				bestScores.erase(bestScores.begin());
			}
		}
		printf("For R:%lf min score is %lf; max score is %lf\n",R, minScore, maxScore);
		MaxScoresRadius.push_back(R);
		MaxScoresRadius.push_back(maxScore);
	}

	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	delete transTmp;
	

}
void Docking::dockingQsearch(vector <pair<double, ScoreConfiguration> >& scores, vector<double> RadiusSet, vector<double>& MaxScoresRadius)
{
	int raSize = 20*(1<<(tessellationOrder_*2))+1;

	set <pair<double, ScoreConfiguration> > bestScores;

	preDockingCalculateQRotations();
	//precalculation of all rotations
	trigonometricCash();

	calculateCoeffMapping( );

	Protein *transReceptor = new Protein;

	//printf("Starting docking search...\n");

	//scores.clear();
	vector<double> qCoeffPlusPlus, qCoeffMinusMinus;
	int order = receptor_.getOrder();
	qCoeffPlusPlus.resize(order, 0.0);
	qCoeffMinusMinus.resize(order, 0.0);

	vector<double> qCoeffPlus;
	qCoeffPlus.resize((2* order - 1), 0.0); 
	vector<double> qCoeffMinus;
	qCoeffMinus.resize((2* order - 1), 0.0);
	int timeFlag = 0;

	//vector<int> translationIndexes;
	//receptor_.calculateTranslationIndexes( translationIndexes );

	for (unsigned int radiusIndex = 0; radiusIndex < RadiusSet.size(); ++radiusIndex)
	{
		double R = RadiusSet[radiusIndex];
		double minScore = 10000000.0, maxScore = -10000000.0;

		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		for (int i = 0; i < raSize; ++i)
		{
			/*clock_t start,end;
			start = clock ();*/
			//rotReceptor_[i].translateTo(*transReceptor, translationmatrix, translationIndexes);
			rotReceptor_[i].translateTo(*transReceptor, translationmatrix);
			/*end = clock ();
			if (timeFlag == 0) printf("Finished translation in about %d ms. \n",(end-start));
			start = clock ();*/
			for (int j = 0; j < raSize; ++j)
			{
				/*calculateQcoeffPlusPlus(qCoeffPlusPlus,qCoeffPlus, *transReceptor, qRotLigand_[j] );
				calculateQcoeffMinusMinus(qCoeffMinusMinus,qCoeffMinus, *transReceptor, qRotLigand_[j] );*/
				calculateQcoeffs(qCoeffPlusPlus, qCoeffPlus, qCoeffMinusMinus, qCoeffMinus,*transReceptor, qRotLigand_[j]);
				double maxScoreAlfa = - 100000.0;
				double maxAlfa = 0.0;				
				for (int k = 0; k < alphaSize_; ++k)
				{
					int index_alfa = k*order;
					double tmpScore = qCoeffPlusPlus[0];
					for (int m = 1; m <= (order-1); ++m)
					{
						tmpScore += (qCoeffPlusPlus[m] * cosValue_->at(index_alfa+m) ) + (qCoeffMinusMinus[m] * sinValue_->at(index_alfa+m) );
					}

					if (tmpScore > maxScoreAlfa){
						maxScoreAlfa = tmpScore;
						maxAlfa = k*(2.0*PI/alphaSize_);
					}					

					if ( (i+1 == raSize)&&(j+1==raSize)&& (k==0) ){
					printf("R:%lf ,b1:%lf, g1:%lf, a2:%lf, b2:%lf, g2:%lf score:%lf \n",R, k*(2.0*PI/alphaSize_),rotationAngles_[i].beta,rotationAngles_[i].gamma,rotationAngles_[j].beta, rotationAngles_[j].gamma,tmpScore); 
					}
					minScore = min(minScore, tmpScore);
					maxScore = max(maxScore, tmpScore);
				}
				bestScores.insert(make_pair( maxScoreAlfa,ScoreConfiguration(R, maxAlfa ,rotationAngles_[i].beta, rotationAngles_[i].gamma, rotationAngles_[j].beta, rotationAngles_[j].gamma )));				

			}
			while ((int)bestScores.size() > scoresSize_)
			{
				bestScores.erase(bestScores.begin());
			}
			/*end = clock ();
			if (timeFlag == 0){
				printf("Finished rotation in about %d ms. \n", (end-start)/100);
				timeFlag = 1;
			}*/
		}
		printf("For R:%lf min score is %E; max score is %E\n",R, minScore, maxScore);
		MaxScoresRadius.push_back(R);
		MaxScoresRadius.push_back(maxScore);
	}

	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	delete transReceptor;
	
}
void Docking::calculateCoeffMapping(  )
{
	if ( coeffMappingNLMCalculated_ == false ) 
	{
		//printf("Kalkulisem coeff Mapping \n");
		int order = receptor_.getOrder();
		coeffMappingNLM_.resize( 2*(order - 1) + 1 ); 
		coeffMappingNLMcrt_.resize( 2*(order - 1) + 1 ); 
	
		for( int n = 1; n <= order; ++n)
		for( int l = 0; l <= n-1; ++l)
		for( int m = -l; m <= l; ++m)
		{
			int index_m = m + order - 1;
			int index_nlm = ligand_.inner_.getIndex(n,l,m);
			coeffMappingNLM_.at( index_m ).push_back( index_nlm );

			int index_nlm_crt = ligand_.inner_.getIndex(n,l,-m);
			coeffMappingNLMcrt_.at( index_m ).push_back( index_nlm_crt );
		}
		
		coeffMappingNLMCalculated_ = true;
	}
}
void Docking::calculateQcoeffPlusPlus(vector<double>& qCoeffPlusPlus, vector<double>& qCoeffPlus, Protein& transReceptor, Protein& qRotLigand )
{
	fill ( qCoeffPlusPlus.begin(), qCoeffPlusPlus.end(), 0.0 );
	fill ( qCoeffPlus.begin(), qCoeffPlus.end(), 0.0 );
	int order = receptor_.getOrder();

	double qmCoeff;
	int qCoeffPlusIndex = 0;
	for (int m = -(order-1); m <= (order-1); ++m)
	{
		qmCoeff = 0.0;
		int index_m = m + order - 1;
		list<int>::iterator it;
		for( it = coeffMappingNLM_.at(index_m).begin(); it != coeffMappingNLM_.at(index_m).end(); ++it)
		{
			qmCoeff += (transReceptor.outer_.coefficients_[*it].value * qRotLigand.inner_.coefficients_[*it].value) + (transReceptor.inner_.coefficients_[*it].value * qRotLigand.outer_.coefficients_[*it].value);
		}
		qCoeffPlus[qCoeffPlusIndex] = qmCoeff;
		qCoeffPlusIndex++;
	}

	int indexNula = order - 1;
	qCoeffPlusPlus[0] = qCoeffPlus[indexNula];
	for (int m = 1 ; m <= (order-1); ++m)
	{
		qCoeffPlusPlus[m] = (qCoeffPlus[indexNula+m] + qCoeffPlus[indexNula-m]);
	}
	
}
void Docking::calculateQcoeffs(vector<double>& qCoeffPlusPlus, vector<double>& qCoeffPlus,vector<double>& qCoeffMinusMinus,vector<double> &qCoeffMinus,Protein& transReceptor, Protein& qRotLigand)
{
	
	fill ( qCoeffPlusPlus.begin(), qCoeffPlusPlus.end(), 0.0 );
	fill ( qCoeffPlus.begin(), qCoeffPlus.end(), 0.0 );
	fill ( qCoeffMinusMinus.begin(), qCoeffMinusMinus.end(), 0.0 );
	fill ( qCoeffMinus.begin(), qCoeffMinus.end(), 0.0 );
	int order = receptor_.getOrder();

	double qmCoeffPlus,qmCoeffMinus;
	int qCoeffIndex = 0;
	for (int m = -(order-1); m <= (order-1); ++m)
	{
		qmCoeffPlus = 0.0;
		qmCoeffMinus = 0.0;
		int index_m = m + order - 1;
		list<int>::iterator it1,it2;
		it2 = coeffMappingNLMcrt_.at(index_m).begin();
		for( it1 = coeffMappingNLM_.at(index_m).begin(); it1 != coeffMappingNLM_.at(index_m).end(); ++it1, ++it2)
		{
			qmCoeffPlus += (transReceptor.outer_.coefficients_[*it1].value * qRotLigand.inner_.coefficients_[*it1].value) + (transReceptor.inner_.coefficients_[*it1].value * qRotLigand.outer_.coefficients_[*it1].value);
			qmCoeffMinus += (transReceptor.outer_.coefficients_[*it1].value * qRotLigand.inner_.coefficients_[*it2].value) + (transReceptor.inner_.coefficients_[*it1].value * qRotLigand.outer_.coefficients_[*it2].value);
		}
		qCoeffPlus[qCoeffIndex] = qmCoeffPlus;
		qCoeffMinus[qCoeffIndex] = qmCoeffMinus;
		qCoeffIndex++;
	}

	int indexNula = order - 1;
	qCoeffPlusPlus[0] = qCoeffPlus[indexNula];
	qCoeffMinusMinus[0]= 0;
	for (int m = 1 ; m <= (order-1); ++m)
	{
		qCoeffPlusPlus[m] = (qCoeffPlus[indexNula+m] + qCoeffPlus[indexNula-m]);
		qCoeffMinusMinus[m] = (qCoeffMinus[indexNula-m] - qCoeffMinus[indexNula+m]);
	}
}
void Docking::calculateQcoeffMinusMinus(vector<double>& qCoeffMinusMinus,vector<double> &qCoeffMinus, Protein& transReceptor, Protein& qRotLigand )
{
	fill ( qCoeffMinusMinus.begin(), qCoeffMinusMinus.end(), 0.0 );
	fill ( qCoeffMinus.begin(), qCoeffMinus.end(), 0.0 );
	int order = receptor_.getOrder();

	double qmCoeff;
	int qCoeffMinusIndex = 0;
	for (int m = -(order-1); m <= (order-1); ++m)
	{
		qmCoeff = 0.0;
		int index_m = m + order - 1;
		list<int>::iterator it1,it2;
		it2 = coeffMappingNLMcrt_.at(index_m).begin();
		for( it1 = coeffMappingNLM_.at(index_m).begin(); it1 != coeffMappingNLM_.at(index_m).end(); ++it1, ++it2)
		{
			qmCoeff += (transReceptor.outer_.coefficients_[*it1].value * qRotLigand.inner_.coefficients_[*it2].value) + (transReceptor.inner_.coefficients_[*it1].value * qRotLigand.outer_.coefficients_[*it2].value);
			//qmCoeff += (transReceptor.outer_.getValue(n,l,m) * qRotLigand.inner_.getValue(n,l,-m) ) + (transReceptor.inner_.getValue(n,l,m) * qRotLigand.outer_.getValue(n,l,-m));
		}
		qCoeffMinus[qCoeffMinusIndex] = qmCoeff;
		qCoeffMinusIndex++;
	}

	qCoeffMinusMinus[0]= 0;
	int indexNula = order - 1;
	for (int m = 1 ; m <= (order-1); ++m)
	{
		qCoeffMinusMinus[m] = (qCoeffMinus[indexNula-m] - qCoeffMinus[indexNula+m]);
	}

}

void Docking::freeMemory()
{
	delete [] rotationAngles_;
	delete [] rotReceptor_;
	delete [] rotLigand_;
}

void Docking::dockingSearch(vector <pair<double, ScoreConfiguration> >& scores)
{
	int raSize = 20*(1<<(tessellationOrder_*2));

	set <pair<double, ScoreConfiguration> > bestScores;

	preDockingCalculateRotations();

	Protein *transTmp = new Protein;

	
	scores.clear();
        

	for (double R = radiusStart_; R < radiusEnd_; R += 0.5)
	{
		double minScore = 10000000.0, maxScore = -10000000.0;

		printf("R: %lf\n", R);
		char buffer[100];
		sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
		TranslationMatrix translationmatrix(buffer);
		for (int i = 0; i < raSize; ++i)
		{
			rotReceptor_[i].translateTo(*transTmp, translationmatrix);
			for (int j = 0; j < raSize*alphaSize_; ++j)
			{
				double tmpScore = scoreIt(*transTmp, rotLigand_[j], penalty_);
				bestScores.insert(make_pair(tmpScore,ScoreConfiguration(R,(j%alphaSize_)*(2.0*PI/alphaSize_),rotationAngles_[i].beta,rotationAngles_[i].gamma,rotationAngles_[j/alphaSize_].beta, rotationAngles_[j/alphaSize_].gamma)));

				minScore = min(minScore, tmpScore);
				maxScore = max(maxScore, tmpScore);
			}
			while ((int)bestScores.size() > scoresSize_)
			{
				bestScores.erase(bestScores.begin());
			}
		}
		printf("For this R: min score is %lf; max score is %lf\n", minScore, maxScore);
		printf("OK\n");
	}

	for (set <pair<double, ScoreConfiguration> >::iterator itr = bestScores.begin(); itr != bestScores.end(); ++itr)
	{
		scores.push_back(*itr);
	}

	freeMemory();
	delete transTmp;
	
}

int Docking::outputScores(const string& outputFile, const string& header, vector <pair<double, ScoreConfiguration> > scores) const
{
	/*PdbFile ligandPDB;
	PdbFile receptorPDB;*/
	FILE *fp = fopen(outputFile.c_str(), "wt");
	//FILE *fpPDB = 0;

	if (fp == 0)
	{
		// can't open file
		return -1;
	}

	/*if (ligandPath_!="" && receptorPath_!="" && radiiPath_!="")
	{
		fpPDB = fopen((outputFile + ".pdb").c_str(), "w");

		if (fpPDB == NULL)
			return -1;
	}

	if (ligandPath_!="" && receptorPath_!="" && radiiPath_!="")
	{
		ligandPDB.Init((char *) ligandPath_.c_str());
		if (!ligandPDB.LoadAtmtypenumbers((char *) radiiPath_.c_str()))
			return -1;
		ligandPDB.UseUnitedRadius();
		ligandPDB.Import();

		receptorPDB.Init((char *) receptorPath_.c_str());
		if (!receptorPDB.LoadAtmtypenumbers((char *) radiiPath_.c_str()))
			return -1;
		receptorPDB.UseUnitedRadius();
		receptorPDB.Import();
	}*/

	fprintf(fp, "%s", header.c_str());

	dumpParameters(fp);
	sort(scores.begin(), scores.end(), greater < pair<double, ScoreConfiguration> >());

	//fprintf(fp, "# rank score R beta1 gamma1 alpha2 beta2 gamma2\n");
	fprintf(fp, "# rank score R Rec_beta1 Rec_gamma1 Lig_alpha2 Lig_beta2 Lig_gamma2\n");

	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		//fprintf(fp, "%d %lf %lf %lf %lf %lf %lf %lf\n", i+1, scores[i].first, scores[i].second.R, scores[i].second.beta1, scores[i].second.gamma1, scores[i].second.alpha, scores[i].second.beta2, scores[i].second.gamma2);

		fprintf(fp, "%d %E %lf %lf %lf %lf %lf %lf\n", i+1, scores[i].first, scores[i].second.R, scores[i].second.beta1, scores[i].second.gamma1, scores[i].second.alpha, scores[i].second.beta2, scores[i].second.gamma2 ); 
		

		/*if (ligandPath_!="" && receptorPath_!="" && radiiPath_!="")
		{
			fprintf (fpPDB, "MODEL %d\n", i);
			receptorPDB.WriteTransformedAtoms(fpPDB, 'R', scores[i].second.R, 0.0f, scores[i].second.beta1, scores[i].second.gamma1);
			fprintf (fpPDB, "TER\n");
			ligandPDB.WriteTransformedAtoms(fpPDB, 'L', 0.0f, scores[i].second.alpha, scores[i].second.beta2, scores[i].second.gamma2);
			fprintf (fpPDB, "TER\n");
			fprintf (fpPDB, "ENDMDL\n");
		}*/
	}

	fclose(fp);

	/*if (ligandPath_!="" && receptorPath_!="" && radiiPath_!="")
		fclose(fpPDB);*/

	return 0;
}

void Docking::checkOrders()
{
	if (ligand_.getOrder() != receptor_.getOrder())
	{
		fprintf(stderr, "Order of coefficients for receptor & ligand protein differ\n");
		exit(1);
	}
}


void Docking::setConfiguration(const ScoreConfiguration& scoreConfiguration, Protein &newReceptor, Protein &newLigand) const
{
	// rotate receptor
    RotationMatrix rotationMatrix;
    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, scoreConfiguration.gamma2));
	receptor_.rotateTo(newReceptor, rotationMatrix);
    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(scoreConfiguration.beta2, 0.0));
	newReceptor.rotate(rotationMatrix);

	// translate
	char buffer[100];
//	sprintf(buffer, "%s/%d/%.6lf.dat", "data/trans", receptor_.getOrder(), scoreConfiguration.R);
	sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), scoreConfiguration.R);
	TranslationMatrix translationmatrix(buffer);
	newReceptor.translate(translationmatrix);

    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, scoreConfiguration.gamma1));
	ligand_.rotateTo(newLigand, rotationMatrix);
    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(scoreConfiguration.beta1, 0.0));
	newLigand.rotate(rotationMatrix);
    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, scoreConfiguration.alpha));
	newLigand.rotate(rotationMatrix);
}

void Docking::setConfiguration(double R, double betaReceptor, double gammaReceptor, double alphaLigand, double betaLigand, double gammaLigand, Protein &newReceptor, Protein &newLigand) const {
	// rotate receptor
	RotationMatrix rotationMatrix;
	rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, gammaReceptor));
	receptor_.rotateTo(newReceptor, rotationMatrix);
    rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(betaReceptor, 0.0));
	newReceptor.rotate(rotationMatrix);

	// translate
	char buffer[100];
	//	sprintf(buffer, "%s/%d/%.6lf.dat", "data/trans", receptor_.getOrder(), scoreConfiguration.R);
	sprintf(buffer, "%s/%d/%.6lf.dat", translationPath_.c_str(), receptor_.getOrder(), R);
	TranslationMatrix translationmatrix(buffer);
	newReceptor.translate(translationmatrix);

	rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, gammaLigand));
	ligand_.rotateTo(newLigand, rotationMatrix);
	rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(betaLigand, 0.0));
	newLigand.rotate(rotationMatrix);
	rotationMatrix.calculateMatrix(receptor_.getOrder(), RotationAngle(0.0, alphaLigand));
	newLigand.rotate(rotationMatrix);
}

double Docking::scoreIt(const ScoreConfiguration& scoreConfiguration)
{
	Protein newReceptor, newLigand;

	this->setConfiguration(scoreConfiguration, newReceptor, newLigand);

	return this->scoreIt(newReceptor, newLigand, penalty_);
}

double Docking::scoreIt(double R, double betaReceptor, double gammaReceptor, double alphaLigand, double betaLigand, double gammaLigand)
{
	Protein newReceptor, newLigand;

	this->setConfiguration(R, betaReceptor, gammaReceptor, alphaLigand, betaLigand, gammaLigand, newReceptor, newLigand);

	return this->scoreIt(newReceptor, newLigand, penalty_);
}

void Docking::outputToGrid(const ScoreConfiguration& scoreConfiguration, const pair<string, string> receptorFile, const pair<string, string> ligandFile, double gridSize, double gridCellSize)
{
	Protein newReceptor, newLigand;

	this->setConfiguration(scoreConfiguration, newReceptor, newLigand);

	Grid gridNew(gridSize, gridCellSize);

	gridNew.generateFromCoefficients(newReceptor.inner_);
	gridNew.exportToFile(receptorFile.first);
	gridNew.generateFromCoefficients(newReceptor.outer_);
	gridNew.exportToFile(receptorFile.second);

	gridNew.generateFromCoefficients(newLigand.inner_);
	gridNew.exportToFile(ligandFile.first);
	gridNew.generateFromCoefficients(newLigand.outer_);
	gridNew.exportToFile(ligandFile.second);
}
