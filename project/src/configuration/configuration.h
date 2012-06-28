/*
 * configuration.h
 *
 *  Created on: Sep 15, 2009
 *      Author: canadi
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// Configuration file format: "parametar: value"
class Configuration
{
public:
	Configuration(const string &configFile);
	Configuration() { };
	~Configuration();
	int init(const std::string &configFile);
	int reload(const string &configFile);

	int getParameter(const string &parameter, int& retVal);
	int getParameter(const string &parameter, double& retVal);
	int getParameter(const string &parameter, string& retVal);
	bool changeParameter(char *configFile, char *parameter, char *newValue);

	void outputAll();

private:
	map <string, string> values_;
};



#endif /* CONFIGURATION_H_ */
