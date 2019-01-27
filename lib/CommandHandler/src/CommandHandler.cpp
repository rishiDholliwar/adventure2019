#include <CommandHandler.h>
#include <GameController.h>
#include <iostream>

// Initialize the default function map
CommandHandler::FunctionMap CommandHandler::_defFuncMap = []
{
    CommandHandler::FunctionMap mapping;
    mapping["/say"]  = &GameController::say;
    mapping["/alias"] = &GameController::setAlias;
    mapping["/unalias"] = &GameController::removeAlias;
    return mapping;
}();

CommandHandler::CommFunc CommandHandler::getCommand(std::string command,std::string userName)
{
	// For user configurable spellings
	// We need to look for the user's custom command map first

	//Find user's map
	auto mapIt = _userFuncMap.find(userName);
	if(mapIt != _userFuncMap.end())
	{
		// find command inside of user's map
		auto userMap = mapIt->second;
		auto it = userMap.find(command);
		if(it != userMap.end())
		{
			return it->second;
		}
	}
	if(_defFuncMap.find(command) == _defFuncMap.end())
	{
		return nullptr;
	}
	return _defFuncMap[command];
}

std::string CommandHandler::setAlias(std::string userName, std::string command, std::string newAlias)
{
	std::string error = "Error: could not set alias for \"";
	error += command;
	error += "\" to \"";
	error += newAlias;
	error += "\"";
	// Try and insert an empty function map for the user
	// If it fails, it will return us the current map
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));

	// Take the reference of the map... You don't want a copy
	auto userMap = &(ret.first)->second;

	// Check both the user and default map to see if the command
	// exists already or not
	auto it = userMap->find(command);
	if (it == userMap->end())
	{
		it = _defFuncMap.find(command);
		if (it == _defFuncMap.end())
		{
			return error;
		}
	}

	// Do not allow an alias of the same name in our default map
	auto checkIt = _defFuncMap.find(newAlias);
	if (checkIt != _defFuncMap.end())
	{
		return error;
	}

	auto mapRet = userMap->insert(std::pair(newAlias, it->second));
	// Fails if there is already an alias with this name
	if(mapRet.second == false)
	{
		return error;
	}

	std::string success = "Successfully set alias for \"";
	success += command;
	success += "\" to \"";
	success += newAlias;
	success += "\"";
	return success;
}

std::string CommandHandler::removeAlias(std::string userName, std::string alias)
{
	// Try and insert an empty function map for the user
	// If it fails, it will return us the current map
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));
	if(ret.second)
	{
		return "Alias does not exist";
	}
	auto mapIt = ret.first;
	auto res = mapIt->second.erase(alias);
	if (!res)
	{
		return "Failed to unalias: " + alias;
	}
	return "Successfully removed alias: " + alias;
}