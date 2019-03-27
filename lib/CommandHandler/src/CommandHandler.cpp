#include <CommandHandler.h>
#include <Utility.h>

#include <iostream>

void CommandHandler::registerCommand(CommandType invocation, std::unique_ptr<Command> command) {
    CommandHandler::_defCommandMap[invocation] = std::move(command);
}

std::shared_ptr<Command> CommandHandler::getCommand(const Name& userName, CommandType invocation, const Input& input, const Connection connection)
{
	// For user configurable spellings
	// We need to look for the user's custom command map first

	//Find user's map
	auto mapItr = _userCommandMap.find(userName);
	if(mapItr != _userCommandMap.end())
	{
		// find command inside of user's map
		auto userMap = &(mapItr->second);
		auto itr = userMap->find(invocation);
		if(itr != userMap->end())
		{
            // Update with new input
            itr->second = itr->second->clone(userName, input, connection);
            return itr->second;
		}
	}
	if(_defCommandMap.find(invocation) == _defCommandMap.end())
	{
		return nullptr;
	}
    if( _defCommandMap[invocation]->isInteractable() ) {
        auto ret = _userCommandMap.insert(std::pair(userName, CommandHandler::UserMap{}));
        ret.first->second[invocation] = _defCommandMap[invocation]->clone(userName, input, connection);
        return ret.first->second[invocation];
    }
	return _defCommandMap[invocation]->clone(userName, input, connection);
}

const std::vector<std::unique_ptr<Command>> CommandHandler::getAllCommands() const{
    std::vector<std::unique_ptr<Command>> commands;
    commands.reserve(_defCommandMap.size());
    for(auto& itr : _defCommandMap) {
        commands.push_back(std::move(itr.second->clone()));
    }
    return commands;
}
