/*
 * log.h
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

using namespace std;

#ifndef LOG_H_
#define LOG_H_

class CLog
{
public:

	std::string log_file;

	static const CLog* getInstance();
	void SetLogFile(std::string log_name);
	std::string Get_Current_Time();
	bool Error_Report(std::string log_file, std::string severity, const char *error_message, ...);
	bool Error_Report(std::string error_message, std::string severity);
	bool Log_Append(std::string log_line);
	bool Log_Append(const char *log_line, ...);
	bool Log_Clear();


//private:
	CLog();
	~CLog();

private:
	//static CLog *instance_;
};

#endif /* LOG_H_ */
