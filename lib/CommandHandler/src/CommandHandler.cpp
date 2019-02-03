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

CommandHandler::CommFunc CommandHandler::getCommand(const Name& userName, const Command& command)
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

std::string CommandHandler::setAlias(const Name& userName, const Command& command, const Alias& newAlias)
{
	std::string error   = "Error: could not set alias for \"";
	std::string success = "Successfully set alias for \"";

	std::string response  = command;
				response += "\" to \"";
				response += newAlias;
				response += "\"";

	success += response;
	error += response;

	// Initialize the user map with an empty one
	// If it fails, it will return us the current map
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));

	// Take the reference of the map... You don't want a copy
	auto userMap = &(ret.first)->second;

	// Check both the user and default map to see if the command
	// exists already or not
	auto itr = userMap->find(command);
	if (itr == userMap->end())
	{
		itr = _defFuncMap.find(command);
		if (itr == _defFuncMap.end())
		{
			return error;
		}
	}

	// Do not allow an alias of the same name in our default map
	auto checkItr = _defFuncMap.find(newAlias);
	if (checkItr != _defFuncMap.end())
	{
		return error;
	}

	auto mapItr = userMap->insert(std::pair(newAlias, itr->second));
	// Fails if there is already an alias with this name
	if( ! mapItr.second )
	{
		return error;
	}
	return success;
}

std::string CommandHandler::removeAlias(const Name& userName, const Alias& alias)
{
	// Try and insert an empty function map for the user
	// If it fails, it will return us the current map
	auto userFuncMap = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));
	if(userFuncMap.second)
	{
		return "Alias does not exist";
	}

	auto map = userFuncMap.first;
	auto numErased = map->second.erase(alias);

	if ( numErased == 0 )
	{
		return "Failed to unalias: " + alias;
	}
	return "Successfully removed alias: " + alias;
}
