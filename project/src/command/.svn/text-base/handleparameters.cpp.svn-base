/*
 * handleparameters.cpp
 *
 *  Created on: May 16, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"



Parameters VmolCommand::handleParameters(vector<CommandParameter> commandVector)
{
	Parameters ret;

	ret.name = trimFileName(commandVector[1].value);

	for (unsigned int i=0; i<commandVector.size(); i++)
	{
		if (commandVector[i].parameter == PARAMETER_NAME)
		{
			ret.name = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_PATH)
		{
			ret.path = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_CENTER)
		{
			if (commandVector[i].value == "true")
				ret.center = true;
			else
				ret.center = false;
		}
		else if (commandVector[i].parameter == PARAMETER_CENTER_TYPE)
		{
			ret.centerType = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_NODE_TYPE)
		{
			ret.nodeType = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_NODE_PARAMS)
		{
			ret.nodeParams = commandVector[i].value;
		}
//		else if (commandVector[i].parameter == PARAMETER_NODE_PARENT)
//		{
//			ret.nodeParent = commandVector[i].value;
//		}
		else if (commandVector[i].parameter == PARAMETER_TRANSLATE)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf %lf %lf", &(ret.translate.x), &(ret.translate.y), &(ret.translate.z)) != 3)
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters for command %s!", PARAMETER_TRANSLATE);
		}
		else if (commandVector[i].parameter == PARAMETER_ROTATE_X)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf", &(ret.rotateX)) != 1)
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters for command %s!", PARAMETER_ROTATE_X);
		}
		else if (commandVector[i].parameter == PARAMETER_ROTATE_Y)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf", &(ret.rotateY)) != 1)
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters for command %s!", PARAMETER_ROTATE_Y);
		}
		else if (commandVector[i].parameter == PARAMETER_ROTATE_Z)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf", &(ret.rotateZ)) != 1)
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters for command %s!", PARAMETER_ROTATE_Z);
		}
		else if (commandVector[i].parameter == PARAMETER_ROTATE_EULER)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf %lf %lf", &(ret.rotateEuler.alpha), &(ret.rotateEuler.beta), &(ret.rotateEuler.gamma)) != 3)
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters for command %s!", PARAMETER_ROTATE_EULER);
		}
		else if (commandVector[i].parameter == PARAMETER_RADIUS_PATH)
		{
			ret.radiusPath = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_RADIUS_TYPE)
		{
			ret.radiusType = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_TYPE)
		{
			ret.type = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_VALUE)
		{
			ret.value = commandVector[i].value;
		}
		else if (commandVector[i].parameter == PARAMETER_AUTO_SCALE)
		{
			if (sscanf(commandVector[i].value.c_str(), "%lf", &(ret.autoScale)) != 1)
			{
				Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters when creating a node!");
				return ret;
			}
		}
		else if (commandVector[i].parameter == PARAMETER_PARENT)
		{
			ret.parent = commandVector[i].value;
		}
	}

//	ret.debugPrint();

	return ret;
}
