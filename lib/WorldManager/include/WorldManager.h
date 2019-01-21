
#ifndef WEBSOCKETNETWORKING_WORLDMANAGER_H
#define WEBSOCKETNETWORKING_WORLDMANAGER_H


#include <deque>
#include <vector>
#include "User.h"
#include <functional>

class WorldManager {
private:
    std::vector<User> _users;
    //Areas
    //other objects

public:
    WorldManager()
    :_users{}{}
    //handles real user input
    void receiveText(User user, std::string input, std::function<void (const User user, const std::string feedback)> callBack);
};


#endif //WEBSOCKETNETWORKING_WORLDMANAGER_H
