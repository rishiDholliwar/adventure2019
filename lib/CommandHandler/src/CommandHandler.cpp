#include <CommandHandler.h>
#include <GameController.h>
#include <iostream>

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
	
	auto mapIt = _userFuncMap.find(userName);
	if(mapIt != _userFuncMap.end())
	{
		auto it = (mapIt->second).find(command);
		if(it != mapIt->second.end())
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
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));
	auto mapIt = ret.first;
	auto it = mapIt->second.find(command);
	if (it == mapIt->second.end())
	{
		it = _defFuncMap.find(command);
	}
	if (it == _defFuncMap.end())
	{
		return error;
	}

	auto checkIt = _defFuncMap.find(newAlias);
	if (checkIt != _defFuncMap.end())
	{
		return error;
	}

	auto mapRet = mapIt->second.insert(std::pair(newAlias, it->second));
	if(!mapRet.second)
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
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::FunctionMap{}));
	auto mapIt = ret.first;
	auto res = mapIt->second.erase(alias);
	if (!res)
	{
		return "Failed to unalias: " + alias;
	}
	return "Successfully removed alias: " + alias;
}