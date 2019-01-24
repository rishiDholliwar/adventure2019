#include <utility>
#include "GameController.h"
#include <iostream>
GameController::FunctionMap GameController::_funcMap = []
{
    std::map<std::string, std::string (GameController::*)(std::string, std::string)> mapping;
    mapping["!say"]  = &GameController::say;
    return mapping;
}();


std::string GameController::say(std::string userName, std::string input)
{
    std::cout << "Say " << input << std::endl;
    return userName+" says: "+input;
}

void GameController::receiveText(std::string input, std::string userName, std::function<void (std::string userName, std::string message)> callBack) {
    auto command = input.substr(0, input.find(' '));
    auto actionText = input.substr(input.find(' ') + 1, std::string::npos);
    std::string ret;
    std::string error = "Unknown";
    if(_funcMap.find(command) != _funcMap.end())
    {
        ret = (this->*_funcMap[command])(userName, actionText);
    }
    else
    {
        error = "Invalid command";
    }
    callBack(userName, ret);
}