#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H

#include <deque>
#include <vector>
#include <unordered_map>

#include <AlterSpace.h>
#include <GameController.h>
#include <UserController.h>
#include <Server.h>
#include <Response.h>

using AlterSpace::Alias;
using AlterSpace::Command;
using AlterSpace::Input;
using AlterSpace::Name;
using AlterSpace::Password;

using networking::Connection;

class GameController;
class UserController;

struct CommandInfo;

enum CommandType
{
    GAMECONTROLLER,
    USERCONTROLLER,
    COMMANDHANDLER,
    UNKNOWN
};
/*
     * Command Handler
     *
     * Stores and maps our commands to a string
     *
     * Command function pointers are returned to be used when found in our maps
*/
class CommandHandler {
public:
    using UserCommFunc = std::vector<Response>    (GameController::*) (Name userName, Input input);
    using CommHandFunc = std::string              (CommandHandler::*) (const Name& userName, const Input& input);
    using LognCommFunc = UserController::UserData (UserController::*) (const Name& userName, Password password, const Connection);

    using UserFunctionMap = std::unordered_map<Command, UserCommFunc>;
    using CommFunctionMap = std::unordered_map<Command, CommHandFunc>;
    using LognFunctionMap = std::unordered_map<Command, LognCommFunc>;

    CommandHandler() = default;

    /*
     * Retrieves the User Function pointer to a gamecontroller function
     *
     * Pre-Condition: Takes in a Name(std::string) and Command(std::string)
     *
     * Post-Condition: Returns a member function pointer
     *                  or nullptr if fails to find command
    */
    UserCommFunc getUserFunc(const Name& userName, const Command& command);

    /*
     * Retrieves the Command function pointer to a Command Handler function
     *
     * Pre-Condition: Takes in a Command(std::string)
     *
     * Post-Condition: Returns a member function pointer
     *                  or nullptr if fails to find command
    */
    CommHandFunc getCommFunc(const Command& command);

    /*
     * Retrieves the login function pointer to a User Controller function
     *
     * Pre-Condition: Takes in a Command(std::string)
     *
     * Post-Condition: Returns a member function pointer
     *                  or nullptr if fails to find command
    */
    LognCommFunc getLognFunc(const Command& command);

    /*
     * Parses the arguments for _setAlias
     * Calls _setAlias is args are valid
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string setAlias(const Name& userName, const Input& input);

    /*
     * Parses the arguments for _removeAlias
     * Calls _removeAlias is args are valid
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string removeAlias(const Name& userName, const Input& input);

    /*
     * Sets user alias for a command (Only works for game controller commands)
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string _setAlias(const Name& userName, const Command& command, const Alias& alias);

    /*
     * removes user alias for a command (Only works for game controller commands)
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string _removeAlias(const Name& userName, const Alias& alias);

    /*
     * Parses input and determines the type of command it is
     *
     * Pre-Condition: Takes in input
     *
     * Post-Condition: Returns a struct with CommandType, Command(std::string),
     *                  and the rest of the command(input)
    */
    CommandInfo parseCommand(const Input& input);

private:
    /*
     * Maps to function pointers
    */
    static UserFunctionMap _defUserMap;
    static CommFunctionMap _defCommMap;
    static LognFunctionMap _defLognMap;

    std::unordered_map<Name, UserFunctionMap> _userFuncMap;
};

struct CommandInfo
{
    CommandType type;
    Command command;
    Input input;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
