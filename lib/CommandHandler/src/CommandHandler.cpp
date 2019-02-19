#include <CommandHandler.h>
#include <GameController.h>
#include <SpellController.h>
#include <iostream>
#include <Utility.h>

// Initialize the default user function map
CommandHandler::UserFunctionMap CommandHandler::_defUserMap = []
{
    CommandHandler::UserFunctionMap mapping;
    mapping["/say"]  = &GameController::say;
    mapping["/broadcast"] = &GameController::broadcast;
    mapping["/move"] = &GameController::move;
    mapping["/get"] = &GameController::pickUp;
    mapping["/drop"] = &GameController::drop;
    // mapping["/logout"] = &GameController::logout;
    mapping["/inventory"] = &GameController::inventory;
    mapping["/swap"] = &GameController::swap;
    return mapping;
}();

// Initialize the default command handler function map
CommandHandler::CommFunctionMap CommandHandler::_defCommMap = []
{
    CommandHandler::CommFunctionMap mapping;
    mapping["/alias"]  	= &CommandHandler::setAlias;
    mapping["/unalias"] = &CommandHandler::removeAlias;
    return mapping;
}();

// Initialize the default login function map
CommandHandler::LognFunctionMap CommandHandler::_defLognMap = []
{
    CommandHandler::LognFunctionMap mapping;
    mapping["/login"]  = &UserController::login;
    mapping["/signup"] = &UserController::createUser;
    mapping["/logout"] = &UserController::logoutUser;
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
	std::string command = v[0];
	if ( _defCommMap.find(command) != _defCommMap.end() )
	{
		ci.type = CommandType::COMMANDHANDLER;
	}
	else if( _defLognMap.find(command) != _defLognMap.end() )
	{
		ci.type = CommandType::LOGIN;	
	}
	else
	{
		ci.type = CommandType::GAMECONTROLLER;
	}

	ci.command = v[0];
	ci.input = v[1];
	return ci;
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
	if(_defUserMap.find(command) == _defUserMap.end())
	{
		return nullptr;
	}
	return _defUserMap[command];
}

CommandHandler::LognCommFunc CommandHandler::getLognFunc( const Command& command )
{
	if( _defLognMap.find(command) == _defLognMap.end() )
	{
		return nullptr;
	}
	return _defLognMap[command];
}


CommandHandler::CommHandFunc CommandHandler::getCommFunc(const Command& command)
{
	if( _defCommMap.find(command) == _defCommMap.end() )
	{
		return nullptr;
	}
	return _defCommMap[command];
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
		itr = _defUserMap.find(command);
		if (itr == _defUserMap.end())
		{
			return error;
		}
	}

	// Do not allow an alias of the same name in our default map
	if ( _defUserMap.find(newAlias) != _defUserMap.end() ||
		 _defCommMap.find(newAlias) != _defCommMap.end() ||
		 _defLognMap.find(newAlias) != _defLognMap.end() )
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
