
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H

#include "User.h"
#include <CommandHandler.h>

class CommandHandler;

class GameController {
private:
    std::vector<User> _users;
    //Areas
    //other objects

public:
    GameController();
    //handles real user input
    std::string say(std::string userName, std::string input);
};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
