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
/*
     * Command Handler
     *
     * Stores and maps our commands to a string
     *
     * Command function pointers are returned to be used when found in our maps
*/
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
    std::string setAlias(const Name& userName, const std::string& input);

    /*
     * Parses the arguments for _removeAlias
     * Calls _removeAlias is args are valid
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string removeAlias(const Name& userName, const std::string& input);

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
    CommandInfo parseCommand(const std::string& input);

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
    CommandHandler::Command command;
    std::string input;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
