#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H


#include <deque>
#include <vector>
#include <User.h>
#include <unordered_map>
#include <GameController.h>

class GameController;
struct CommandInfo;

enum CommandType
{
    GAMECONTROLLER,
    LOGIN,
    COMMANDHANDLER,
    UNKNOWN
};

class CommandHandler {
public:
    using Name = std::string;
    using Alias = std::string;
    using Command = std::string;
    typedef std::string (GameController::*UserCommFunc) (Name userName, std::string input);
    typedef std::string (CommandHandler::*CommHandFunc) (const Name& userName, const std::string& input);
    // typedef std::string (UserController::*LognCommFunc) (Name userName, std::string input);
    using UserFunctionMap = std::unordered_map<Command, UserCommFunc>;
    using CommFunctionMap = std::unordered_map<Command, CommHandFunc>;

    CommandHandler() = default;
    UserCommFunc getUserFunc(const Name& userName, const Command& command);
    CommHandFunc getCommFunc(const Name& userName, const Command& command);
    // LognCommFunc getLognFunc(const Name& userName, const Command& command);

    std::string setAlias(const Name& userName, const std::string& input);
    std::string removeAlias(const Name& userName, const std::string& input);
    std::string _setAlias(const Name& userName, const Command& command, const Alias& alias);
    std::string _removeAlias(const Name& userName, const Alias& alias);

    CommandInfo parseCommand(const std::string& input);

private:
    static UserFunctionMap _defUserMap;
    static CommFunctionMap _defCommMap;
    // static LognFunctionMap _defLognMap;
    std::unordered_map<Name, UserFunctionMap> _userFuncMap;
};

struct CommandInfo
{
    CommandType type;
    CommandHandler::Command command;
    std::string input;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
