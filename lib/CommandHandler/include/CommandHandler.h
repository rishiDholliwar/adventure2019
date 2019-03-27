#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H

#include <deque>
#include <vector>
#include <unordered_map>
#include <memory>

#include <AlterSpace.h>
#include <Command.h>
#include <UserController.h>
#include <Server.h>
#include <Response.h>

using AlterSpace::Alias;
using AlterSpace::Invocation;
using AlterSpace::Input;
using AlterSpace::Name;
using AlterSpace::Password;

using networking::Connection;

/*
     * Command Handler
     *
     * Stores and maps our commands to a string
     *
     * Command function pointers are returned to be used when found in our maps
*/
class CommandHandler {
public:

    using CommandMap = std::unordered_map<Invocation, std::unique_ptr<Command>>;
    using UserMap = std::unordered_map<Invocation, std::shared_ptr<Command>>;

    CommandHandler() = default;

    /*
     * Retrieves the User Function pointer to a gamecontroller function
     *
     * Pre-Condition: Takes in a Name(std::string) and Command(std::string)
     *
     * Post-Condition: Returns a member function pointer
     *                  or nullptr if fails to find command
    */
    std::shared_ptr<Command> getCommand(const Name& userName, const Invocation& invokeWord, const Input& input, const Connection connection);

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
    std::string _setAlias(const Name& userName, const Invocation& invokeWord, const Alias& alias);

    /*
     * removes user alias for a command (Only works for game controller commands)
     *
     * Pre-Condition: Takes in a Name(std::string) and input
     *
     * Post-Condition: Returns an output string
    */
    std::string _removeAlias(const Name& userName, const Alias& alias);

    void registerCommand(const Invocation& invokeWord, std::unique_ptr<Command> command);

    const std::vector<std::unique_ptr<Command>> getAllCommands() const;

private:
    /*
     * Map to Commands
    */
    CommandMap _defCommandMap;

    std::unordered_map<Name, UserMap> _userCommandMap;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
