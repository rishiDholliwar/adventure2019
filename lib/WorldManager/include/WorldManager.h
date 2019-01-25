
#ifndef WEBSOCKETNETWORKING_WORLDMANAGER_H
#define WEBSOCKETNETWORKING_WORLDMANAGER_H


#include <deque>
#include <vector>
#include "User.h"
#include "../../Controllers/include/CharacterController.h"
#include <functional>
#include <map>



class WorldManager {

    using FunctionMap = std::map<std::string, std::string(WorldManager::*)(std::string, std::string)>;

private:
    std::vector<User> _users;
    static FunctionMap _funcMap;
    CharacterController charController;
    //Areas
    //other objects

public:
    WorldManager()
    :_users{}{}
    //handles real user input
    void receiveText(std::string input,std::string userName, std::function<void (std::string userName, std::string message)> callBack);
    std::string say(std::string userName, std::string input);


};


#endif //WEBSOCKETNETWORKING_WORLDMANAGER_H
