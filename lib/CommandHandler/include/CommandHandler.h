#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H


#include <deque>
#include <vector>
#include <User.h>
#include <unordered_map>
#include <GameController.h>

class GameController;

class CommandHandler {

private:
    using Name = std::string;
    using Command = std::string;
    using Alias = std::string;
	typedef std::string (GameController::*CommFunc) (Name userName, std::string input);
    using FunctionMap = std::unordered_map<Command, CommFunc>;

    static FunctionMap _defFuncMap;
    std::unordered_map<Name, FunctionMap> _userFuncMap;

public:
    CommandHandler() = default;
    CommFunc getCommand(const Name& userName, const Command& command);
    std::string setAlias(const Name& userName, const Command& command, const Alias& alias);
    std::string removeAlias(const Name& userName, const Alias& alias);
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
