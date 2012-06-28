/*
 * configuration.cpp
 *
 *  Created on: Sep 15, 2009
 *      Author: canadi
 */

#include "configuration.h"

Configuration::Configuration(const std::string& configFile)
{
	init(configFile);
}

Configuration::~Configuration()
{
	;
}

// Initializes Configuration class with configFile. Returns number of read bytes, -1 in case of an error.
int Configuration::init(const string& configFile)
{
	ifstream input(configFile.c_str());

	if (input == 0)
	{
		// can't open file
		return -1;
	}

	string buffer;

	while (getline(input, buffer))
	{
		if (buffer.size() > 0 && buffer[0] == '#') continue;

		int colonPos = buffer.find(":");

		if ((size_t)colonPos != string::npos)
		{
			values_[buffer.substr(0, colonPos)] = buffer.substr(colonPos+2);
		}
	}

	return 0;
}

bool Configuration::changeParameter(char *configFile, char *parameter, char *newValue)
{
	unsigned int i=0;
	std::vector<string> loadedLines;

	string oldParameter = parameter;

	ifstream input(configFile);

	if (input == 0)
	{
		// can't open file
		return -1;
	}

	string buffer;

	while (getline(input, buffer))
	{
		if (buffer.size() > 0 && buffer[0] == '#') continue;

		int colonPos = buffer.find(":");

		if ((size_t)colonPos != string::npos)
		{
			string currentParameter = buffer.substr(0, colonPos);
			string oldValue = buffer.substr(colonPos+2);
			string newLine = "";

			if (currentParameter == oldParameter)
			{
				newLine = currentParameter + ": ";
				newLine += newValue;
			}
			else
			{
				newLine = buffer;
			}

			loadedLines.push_back(newLine);
		}
		else
			loadedLines.push_back(buffer);
	}

	input.close();

	FILE *fp;
	fp = fopen(configFile, "w");

	for (i=0; i<loadedLines.size(); i++)
		fprintf (fp, "%s\n", loadedLines[i].c_str());

	fclose(fp);





	return true;
}

// Reloades Configuration class with configFile. Returns -1 in case of an error.
int Configuration::reload(const string& configFile)
{
	values_.clear();
	return init(configFile);
}

// Returns -1 in case of an error
int Configuration::getParameter(const string& parameter, int& retVal)
{
	map<string, string>::iterator itr = values_.find(parameter);
	if (itr != values_.end())
	{
		sscanf(itr->second.c_str(), "%d", &retVal);
		return 0;
	}
	return -1;
}

// Returns -1 in case of an error
int Configuration::getParameter(const string& parameter, double& retVal)
{
	map<string, string>::iterator itr = values_.find(parameter);
	if (itr != values_.end())
	{
		sscanf(itr->second.c_str(), "%lf", &retVal);
		return 0;
	}
	return -1;
}

// Returns -1 in case of an error
int Configuration::getParameter(const string& parameter, string& retVal)
{
	map<string, string>::iterator itr = values_.find(parameter);
	if (itr != values_.end())
	{
		retVal = itr->second;
		return 0;
	}
	return -1;
}

// For debugging purposes only.
void Configuration::outputAll()
{
	for (map<string,string>::iterator itr = values_.begin(); itr != values_.end(); ++itr)
	{
		cout << itr->first << ":: " << itr->second << endl;
	}
}
