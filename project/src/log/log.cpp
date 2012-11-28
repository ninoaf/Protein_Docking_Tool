/*
 * log.cpp
 *
 *  Created on: May 6, 2010
 *      Author: ivan
 */

#include "log.h"

using namespace std;

Log* Log::singleInstance_=NULL;



Log::Log()
{
	init();
}

Log::~Log()
{
	init();
}

void Log::init()
{
	logPath_ = "vmol2.log";
	logLines_.clear();
}

Log* Log::getInstance()
{
	if (singleInstance_ == NULL)
	{
		singleInstance_ = new Log();
		return singleInstance_;
	}

	return singleInstance_;
}

void Log::setLogPath(std::string logPath)
{
	logPath_ = logPath;
}

void Log::clearLog()
{
	FILE *fp;
	fp = fopen(logPath_.c_str(), "w");
	if (fp == NULL)
	{
		printf ("ERROR: can't open log file %s!\n", logPath_.c_str());
		return;
	}
	fclose(fp);

	logLines_.clear();
}

int Log::writeToLog(const char *logMessage, ...)
{
	int n=0, size=strlen(logMessage)*2 + 20;
	char *tempLine, *tempNewLine;
	FILE *fp;
	string timeString;
	va_list param;

	fp = fopen(logPath_.c_str(), "a");
	if (fp == NULL)
	{
		printf ("ERROR: can't open log file %s!\n", logPath_.c_str());
		return 2;
	}

	tempLine = (char *) calloc (size, sizeof(char));
	if (tempLine == NULL)
	{
//		Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
		printf ("ERROR: not enough memory to create log entry!\n");
		return 1;
	}

	while (true)
	{
		va_start(param, logMessage);
		n = vsnprintf (tempLine, size, logMessage, param);
		va_end(param);

		// If the string fits in the allocated memory, return it.
		if (n > -1 && n < size)
		{
			break;
		}

		// If not, allocate more space, and try again.
		if (n > -1)
		{
			// glibc 2.1
			// Precisely what is needed.
			size = n+1;
		}
		else
		{
			// glibc 2.0
			// Twice the old size.
			size *= 2;
		}

		tempNewLine = (char *) realloc (tempLine, sizeof(char) * (size + 1));
		if (tempNewLine == NULL)
		{
			free(tempLine);
//			Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
			printf ("ERROR: not enough memory to create log entry!\n");
			return 1;
		}
		else
		{
			tempLine = tempNewLine;
		}
	}

//	ret = Log_Append(log_file, (string) temp_line);

	timeString = getCurrentTime();
	fprintf (fp, "%s%s\n", timeString.c_str(), tempLine);

	fclose(fp);

	std::string tempString;
	tempString = timeString + tempLine;
	logLines_.push_back(tempString);

	if (tempLine)
		free(tempLine);

	return 0;
}

int Log::errorReport(std::string errorSeverity, unsigned int errorNumber, const char *errorMessage, ...)
{
	int n=0, size=strlen(errorMessage)*2 + 20;
	char *tempLine, *tempNewLine;
	FILE *fp;
	string timeString;
	va_list param;

	fp = fopen(logPath_.c_str(), "a");
	if (fp == NULL)
	{
		printf ("ERROR: can't open log file %s!\n", logPath_.c_str());
		return 2;
	}

	tempLine = (char *) calloc (size, sizeof(char));
	if (tempLine == NULL)
	{
//		Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
		printf ("ERROR: not enough memory to create log entry!\n");
		return 1;
	}

	while (true)
	{
		va_start(param, errorMessage);
		n = vsnprintf (tempLine, size, errorMessage, param);
		va_end(param);

		// If the string fits in the allocated memory, return it.
		if (n > -1 && n < size)
		{
			break;
		}

		// If not, allocate more space, and try again.
		if (n > -1)
		{
			// glibc 2.1
			// Precisely what is needed.
			size = n+1;
		}
		else
		{
			// glibc 2.0
			// Twice the old size.
			size *= 2;
		}

		tempNewLine = (char *) realloc (tempLine, sizeof(char) * (size + 1));
		if (tempNewLine == NULL)
		{
			free(tempLine);
//			Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
			printf ("ERROR: not enough memory to create log entry!\n");
			return 1;
		}
		else
		{
			tempLine = tempNewLine;
		}
	}

	timeString = getCurrentTime();
	fprintf (fp, "%s%s #%d: %s\n", timeString.c_str(), errorSeverity.c_str(), errorNumber, tempLine);
	fprintf (stderr, "%s%s #%d: %s\n", timeString.c_str(), errorSeverity.c_str(), errorNumber, tempLine);

	fclose(fp);

	if (tempLine)
		free(tempLine);

	char errorNumberString[100];
	std::string tempString;

	sprintf (errorNumberString, " #%d: ", errorNumber);
	tempString = timeString + errorSeverity;
	tempString += errorNumberString;
	tempString += tempLine;
	logLines_.push_back(tempString);

	if (errorSeverity == "ERROR")
		exit(1);

	return 0;
}

string Log::getCurrentTime()
{
	time_t current_time;
	tm *time_info;
	std::string ret;
	int hour=0, min=0, sec=0;
	char temp_time[50];

	current_time = time(NULL);
	time_info = localtime(&current_time);

	hour = time_info->tm_hour;
	min = time_info->tm_min;
	sec = time_info->tm_sec;

	sprintf (temp_time, "[%02d:%02d.%02d] ", hour, min, sec);

	ret = temp_time;

	return ret;
}

std::vector<std::string>& Log::getLogLines()
{
	return logLines_;
}
