/*
 * commandhandler.cpp
 *
 *  Created on: May 6, 2010
 *      Author: ivan
 */

#include "commanddefinitions.h"
#include "vmolcommand.h"
#include "../log/log.h"
#include "../gui/vmolgui.h"



int VmolCommand::handleCommands(std::vector<CommandParameter> commandVector)
{
	if (commandVector[0].parameter == COMMAND_CREATE)
		return handleCommandCreate(commandVector);
	else if (commandVector[0].parameter == COMMAND_CHANGE)
		return handleCommandChange(commandVector);
	else if (commandVector[0].parameter == COMMAND_REMOVE)
		return handleCommandRemove(commandVector);
//	else if (commandVector[0].parameter == COMMAND_HIDE)
//		handleCommandHide(commandVector);
//	else if (commandVector[0].parameter == COMMAND_SHOW)
//		handleCommandShow(commandVector);
	else if (commandVector[0].parameter == COMMAND_RUN)
		return handleCommandRun(commandVector);
	else if (commandVector[0].parameter == COMMAND_MATH)
		return handleCommandMath(commandVector);

	return 1;
}
