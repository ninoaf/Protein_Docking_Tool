/*
 * handlecommandmath.cpp
 *
 *  Created on: May 20, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"
#include <stdlib.h>
#include "../math/evalmath/evaluate.h"



int VmolCommand::handleCommandMath(std::vector<CommandParameter> commandVector)
{
	unsigned int i=0;
	Parameters params;

	params = handleParameters(commandVector);

	if (params.name.size()==0 || params.value.size()==0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a variable!");
		return 1;
	}

	if ((void *) findVariable(COMMAND_VAR_ALL, params.name) == NULL)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Variable %s does not exist!", params.name.c_str());
		return 1;
	}
	else
	{
/*
		char *tempChar=NULL;
		unsigned char *tempUChar=NULL;
		long int *tempLongInt=NULL;
		unsigned long int *tempULongInt=NULL;
		unsigned long long int *tempULongLongInt=NULL;
		float *tempFloat=NULL;
		double *tempDouble=NULL;
		string *tempString=NULL;
		Vector3 *tempVector3=NULL;
		Color *tempColor=NULL;
		EulerVector3 *tempEulerVector3=NULL;
*/

		string value;

		value = params.value;

		double retEval=0.0f;

		if (evaluate((char *) value.c_str(), &retEval) != Success_)
		{
			Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, can not evaluate math expression!");
			return 1;
		}

//		printf ("value = %s\tretEval = %lf\n", (char *) value.c_str(), temp);

		for (i=0; i<charList_.size(); i++)
		{
			if (charList_[i].name == params.name)
			{
				charList_[i].value = (char) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<uCharList_.size(); i++)
		{
			if (uCharList_[i].name == params.name)
			{
				uCharList_[i].value = (unsigned char) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<longIntList_.size(); i++)
		{
			if (longIntList_[i].name == params.name)
			{
				longIntList_[i].value = (long int) retEval;

	//			Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<uLongIntList_.size(); i++)
		{
			if (uLongIntList_[i].name == params.name)
			{
				uLongIntList_[i].value = (unsigned long int) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<uLongLongIntList_.size(); i++)
		{
			if (uLongLongIntList_[i].name == params.name)
			{
				uLongLongIntList_[i].value = (unsigned long long int) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<floatList_.size(); i++)
		{
			if (floatList_[i].name == params.name)
			{
				floatList_[i].value = (float) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}

		for (i=0; i<doubleList_.size(); i++)
		{
			if (doubleList_[i].name == params.name)
			{
				doubleList_[i].value = (double) retEval;

//				Log::getInstance()->writeToLog("Evaluated math expression successfully.", params.name.c_str());
				return 0;
			}
		}
	}

	return 1;
}
