#include "GameController.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <Utility.h>
#include <memory>

GameController::GameController()
{
    _commandHandler = std::make_unique<CommandHandler>();
}

std::string GameController::setAlias(std::string userName, std::string input)
{
    std::vector<std::string> v = utility::stringToVector(input);
    if(v.size() != 2)
    {
        return "Usage: /alias [command] [alias]";
    }
    std::string command = v[0];
    std::string alias = v[1];
    
    return _commandHandler->setAlias(userName, command, alias);
}

std::string GameController::removeAlias(std::string userName, std::string input)
{
    std::vector<std::string> v = utility::stringToVector(input);
    if(v.size() != 1)
    {
        return "Usage: /unalias [alias]";
    }
    std::string alias = v[0];
    
    return _commandHandler->removeAlias(userName, alias);
}

std::string GameController::say(std::string userName, std::string input)
{
    return userName+" says: "+input;
}

std::string GameController::receiveText(std::string input, std::string userName) {
    std::string command = input.substr(0, input.find(' '));
    std::string actionText{""};
    if(command.length() < input.length())
    {
        actionText = input.substr(command.length() + 1, std::string::npos);
    }
    std::string ret = "Unknown";
    auto commFunc = _commandHandler->getCommand(command, userName);
    if(commFunc != nullptr)
    {
        ret = (this->*commFunc)(userName, actionText);
    }
    else
    {
        ret = "Invalid command";
    }
    return ret;
}