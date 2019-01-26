
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include "User.h"
#include <memory>
#include <CommandHandler.h>

class CommandHandler;

class GameController {
private:
    std::vector<User> _users;
    std::unique_ptr<CommandHandler> _commandHandler;
    //Areas
    //other objects

public:
    GameController();
    //handles real user input
    std::string receiveText(std::string input,std::string userName);
    std::string say(std::string userName, std::string input);
    std::string setAlias(std::string userName, std::string input);
    std::string removeAlias(std::string userName, std::string input);
};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
