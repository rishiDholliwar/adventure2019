
#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H


#include <deque>
#include <vector>
#include "User.h"
#include <functional>
#include <unordered_map>
#include <GameController.h>

class GameController;

class CommandHandler {

private:
	typedef std::string (GameController::*CommFunc) (std::string userName, std::string input);
    using FunctionMap = std::unordered_map<std::string, CommFunc>;
    static FunctionMap _defFuncMap;
    std::unordered_map<std::string, FunctionMap> _userFuncMap;
    //Areas
    //other objects

public:
    CommandHandler(){};
    //handles real user input
    CommFunc getCommand(std::string command,std::string userName);
    std::string setAlias(std::string userName,std::string command, std::string alias);
    std::string removeAlias(std::string userName, std::string alias);
};


#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
