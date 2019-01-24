
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H


#include <deque>
#include <vector>
#include "User.h"
#include <functional>
#include <map>

class GameController {

    using FunctionMap = std::map<std::string, std::string(GameController::*)(std::string, std::string)>;

private:
    std::vector<User> _users;
    static FunctionMap _funcMap;
    //Areas
    //other objects

public:
    GameController()
    :_users{}{}
    //handles real user input
    void receiveText(std::string input,std::string userName, std::function<void (std::string userName, std::string message)> callBack);
    std::string say(std::string userName, std::string input);

};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
