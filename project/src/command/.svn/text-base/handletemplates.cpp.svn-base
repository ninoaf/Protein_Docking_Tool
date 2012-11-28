/*
 * handletemplates.cpp
 *
 *  Created on: May 20, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"

int VmolCommand::handleTemplates(string templateName, string *templateValue)
{
	unsigned int i=0;
	string ret="";

	if (findVariable(COMMAND_VAR_ALL, templateName) == NULL)
	{
		*templateValue = templateName;

//		printf ("size = %d\tname = %s\tvalue = %lf\n", doubleList_.size(), doubleList_[1].name.c_str(), doubleList_[1].value);

		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_VAR, "Can not use template, variable %s does not exist, or is of incorrect type!", templateName.c_str());
		return 1;
	}

	for (i=0; i<charList_.size(); i++)
	{
		if (charList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%c", charList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<uCharList_.size(); i++)
	{
		if (uCharList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%c", (char) uCharList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<longIntList_.size(); i++)
	{
		if (longIntList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%ld", longIntList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<uLongIntList_.size(); i++)
	{
		if (uLongIntList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%lu", uLongIntList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<uLongLongIntList_.size(); i++)
	{
		if (uLongLongIntList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%llx", uLongLongIntList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<floatList_.size(); i++)
	{
		if (floatList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%f", floatList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<doubleList_.size(); i++)
	{
		if (doubleList_[i].name == templateName)
		{
			char tempRet[100];
			sprintf (tempRet, "%lf", doubleList_[i].value);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<stringList_.size(); i++)
	{
		if (stringList_[i].name == templateName)
		{
			ret = *(stringList_[i].value);
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<vector3List_.size(); i++)
	{
		if (vector3List_[i].name == templateName)
		{
			char tempRet[300];
			sprintf (tempRet, "%lf %lf %lf", vector3List_[i].value.x, vector3List_[i].value.y, vector3List_[i].value.z);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<colorList_.size(); i++)
	{
		if (colorList_[i].name == templateName)
		{
			char tempRet[300];
			sprintf (tempRet, "%u %u %u", colorList_[i].value.r, colorList_[i].value.g, colorList_[i].value.b, colorList_[i].value.a);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}

	for (i=0; i<eulerVector3List_.size(); i++)
	{
		if (eulerVector3List_[i].name == templateName)
		{
			char tempRet[300];
			sprintf (tempRet, "%lf %lf %lf", eulerVector3List_[i].value.alpha, eulerVector3List_[i].value.beta, eulerVector3List_[i].value.gamma);
			ret = tempRet;
			*templateValue = ret;

//			Log::getInstance()->writeToLog("Template %s found successfully.", templateName.c_str());
			return 0;
		}
	}



	return 1;
}
