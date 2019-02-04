#include <CommandHandler.h>
#include <GameController.h>
#include <iostream>
#include <Utility.h>

// Initialize the default function map
CommandHandler::UserFunctionMap CommandHandler::_defFuncMap = []
{
    CommandHandler::UserFunctionMap mapping;
    mapping["/say"]  = &GameController::say;
    return mapping;
}();

CommandInfo CommandHandler::parseCommand(const std::string& input)
{
	std::vector<std::string> v = utility::popFront(input);
	CommandInfo ci{ .type = CommandType::UNKNOWN };
	if ( v.size() != 2 )
	{
		std::cout << "Error has occurred in parseCommand somehow..." << std::endl;
		std::cout << "DEBUG: contents of vector" << std::endl;
		for ( auto str : v )
		{
			std::cout << str << std::endl;
		}
		return ci;
	}

	/*
	// This logic will be used when user controller is integrated to this branch
	if ( _loginMap.find(v[0]) != _loginMap.end() )
	{
		ci.type = CommandType::LOGIN;
	}
	else
	{
		ci.type = CommandType::GAMECONTROLLER;
	}
	*/
	const std::string ALIAS = "/alias";
	const std::string UNALIAS = "/unalias";

	if ( v[0] == ALIAS || v[0] == UNALIAS )
	{
		ci.type = CommandType::COMMANDHANDLER;
	}
	else
	{
		ci.type = CommandType::GAMECONTROLLER;
	}
	ci.command = v[0];
	ci.input = v[1];
	return ci;
}

CommandHandler::CommHandFunc CommandHandler::getCommFunc(const Name& userName, const Command& command)
{
	// Turn this into a map when we have more than 2 functions from command handler?
	const std::string ALIAS = "/alias";
	const std::string UNALIAS = "/unalias";
	if ( command == ALIAS)
	{
		return &CommandHandler::setAlias;
	}
	else if ( command == UNALIAS )
	{
		return &CommandHandler::removeAlias;
	}
	return nullptr;

}

std::string CommandHandler::setAlias(const Name& userName, const std::string& input)
{
    std::vector<std::string> v = utility::tokenizeString(input);
    if(v.size() != 2)
    {
        return "Usage: /alias [command] [alias]";
    }
    std::string command = v[0];
    std::string alias = v[1];

    return _setAlias(userName, command, alias);
}

std::string CommandHandler::removeAlias(const Name& userName, const std::string& input)
{
    std::vector<std::string> v = utility::tokenizeString(input);
    if(v.size() != 1)
    {
        return "Usage: /unalias [alias]";
    }
    std::string alias = v[0];

    return _removeAlias(userName, alias);
}

CommandHandler::UserCommFunc CommandHandler::getUserFunc(const Name& userName, const Command& command)
{
	// For user configurable spellings
	// We need to look for the user's custom command map first

	//Find user's map
	auto mapItr = _userFuncMap.find(userName);
	if(mapItr != _userFuncMap.end())
	{
		// find command inside of user's map
		auto userMap = mapItr->second;
		auto itr = userMap.find(command);
		if(itr != userMap.end())
		{
			return itr->second;
		}
	}
	if(_defFuncMap.find(command) == _defFuncMap.end())
	{
		return nullptr;
	}
	return _defFuncMap[command];
}

std::string CommandHandler::_setAlias(const Name& userName, const Command& command, const Alias& newAlias)
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
	auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::UserFunctionMap{}));

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

std::string CommandHandler::_removeAlias(const Name& userName, const Alias& alias)
{
	// Try and insert an empty function map for the user
	// If it fails, it will return us the current map
	auto userFuncMap = _userFuncMap.insert(std::pair(userName, CommandHandler::UserFunctionMap{}));
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
