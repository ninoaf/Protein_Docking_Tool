/*
 * log.cpp
 *
 *  Created on: Sep 11, 2009
 *      Author: nino
 */

#include "log.h"

//using namespace std;

CLog::CLog()
{
	log_file = "data/log/log_file.txt";
}

CLog::~CLog()
{
}

/*
static const CLog* getInstance()
{
  if (!instance_) instance_ = new CLog;
  return instance_;
}
*/

void CLog::SetLogFile(std::string log_name)
{
	log_file = log_name;
}


/** Function that gets the current time, and formats it into a string, for use
 *  in Log and Error functions. */
std::string CLog::Get_Current_Time()
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

/** Function Error_Report(...) writes a report about an occured error. Content
 *  of the error log is given by error_message parameter. Also, severity of the
 *  error must be supplied. If the severity of the error is "ERROR", then the
 *  message will be logged, and the program will exit with status 1. */
//bool CLog::Error_Report(string log_file, string error_message, string severity)
bool CLog::Error_Report(std::string error_message, std::string severity)
{
	// time_t current_time;
	string temp_out="";

	temp_out = severity;
	temp_out += ": ";
	temp_out += error_message;

	printf ("%s\n", temp_out.c_str());

	Log_Append(log_file.c_str(), temp_out.c_str());

	if (severity == "ERROR")
		exit(1);

	return true;
}

/** Adds a line of text to the end of a log file. */
//bool CLog::Log_Append(string log_file, string log_line)
bool CLog::Log_Append(std::string log_line)
{
	std::string time_string;
	FILE *fp;

	time_string = Get_Current_Time();
	log_line = time_string + log_line;



	fp = fopen(log_file.c_str(), "a");
	if (fp == NULL)
	{
		cout << "[" << time_string << "] " << "ERROR: Can't open log file " << log_file << " to append new data!";		// not invoking Error_Report() for safety reasons (endless error loop)
		return false;
	}

	fprintf (fp, "%s\n", log_line.c_str());
	fclose (fp);

	return true;
}

/** Clears the log file. */
//bool CLog::Log_Clear(string log_file)
bool CLog::Log_Clear()
{
	FILE *fp;

	fp = fopen(log_file.c_str(), "w");

	if (fp == NULL)
	{
		cout << "ERROR: Can't open log file " << log_file << " to clear the contents!";		// not invoking Error_Handling() for safety reasons (endless error loop)
		return false;
	}

	fclose(fp);

	return true;
}

/** Adds a line to the end of the log file. This overloaded function enables direct string formating. */
//bool CLog::Log_Append(std::string log_file, const char *log_line, ...)
bool CLog::Log_Append(const char *log_line, ...)
{
	int n=0, size=strlen(log_line)*2 + 20;
	char *temp_line, *temp_new_line;
	bool ret=false;
	va_list param;

	temp_line = (char *) calloc (size, sizeof(char));
	if (temp_line == NULL)
	{
		Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
		return false;
	}

	while (true)
	{
		va_start(param, log_line);
		n = vsnprintf (temp_line, size, log_line, param);
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

		temp_new_line = (char *) realloc (temp_line, sizeof(char) * (size + 1));
		if (temp_new_line == NULL)
		{
			free(temp_line);
			Error_Report(pdt_log_file, (string) "Not enough memory, in function Log_Append (varargs version)!", "ERROR");
			return false;
		}
		else
		{
			temp_line = temp_new_line;
		}
	}

	ret = Log_Append(log_file, (string) temp_line);

	if (temp_line)
		free(temp_line);

	return ret;
}

/** Function Error_Report(...) writes a report about an occured error. Content of the error log is given by error_message parameter. Also, severity of the error must be supplied. If the severity of the error is "ERROR", then the message will be logged, and the program will exit with status 1. This overloaded function enables direct string formating. */
bool CLog::Error_Report(std::string log_file, std::string severity, const char *error_message, ...)
{
	int n=0, size=strlen(error_message)*2 + 20;
	char *temp_line, *temp_new_line;
	bool ret=false;
	va_list param;

	temp_line = (char *) calloc (size, sizeof(char));
	if (temp_line == NULL)
	{
		Error_Report(pdt_log_file, (string) "Not enough memory, in function Error_Report (varargs version)!", "ERROR");
		return false;
	}

	while (true)
	{
		va_start(param, error_message);
		n = vsnprintf (temp_line, size, error_message, param);
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

		temp_new_line = (char *) realloc (temp_line, sizeof(char) * (size + 1));
		if (temp_new_line == NULL)
		{
			free(temp_line);
			Error_Report(pdt_log_file, (string) "Not enough memory, in function Error_Report (varargs version)!", "ERROR");
			return false;
		}
		else
		{
			temp_line = temp_new_line;
		}
	}

	ret = Error_Report(log_file, (string) temp_line, severity);

	if (temp_line)
		free(temp_line);

	return ret;
}
