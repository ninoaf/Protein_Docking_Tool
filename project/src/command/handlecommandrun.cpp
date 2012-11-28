/*
 * commanddefinitions.cpp
 *
 *  Created on: May 6, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"
#include <stdlib.h>



int VmolCommand::handleCommandRun(std::vector<CommandParameter> commandVector)
{
	Parameters params;

	params = handleParameters(commandVector);

	if (params.type.size()==0 || params.value.size()==0)
	{
		Log::getInstance()->errorReport("WARRNING", ERR_COMMAND_WRONG_PARAM, "Invalid script command, wrong command parameters!");
		return 1;
	}

	if (params.type == "exe")
	{
		Log::getInstance()->writeToLog("Running system command (%s)...", params.value.c_str());
		Log::getInstance()->writeToLog("System command executed, return value: %d.", system(params.value.c_str()));
	}
	else if (params.type == "script");
	{
		Log::getInstance()->writeToLog("Running script (%s)...", params.value.c_str());
		Log::getInstance()->writeToLog("Script executed, return value: %d.", loadScript(params.value));
	}

	return 0;
}











