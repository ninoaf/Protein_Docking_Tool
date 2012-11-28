/*
 * log.h
 *
 *  Created on: May 6, 2010
 *      Author: ivan
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <vector>

#define ERR_MEMORY						1
#define	ERR_OPENING_FILE				2
#define ERR_COMMAND_WRONG_PARAM			3
#define ERR_COMMAND_NOT_IMPLEMENTED		4
#define ERR_COMMAND_WRONG_VAR			5
#define ERR_COMMAND_CANT_EXECUTE		6
#define ERR_RETURNED_FUNCTION			7



class Log
{
public:

	Log();
	~Log();

	void init();
	static Log* getInstance();

	void setLogPath(std::string logPath);
	void clearLog();

	int writeToLog(const char *logMessage, ...);
	int errorReport(std::string errorSeverity, unsigned int errorNumber, const char *errorMessage, ...);

	std::vector<std::string>& getLogLines();

private:
	static Log* singleInstance_;

	std::string logPath_;
	std::vector<std::string> logLines_;

	std::string getCurrentTime();
};



#endif /* LOG_H_ */
