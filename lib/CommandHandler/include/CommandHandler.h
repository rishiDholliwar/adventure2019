#ifndef WEBSOCKETNETWORKING_COMMANDHANDLER_H
#define WEBSOCKETNETWORKING_COMMANDHANDLER_H

#include <deque>
#include <vector>
#include <map>
#include <memory>

#include <AlterSpace.h>
#include <Command.h>
#include <CommandTranslator.h>
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

    using CommandMap = std::map<CommandType, std::unique_ptr<Command>>;
    using UserMap = std::map<CommandType, std::shared_ptr<Command>>;

    CommandHandler() = default;

    /*
     * Retrieves the User Function pointer to a gamecontroller function
     *
     * Pre-Condition: Takes in a Name(std::string) and Command(std::string)
     *
     * Post-Condition: Returns a member function pointer
     *                  or nullptr if fails to find command
    */
    std::shared_ptr<Command> getCommand(const Name& userName, CommandType invocation, const Input& input, const Connection connection);

    void registerCommand(CommandType invocation, std::unique_ptr<Command> command);

    const std::vector<std::unique_ptr<Command>> getAllCommands() const;

private:
    /*
     * Map to Commands
    */
    CommandMap _defCommandMap;

    std::map<Name, UserMap> _userCommandMap;
};

#endif //WEBSOCKETNETWORKING_COMMANDHANDLER_H
