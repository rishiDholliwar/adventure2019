#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H


#include <deque>
#include <vector>
#include <unordered_map>
#include <GameController.h>
#include <UserController.h>
#include <Server.h>
#include <Response.h>

class GameController;
class UserController;

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
    typedef std::vector<Response>    (GameController::*UserCommFunc) (Name userName, std::string input);
    typedef std::string              (CommandHandler::*CommHandFunc) (const Name& userName, const std::string& input);
    typedef UserController::UserData (UserController::*LognCommFunc) (const Name& userName, std::string password, const networking::Connection);

    using UserFunctionMap = std::unordered_map<Command, UserCommFunc>;
    using CommFunctionMap = std::unordered_map<Command, CommHandFunc>;
    using LognFunctionMap = std::unordered_map<Command, LognCommFunc>;

    CommandHandler() = default;
    UserCommFunc getUserFunc(const Name& userName, const Command& command);
    CommHandFunc getCommFunc(const Command& command);
    LognCommFunc getLognFunc(const Command& command);

    std::string setAlias(const Name& userName, const std::string& input);
    std::string removeAlias(const Name& userName, const std::string& input);
    std::string _setAlias(const Name& userName, const Command& command, const Alias& alias);
    std::string _removeAlias(const Name& userName, const Alias& alias);

    CommandInfo parseCommand(const std::string& input);

private:
    static UserFunctionMap _defUserMap;
    static CommFunctionMap _defCommMap;
    static LognFunctionMap _defLognMap;

    std::unordered_map<Name, UserFunctionMap> _userFuncMap;
};

struct CommandInfo
{
    CommandType type;
    CommandHandler::Command command;
    std::string input;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
