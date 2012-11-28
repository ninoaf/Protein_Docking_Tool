/*
 * predocking_test.h
 *
 *  Created on: Jun 8, 2010
 *      Author: ivan
 */

#ifndef PREDOCKING_TEST_H_
#define PREDOCKING_TEST_H_

#include "predocking.h"
#include <string>



class PredockingTestDrive
{
public:
	/* backToGrid test
	 *
	 * ovaj test ucitava podatke o PDB fajlovima i parametre iz config.txt,
	 * izracunava koeficijente skinova, vraca ih natrag na grid i sva 4 grida
	 * exporta u fajlove (hardcodirane).
	 */
	void backToGrid(std::string configPath);

	void predockingToGrid(std::string configPath);
	void coefToGrid(std::string configPath);

	/* predockingRun test
	 *
	 * ovaj test ucitava podatke o PDB fajlovima i parametre iz config.txt,
	 * izracunava koeficijente skinova, i vraca ih u fajlove prema config.txt-u
     * */
	void predockingRun(std::string configPath);

private:
	std::string trimFileName(std::string path);
};

#endif /* PREDOCKING_TEST_H_ */
