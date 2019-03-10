#include <CommandHandler.h>
#include <GameController.h>
#include <Utility.h>

#include <iostream>

void CommandHandler::registerCommand(const Invocation& invokeWord, std::unique_ptr<Command> command) {
    CommandHandler::_defCommandMap[invokeWord] = std::move(command);
}

std::shared_ptr<Command> CommandHandler::getCommand(const Name& userName, const Invocation& invokeWord, const Input& input, const Connection connection)
{
	// For user configurable spellings
	// We need to look for the user's custom command map first

	//Find user's map
	auto mapItr = _userCommandMap.find(userName);
	if(mapItr != _userCommandMap.end())
	{
		// find command inside of user's map
		auto userMap = &(mapItr->second);
		auto itr = userMap->find(invokeWord);
		if(itr != userMap->end())
		{
            // Update with new input
			auto command = itr->second->clone(userName, input, connection);
            itr->second = std::move(command);
            return itr->second;
		}
	}
	if(_defCommandMap.find(invokeWord) == _defCommandMap.end())
	{
		return nullptr;
	}
    if( _defCommandMap[invokeWord]->isInteractable() ) {
        auto ret = _userCommandMap.insert(std::pair(userName, CommandHandler::UserMap{}));
        ret.first->second[invokeWord] = _defCommandMap[invokeWord]->clone(userName, input, connection);
        return ret.first->second[invokeWord];
    }
	return std::move(_defCommandMap[invokeWord]->clone(userName, input, connection));
}

std::string CommandHandler::setAlias(const Name& userName, const Input& input)
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

std::string CommandHandler::removeAlias(const Name& userName, const Input& input)
{
    std::vector<std::string> v = utility::tokenizeString(input);
    if(v.size() != 1)
    {
        return "Usage: /unalias [alias]";
    }
    std::string alias = v[0];

    return _removeAlias(userName, alias);
}

std::string CommandHandler::_setAlias(const Name& userName, const Invocation& invokeWord, const Alias& newAlias)
{
	std::string error   = "Error: could not set alias for \"";
	std::string success = "Successfully set alias for \"";

	std::string response  = invokeWord;
				response += "\" to \"";
				response += newAlias;
				response += "\"";

	success += response;
	error += response;

	// Initialize the user map with an empty one
	// If it fails, it will return us the current map
	// auto ret = _userFuncMap.insert(std::pair(userName, CommandHandler::UserFunctionMap{}));

	// // Take the reference of the map... You don't want a copy
	// auto userMap = &(ret.first)->second;

	// // Check both the user and default map to see if the command
	// // exists already or not
	// auto itr = userMap->find(command);
	// if (itr == userMap->end())
	// {
	// 	itr = _defUserMap.find(command);
	// 	if (itr == _defUserMap.end())
	// 	{
	// 		return error;
	// 	}
	// }

	// // Do not allow an alias of the same name in our default map
	// if ( _defUserMap.find(newAlias) != _defUserMap.end() ||
	// 	 _defCommMap.find(newAlias) != _defCommMap.end() ||
	// 	 _defLognMap.find(newAlias) != _defLognMap.end() )
	// {
	// 	return error;
	// }

	// auto mapItr = userMap->insert(std::pair(newAlias, itr->second));
	// // Fails if there is already an alias with this name
	// if( ! mapItr.second )
	// {
	// 	return error;
	// }
	return success;
}

std::string CommandHandler::_removeAlias(const Name& userName, const Alias& alias)
{
	// Try and insert an empty function map for the user
	// If it fails, it will return us the current map
	// auto userFuncMap = _userFuncMap.insert(std::pair(userName, CommandHandler::UserFunctionMap{}));
	// if(userFuncMap.second)
	// {
	// 	return "Alias does not exist";
	// }

	// auto map = userFuncMap.first;
	// auto numErased = map->second.erase(alias);

	// if ( numErased == 0 )
	// {
	// 	return "Failed to unalias: " + alias;
	// }
	return "Successfully removed alias: " + alias;
}
