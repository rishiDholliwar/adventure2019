
#ifndef WEBSOCKETNETWORKING_GAMECONTROLLER_H
#define WEBSOCKETNETWORKING_GAMECONTROLLER_H


#include <deque>
#include <vector>
#include <User.h>
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
    std::string receiveText(std::string input,std::string userName);
    std::string say(std::string userName, std::string input);

};


#endif //WEBSOCKETNETWORKING_GAMECONTROLLER_H
